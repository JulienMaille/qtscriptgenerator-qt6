function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

// Pixel writes/reads and a detached copy exercise the value-type conversion
// path rather than only checking that QImage can be constructed.
var image = new QImage(4, 3, QImage.Format_ARGB32);
// Keep the packed ARGB value below INT_MAX so this assertion is independent
// of whether a legacy wrapper exposes uint as a signed 32-bit script number.
var color = new QColor(12, 34, 56, 100);
image.fill(new QColor(0, 0, 0, 0).rgba());
image.setPixel(2, 1, color.rgba());
check(image.valid(2, 1) && image.pixel(2, 1) === color.rgba(),
      "QImage pixel conversion did not round-trip");
var copy = image.copy(new QRect(1, 0, 2, 2));
check(copy.width() === 2 && copy.height() === 2
      && copy.pixel(1, 1) === color.rgba(),
      "QImage QRect copy used the wrong coordinates");
var scaled = image.scaled(8, 6);
check(scaled.size().width() === 8 && scaled.size().height() === 6,
      "QImage scaling returned the wrong size");

// QTextCursor selection is sensitive to the MoveAnchor/KeepAnchor enum
// bridge and catches a common generated-overload regression.
var document = new QTextDocument();
document.setPlainText("alpha beta\ngamma");
var cursor = new QTextCursor(document);
// Moving to the current position legitimately returns false; verify the
// resulting position instead of treating that no-op as an error.
cursor.movePosition(QTextCursor.Start);
check(cursor.position() === 0, "QTextCursor did not move to start");
check(cursor.movePosition(QTextCursor.NextWord, QTextCursor.KeepAnchor),
      "QTextCursor KeepAnchor overload failed");
// Qt's word movement includes the separating space in this direction.
check(cursor.selectedText() === "alpha ", "QTextCursor selected the wrong word");
check(cursor.selectionStart() === 0 && cursor.selectionEnd() === 6,
      "QTextCursor selection bounds were not preserved");
cursor.clearSelection();
check(!cursor.hasSelection(), "QTextCursor clearSelection left stale state");

// The compatibility QRegExp wrapper must dispatch through the Qt 6
// QRegularExpression overloads, just like a native JavaScript RegExp.
var expression = new QRegExp("readme\\.txt");
var regexpDocument = new QTextDocument();
regexpDocument.setPlainText("readme.txt notes.md");
var documentMatch = regexpDocument.find(expression);
check(!documentMatch.isNull() && documentMatch.selectedText() === "readme.txt",
      "QTextDocument.find(QRegExp) overload failed");

var textEdit = new QTextEdit();
textEdit.setPlainText("readme.txt notes.md");
check(textEdit.find(expression), "QTextEdit.find(QRegExp) overload failed");
textEdit.close();

var plainTextEdit = new QPlainTextEdit();
plainTextEdit.setPlainText("readme.txt notes.md");
check(plainTextEdit.find(expression), "QPlainTextEdit.find(QRegExp) overload failed");
plainTextEdit.close();

// QColor equality and floating-point geometry expose value-type comparisons
// that can otherwise be hidden by the generated wrapper.
var sameColor = new QColor(12, 34, 56, 100);
check(color.equals(sameColor), "QColor equality conversion failed");
var rect = new QRectF(1.5, 2.5, 10.0, 20.0);
check(rect.contains(new QPointF(5.0, 10.0)) && !rect.contains(new QPointF(20.0, 10.0)),
      "QRectF containment semantics changed");

// QInputEvent now exposes its input device and device category. The generated
// compatibility shell supplies Qt's primary keyboard for deterministic tests.
var inputEvent = new QInputEvent(QEvent.KeyPress);
check(inputEvent.isInputEvent() && !inputEvent.isPointerEvent(),
      "QInputEvent category predicates are incorrect");
check(inputEvent.device() !== null, "QInputEvent did not expose its device");
check(inputEvent.deviceType().valueOf() === 0x1000,
      "QInputEvent deviceType was not reported as Keyboard");
