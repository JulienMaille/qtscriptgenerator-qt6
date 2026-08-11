# QtScriptGenerator bindings for Qt 6

This is a port of the generated QtScript bindings used by QCAD, from Qt 5 to
Qt 6. It currently builds the `qt.core`, `qt.gui`, `qt.network`, `qt.sql`,
`qt.widgets`, `qt.printsupport`, `qt.uitools`, `qt.xml`, `qt.svg`, and `qt.svgwidgets`
QtScript extensions and the `qs_eval` functional-test executable with Qt
6.8.3 or newer/MSVC x64. The evaluator is
linked to the ported QtScriptTools module and includes a headless debugger
attach/widget smoke test.

This repository contains the generated binding sources and the handwritten Qt
6 compatibility/build layer. It does not contain a Qt 6 port of the generator
executable itself; API additions are maintained in the generated sources.

> This port was developed with AI assistance under human planning and review,
with every change verified by continuous integration.

## Origin and attribution

The Qt 5 baseline came from QCAD's bundled
`src/3rdparty/qt-labs-qtscriptgenerator-5.5.0` tree. QCAD's version-selector
projects through Qt 5.15.8 continued to build that shared binding tree. QCAD's
bundled readme credits
[shibukawa/qtscriptgenerator](https://github.com/shibukawa/qtscriptgenerator),
a fork of the original Qt Labs Qt Script Generator.

This Qt 6 port keeps that history and includes the upstream LGPL license and
Qt LGPL exception.

## Prerequisites

- Qt 6.8.3 or newer built for MSVC x64.
- [QtScript port for Qt 6](https://github.com/JulienMaille/qtscript-qt6),
  installed as `Qt6::Script` and
  `Qt6::ScriptTools` with CMake package metadata; qmake module metadata is
  also required when using the legacy nmake backend.
- CMake 3.16 or newer (the minimum required by Qt 6.8).
- Visual Studio 2022 or newer with the x64 C++ toolchain.
- Ninja Multi-Config is the default CMake generator. A Visual Studio generator
  can be selected explicitly when needed.

CI covers Release builds with Qt 6.8.3 LTS and Qt 6.11.1 on Windows.

## Build and test

From PowerShell:

```powershell
.\build.ps1 -Configuration All
.\test.ps1 -Configuration All
```

`build.ps1` uses CMake with Ninja Multi-Config by default. The existing
qmake/nmake build remains available explicitly:

```powershell
.\build.ps1 -Backend NMake -Configuration All
```

Custom Qt locations can be selected without editing files:

```powershell
.\build.ps1 -QtPrefix C:\Qt\my-qt6 -QtScriptPrefix C:\Qt\my-qtscript-overlay
```

The scripts also accept `QT_ROOT_DIR` and `QTSCRIPT_PREFIX`. If QtScript is
installed into the Qt prefix, only `QT_ROOT_DIR` is needed:

```powershell
$env:QT_ROOT_DIR = 'C:\Qt\6.11.1\6.11.1\msvc2022_64'
.\build.ps1 -Generator "Ninja Multi-Config" -Configuration Release
```

The Visual Studio generator can be selected explicitly:

```powershell
.\build.ps1 -Generator "Visual Studio 17 2022" -Configuration All
```

The plugins are written to `plugins\script`; Debug and Release evaluators are
written below `qtbindings\qs_eval`. `test.ps1` runs smoke tests for core, GUI,
loopback Network, in-memory SQLite, offscreen widgets, PDF PrintSupport,
Designer UI, DOM XML parsing/manipulation, SVG rendering/generation, and SVG
Widgets through that evaluator.
Each module also has a regression smoke
script covering value conversion, overloads, state changes, and failure/cleanup
paths (for example, leap-day `QDateTime` arithmetic, transaction rollback,
model/view data, cookie parsing, PDF page geometry, and malformed `.ui`
handling).

Logs are written to `logs`; each evaluator process has a timeout so a binding
or cleanup hang is reported with its captured output. Use
`-EvaluatorTimeoutMilliseconds` with `test.ps1` to adjust the default 30-second
per-process limit on slower machines.

The same run also constructs and attaches `QScriptEngineDebugger`, verifies a
debugger action and console widget, then detaches it without showing a window.

The port has no Qt5Compat build or runtime dependency. `test.ps1` rejects
source references to it and inspects every selected plugin and evaluator
import table before running the functional tests.

## Qt 6 API additions

The port does more than remove obsolete Qt 5 surface area. It also exports
selected APIs introduced after Qt 5.15:

- `QRhiWidget` construction and its public configuration/framebuffer API
  (Qt 6.7), while its rendering callbacks remain native C++ extension points.
- `QKeySequenceEdit`, including the Qt 6 clear-button, maximum-length, and
  finishing-key-combination properties.
- `QComboBox.LabelDrawingMode` and its accessors (Qt 6.9).
- `QFormLayout` row visibility overloads (Qt 6.4).
- `QGraphicsSceneEvent.timestamp` and the Qt 6 wheel-event pixel delta,
  scroll phase, and inversion API, together with `Qt.ScrollPhase` values.
- Newer `QStyle` line-edit metrics and table/spin-box style hints.
- Meta-object properties, slots, and signals added to existing QObject types,
  including `QAbstractItemView.updateThreshold`,
  `QWidget.accessibleIdentifier`, `QDockWidget.dockLocation`,
  `QWizard.setCurrentId`, `QCheckBox.checkStateChanged`, and
  `QStackedWidget.widgetAdded`.
- Qt 6 GUI values such as `QFont.PreferTypoLineMetrics`,
  `QPainter.LosslessImageRendering`, `QPainter.VerticalSubpixelPositioning`,
  and `QPainter.NonCosmeticBrushPatterns`.
- Qt 6 SQL APIs including `QSqlError.nativeErrorCode`, named bound-value
  inspection, and `QSqlQuery.positionalBindingEnabled`.
- Qt 6 Network values including current HTTP/2/request-control attributes,
  TLS 1.3 and DTLS protocols, and EC/DH SSL key algorithms.
- Qt 6 `QPrinter.copyCount()` and `setCopyCount()` alongside the retained Qt 5
  copy-count API.
- `QUiLoader` form loading against the Qt 6 widget set, including newer widget
  properties such as `accessibleIdentifier`.
- QtSvg's `QtSvg.Option`/`QtSvg.Options` flags, `QSvgRenderer` loading and
  raster rendering, `QSvgGenerator` output, and the QtSvgWidgets
  `QSvgWidget`/`QGraphicsSvgItem` classes.
- Qt XML DOM parsing through `QDomDocument`, including Qt 6
  `ParseOption`/`ParseOptions` and structured `ParseResult` diagnostics,
  namespace-aware lookup, node cloning/import, and serialization.
- Qt 6 date/time parity through the curated `QLocale` and `QTimeZone` value
  bindings, `QDateTime`'s `fromSecsSinceEpoch`/`toSecsSinceEpoch` and
  time-zone conversion APIs, `QDateTimeEdit.timeZone`, plus locale code/BCP-47
  and IANA-zone helpers.
- Qt 6 input-event parity through `QEvent` category predicates, input-device
  metadata, modern `QMouseEvent` positions/lifecycle, `QEventPoint` value
  construction/accessors, and synthetic `QPointerEvent` point-list events,
  together with native `QWheelEvent`/`QTabletEvent` pixel, phase, pressure,
  and tilt accessors.

`tests\qt6-additions-smoke.js`, `tests\xml-smoke.js`, and
`tests\xml-regressions-smoke.js` exercise these additions. Still deferred are
`QStyleOptionHeaderV2` and script-implemented `QRhiWidget`
rendering hooks that would require exposing the QRhi integration types.

## Current compatibility scope

The Core, GUI, Network, SQL, XML DOM, Widgets, PrintSupport, UI Tools, SVG, and
SVG Widgets extensions
retain the generated Qt 5 script API where a direct Qt 6 equivalent exists.
Compatibility adapters cover Qt 6 metatypes and flags, QtScript `QRegExp`, a
local `QStringConverter`-backed `QTextCodec` facade, XML `QStringView` results,
container changes, and removed enum aliases. The XML extension intentionally
exposes the Qt 6 DOM module and its parse options/results while omitting the
removed SAX `QXmlReader`/`QXmlInputSource` family; QtCore's
`QXmlStreamReader`/`QXmlStreamWriter` bindings remain available.

`QDate`, `QTime`, and `QDateTime` return values on their QtScript QVariant
wrappers instead of Qt 6's built-in JavaScript-Date conversion, which preserves
the generated value prototypes during chained calls.

`QLocale` and `QTimeZone` are curated Qt 6 value bindings rather than a
mechanical Qt 5 surface dump: removed `QStringRef` overloads and obsolete
country/time-zone constructors are omitted, while locale-code, BCP-47, IANA,
fixed-offset, and `QDateTime` conversion paths are covered by regression tests.

Some removed APIs have constrained compatibility behavior:

- `QTextStream.setCodec()` accepts encodings supported by Qt 6
  `QStringConverter`; unsupported legacy codecs raise a script error.
- `QXmlStreamWriter` is UTF-8-only in Qt 6; selecting another codec raises a
  script error.
- `QSettings.setIniCodec()` remains callable but is a no-op because Qt 6 INI
  files are UTF-8.
- Removed `QLibraryInfo` queries and `QCoreApplication.hasPendingEvents()`
  raise explicit script errors.
- Legacy `QTime` stopwatch methods use wall-clock `QTime` arithmetic.
- Removed `QTimeLine.CurveShape` symbolic values remain exported; Qt 6 uses
  `QEasingCurve` internally.
- `QPlainTextEdit.find(QRegExp)` and `QTextEdit.find(QRegExp)` use a Qt 6
  `QRegularExpression`; uncommon legacy `QRegExp` pattern modes may differ.
- Removed `QTouchEvent` mutation methods remain callable as no-ops because Qt 6
  touch-event data is immutable.
- Legacy `QPrinter` orientation, page-size, paper-name, margin, and copy-count
  methods are adapted to Qt 6 `QPageLayout`, `QPageSize`, and `copyCount()`.
  The removed Windows page-size ID methods raise explicit script errors.

Deferred core classes are `QBasicTimer` (move-only in Qt 6), `QMutex`'s removed
recursive-mode constructor (the recursive type became `QRecursiveMutex`), and
the state-machine classes (the Qt 6 prefix used here does not contain
QtStateMachine).

Widget classes removed from Qt 6 are not exported: `QDesktopWidget`,
`QGraphicsItemAnimation`, `QPictureFormatPlugin`, `QKeyEventTransition`, and
`QMouseEventTransition`. `QApplication` is exported as a static-only facade;
the evaluator still provides the live `qApp` instance for instance-level use.

The GUI extension omits APIs removed without a direct Qt 6 equivalent:
`QPictureIO`, `QRegExpValidator`, and the generated legacy event constructor
for `QTouchEvent.TouchPoint`. `QMatrix` is kept as a source-compatible alias
backed by `QTransform`.

The SQL extension preserves the generated Qt 5 API across Qt 6 changes:
`QSqlError.number()` and its setter methods are backed by the string-based
native error code, and `QSqlQuery.boundValues()` reconstructs the legacy
name-to-value map from Qt 6's bound-value names and positional list. The newer
native error-code, bound-value-name, and positional-binding APIs are also
exported.

The Network extension omits the removed
`QNetworkAccessManager.NetworkAccessibility` bearer-management enum and the
obsolete SPDY request attributes. Legacy `QSslSocket` CA/cipher configuration
entry points are implemented through Qt 6 `QSslConfiguration`, and legacy
certificate path-pattern modes map to Qt 6 `QSslCertificate.PatternSyntax`.

The SVG plugin exposes both `qt.svg` and `qt.svgwidgets` keys. This preserves
the Qt 5 extension key while matching Qt 6's split between the `QtSvg` and
`QtSvgWidgets` libraries. The bindings cover the renderer/generator APIs and
the widget/graphics-item APIs; they intentionally keep the legacy `QSvg`
namespace as an alias of Qt 6's `QtSvg` namespace.

## Out of scope

Qt WebKit and XMLPatterns was dropped from Qt 6 and is not supported by this
project. Qt WebEngine bindings are not planned. The following
original binding families are also out of scope:

- OpenGL and OpenGL Widgets.
- Multimedia and Multimedia Widgets.
- WebEngine bindings as a replacement for the old WebKit API.
- Generating bindings for additional Qt 6 modules.

The XMLPatterns, WebKit, and WebKitWidgets extensions were removed from Qt 6
and will not be ported by this project.
