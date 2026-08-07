function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

check(typeof QRhiWidget === "function", "Qt 6.7 QRhiWidget binding was not imported");
var rhiWidget = new QRhiWidget();
rhiWidget.setApi(QRhiWidget.Null);
check(rhiWidget.api().valueOf() === QRhiWidget.Null.valueOf(),
      "QRhiWidget API enum bridge failed");
rhiWidget.setDebugLayerEnabled(true);
check(rhiWidget.isDebugLayerEnabled(), "QRhiWidget debug-layer API failed");
rhiWidget.sampleCount = 4;
check(rhiWidget.sampleCount === 4, "QRhiWidget Qt property bridge failed");

check(typeof QKeySequenceEdit === "function", "QKeySequenceEdit binding was not imported");
var keyEditor = new QKeySequenceEdit();
keyEditor.clearButtonEnabled = true;
keyEditor.maximumSequenceLength = 2;
check(keyEditor.clearButtonEnabled, "QKeySequenceEdit Qt 6.4 clear-button property failed");
check(keyEditor.maximumSequenceLength === 2,
      "QKeySequenceEdit Qt 6.5 maximum-sequence-length property failed");

var combo = new QComboBox();
// QComboBox::LabelDrawingMode was added in Qt 6.9.
if (typeof QComboBox.LabelDrawingMode !== "undefined") {
    combo.setLabelDrawingMode(QComboBox.UseDelegate);
    check(combo.labelDrawingMode.valueOf() === QComboBox.UseDelegate.valueOf(),
          "QComboBox Qt 6.9 label drawing mode failed");
}

var formHost = new QWidget();
var form = new QFormLayout(formHost);
var field = new QLineEdit(formHost);
form.addRow("Name", field);
check(form.isRowVisible(0), "QFormLayout Qt 6.4 row visibility query failed");
form.setRowVisible(0, false);
check(!form.isRowVisible(field), "QFormLayout Qt 6.4 row visibility setter failed");

var wheelEvent = new QGraphicsSceneWheelEvent();
wheelEvent.setTimestamp(1234);
check(wheelEvent.timestamp() === 1234, "QGraphicsSceneEvent Qt 6.2 timestamp failed");
wheelEvent.setPixelDelta(new QPoint(4, 5));
check(wheelEvent.pixelDelta().x() === 4 && wheelEvent.pixelDelta().y() === 5,
      "QGraphicsSceneWheelEvent Qt 6.2 pixel delta failed");
wheelEvent.setPhase(Qt.ScrollUpdate);
check(wheelEvent.phase().valueOf() === Qt.ScrollUpdate.valueOf(),
      "QGraphicsSceneWheelEvent Qt 6.2 scroll phase failed");
wheelEvent.setInverted(true);
check(wheelEvent.isInverted(), "QGraphicsSceneWheelEvent Qt 6.2 inversion flag failed");

check(typeof QStyle.PM_LineEditIconSize !== "undefined"
      && typeof QStyle.PM_LineEditIconMargin !== "undefined",
      "Qt 6.2/6.3 QStyle pixel metrics were not exported");
check(typeof QStyle.SH_Table_AlwaysDrawLeftTopGridLines !== "undefined"
      && typeof QStyle.SH_SpinBox_SelectOnStep !== "undefined",
      "Qt 6.3 QStyle hints were not exported");

var listView = new QListView();
if (typeof listView.updateThreshold !== "undefined") {
    listView.updateThreshold = 77;
    check(listView.updateThreshold === 77, "QAbstractItemView Qt 6.9 property failed");
}

var identifiedWidget = new QWidget();
if (typeof identifiedWidget.accessibleIdentifier !== "undefined") {
    identifiedWidget.accessibleIdentifier = "qt6-additions-smoke";
    check(identifiedWidget.accessibleIdentifier === "qt6-additions-smoke",
          "QWidget Qt 6.9 accessible identifier failed");
}

var checkBox = new QCheckBox();
var observedState = -1;
function onCheckStateChanged(state) { observedState = state.valueOf(); }
checkBox.checkStateChanged.connect(onCheckStateChanged);
checkBox.setCheckState(Qt.Checked);
check(observedState === Qt.Checked.valueOf(), "QCheckBox Qt 6.7 typed signal failed");
checkBox.checkStateChanged.disconnect(onCheckStateChanged);

var stack = new QStackedWidget();
if (typeof stack.widgetAdded !== "undefined") {
    var addedIndex = -1;
    function onWidgetAdded(index) { addedIndex = index; }
    stack.widgetAdded.connect(onWidgetAdded);
    stack.addWidget(new QWidget());
    check(addedIndex === 0, "QStackedWidget Qt 6.9 widgetAdded signal failed");
    stack.widgetAdded.disconnect(onWidgetAdded);
}

var mainWindow = new QMainWindow();
var dock = new QDockWidget();
mainWindow.addDockWidget(Qt.LeftDockWidgetArea, dock);
if (typeof dock.dockLocation !== "undefined") {
    check(dock.dockLocation.valueOf() === Qt.LeftDockWidgetArea.valueOf(),
          "QDockWidget Qt 6.9 dockLocation property read failed");
    dock.dockLocation = Qt.RightDockWidgetArea;
    check(dock.dockLocation.valueOf() === Qt.RightDockWidgetArea.valueOf(),
          "QDockWidget Qt 6.9 dockLocation property write failed");
}

var wizard = new QWizard();
wizard.addPage(new QWizardPage());
var secondPageId = wizard.addPage(new QWizardPage());
// QWizard initializes its current page when it is shown.  Set the ID after
// that initialization so the slot's effect is observable in a headless
// offscreen application too.
wizard.show();
wizard.setCurrentId(secondPageId);
check(wizard.currentId === secondPageId, "QWizard Qt 6.4 setCurrentId slot failed");

// Keep the headless evaluator deterministic: these are all top-level widget
// instances, so close them explicitly before the script engine is destroyed.
rhiWidget.close();
keyEditor.close();
combo.close();
formHost.close();
listView.close();
identifiedWidget.close();
checkBox.close();
stack.close();
mainWindow.close();
wizard.close();