inputEvent.setTimestamp(1234);
check(inputEvent.timestamp() === 1234, "QInputEvent timestamp conversion failed");
inputEvent.setModifiers(Qt.ShiftModifier);
check(inputEvent.modifiers().valueOf() === Qt.ShiftModifier.valueOf(),
      "QInputEvent modifier conversion failed");

// QMouseEvent is the main concrete single-point event used by widget code.
// Exercise the Qt 6 pointer hierarchy while keeping the test headless and
// independent of a live window system.
var mouseEvent = new QMouseEvent(QEvent.MouseButtonPress,
                                 new QPointF(10, 20),
                                 new QPointF(15, 25),
                                 new QPointF(30, 40),
                                 Qt.LeftButton, Qt.LeftButton, Qt.NoModifier);
check(mouseEvent.isInputEvent() && mouseEvent.isPointerEvent()
      && mouseEvent.isSinglePointEvent(),
      "QMouseEvent category predicates are incorrect");
check(mouseEvent.button().valueOf() === Qt.LeftButton.valueOf()
      && mouseEvent.buttons().valueOf() === Qt.LeftButton.valueOf(),
      "QMouseEvent button state was not preserved");
check(mouseEvent.position().x() === 10 && mouseEvent.position().y() === 20,
      "QMouseEvent local position was not exposed");
check(mouseEvent.globalPosition().x() === 30
      && mouseEvent.globalPosition().y() === 40
      && mouseEvent.scenePosition().x() === 15
      && mouseEvent.scenePosition().y() === 25,
      "QMouseEvent global/scene positions were not exposed");
check(mouseEvent.pointCount() === 1 && mouseEvent.isBeginEvent()
      && !mouseEvent.isUpdateEvent() && !mouseEvent.isEndEvent(),
      "QMouseEvent pointer lifecycle was not classified");
check(mouseEvent.device() !== null && mouseEvent.pointingDevice() !== null
      && mouseEvent.deviceType().valueOf() === 1,
      "QMouseEvent pointing device metadata was not exposed");

// QWheelEvent now uses pixel/angle deltas and an explicit scroll phase.  The
// old delta()/orientation() accessors remain useful compatibility shims and
// should agree with the native Qt 6 representation.
var wheelEvent = new QWheelEvent(new QPointF(1, 2), new QPointF(11, 12),
                                 new QPoint(0, 0), new QPoint(0, 120),
                                 Qt.NoButton, Qt.NoModifier, Qt.ScrollUpdate,
                                 false);
check(wheelEvent.isInputEvent() && wheelEvent.isPointerEvent()
      && wheelEvent.isSinglePointEvent() && wheelEvent.pointCount() === 1,
      "QWheelEvent category or point count is incorrect");
check(wheelEvent.position().x() === 1 && wheelEvent.position().y() === 2
      && wheelEvent.globalPosition().x() === 11
      && wheelEvent.globalPosition().y() === 12,
      "QWheelEvent positions were not exposed");
check(wheelEvent.angleDelta().y() === 120 && wheelEvent.delta() === 120
      && wheelEvent.orientation().valueOf() === Qt.Vertical.valueOf()
      && !wheelEvent.hasPixelDelta(),
      "QWheelEvent angle/delta compatibility is inconsistent");
check(wheelEvent.phase().valueOf() === Qt.ScrollUpdate.valueOf()
      && wheelEvent.isUpdateEvent() && !wheelEvent.isBeginEvent()
      && !wheelEvent.isEndEvent() && !wheelEvent.inverted()
      && wheelEvent.isInverted() === false,
      "QWheelEvent phase or inversion state is incorrect");
check(wheelEvent.device() !== null && wheelEvent.pointingDevice() !== null
      && wheelEvent.deviceType().valueOf() === 1,
      "QWheelEvent pointing device metadata was not exposed");

// Tablet events share the QSinglePointEvent lifecycle but carry pressure and
// tilt data.  Construct one with the primary pointing device so this remains
// deterministic on the offscreen platform.
var tabletEvent = new QTabletEvent(QEvent.TabletPress,
                                   new QPointF(2, 3), new QPointF(4, 5),
                                   0.5, 1, -2, 0.25, 15, 0.75,
                                   Qt.NoModifier, Qt.LeftButton, Qt.LeftButton);
check(tabletEvent.isInputEvent() && tabletEvent.isPointerEvent()
      && tabletEvent.isSinglePointEvent() && tabletEvent.pointCount() === 1,
      "QTabletEvent category or point count is incorrect");
check(tabletEvent.position().x() === 2 && tabletEvent.position().y() === 3
      && tabletEvent.globalPosition().x() === 4
      && tabletEvent.globalPosition().y() === 5,
      "QTabletEvent positions were not exposed");
check(tabletEvent.pressure() === 0.5 && tabletEvent.xTilt() === 1
      && tabletEvent.yTilt() === -2 && tabletEvent.tangentialPressure() === 0.25
      && tabletEvent.rotation() === 15 && tabletEvent.z() === 0.75,
      "QTabletEvent pressure/tilt data was not preserved");
check(tabletEvent.isBeginEvent() && !tabletEvent.isUpdateEvent()
      && !tabletEvent.isEndEvent() && tabletEvent.device() !== null
      && tabletEvent.pointingDevice() !== null,
      "QTabletEvent lifecycle or device metadata is incorrect");

// QEventPoint and QPointerEvent are the Qt 6 value/event pair behind touch,
// tablet and other pointer input.  Build a synthetic point/event so the
// binding is exercised without relying on a platform touch device.
var eventPoint = new QEventPoint(7, QEventPoint.Pressed,
                                 new QPointF(10, 20), new QPointF(30, 40));
check(eventPoint.id() === 7
      && eventPoint.state().valueOf() === QEventPoint.Pressed.valueOf()
      && eventPoint.scenePosition().x() === 10 && eventPoint.scenePosition().y() === 20
      && eventPoint.globalPosition().x() === 30
      && eventPoint.globalPosition().y() === 40,
      "QEventPoint construction or positions were not preserved: id="
      + eventPoint.id() + " state=" + eventPoint.state()
      + " scene=" + eventPoint.scenePosition().x() + "," + eventPoint.scenePosition().y()
      + " global=" + eventPoint.globalPosition().x() + ","
      + eventPoint.globalPosition().y());
check(eventPoint.scenePos().x() === eventPoint.scenePosition().x()
      && eventPoint.screenPos().y() === eventPoint.globalPosition().y(),
      "QEventPoint legacy position aliases are inconsistent");
check(eventPoint.isAccepted() === false || eventPoint.isAccepted() === true,
      "QEventPoint acceptance accessor did not return a boolean");
eventPoint.setAccepted(true);
check(eventPoint.isAccepted(), "QEventPoint setAccepted(true) failed");
eventPoint.setAccepted(false);
check(!eventPoint.isAccepted(), "QEventPoint setAccepted(false) failed");
eventPoint.setAccepted();
check(eventPoint.isAccepted(), "QEventPoint setAccepted() failed");

var pointerEvent = new QPointerEvent(QEvent.TouchBegin, [eventPoint]);
check(pointerEvent.isInputEvent() && pointerEvent.isPointerEvent()
      && pointerEvent.pointCount() === 1
      && pointerEvent.points().length === 1,
      "QPointerEvent hierarchy or point list is incorrect");
check(pointerEvent.point(0).id() === 7
      && pointerEvent.pointById(7).scenePosition().x() === 10
      && pointerEvent.pointById(99) === null,
      "QPointerEvent point lookup did not preserve point identity");
check(pointerEvent.pointingDevice() !== null
      && pointerEvent.pointerType().valueOf() === 1,
      "QPointerEvent pointing-device metadata is incorrect");
check(pointerEvent.allPointsAccepted() && !pointerEvent.allPointsGrabbed()
      && !pointerEvent.isBeginEvent() && !pointerEvent.isUpdateEvent()
      && !pointerEvent.isEndEvent(),
      "QPointerEvent base lifecycle or acceptance state is incorrect");
pointerEvent.setTimestamp(5678);
check(pointerEvent.timestamp() === 5678, "QPointerEvent timestamp failed");
pointerEvent.setAccepted(false);
check(!pointerEvent.isAccepted(), "QPointerEvent setAccepted(false) failed");
pointerEvent.setAccepted(true);

print("GUI regression smoke passed");
