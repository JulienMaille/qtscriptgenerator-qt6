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

// QColor equality and floating-point geometry expose value-type comparisons
// that can otherwise be hidden by the generated wrapper.
var sameColor = new QColor(12, 34, 56, 100);
check(color.equals(sameColor), "QColor equality conversion failed");
var rect = new QRectF(1.5, 2.5, 10.0, 20.0);
check(rect.contains(new QPointF(5.0, 10.0)) && !rect.contains(new QPointF(20.0, 10.0)),
      "QRectF containment semantics changed");

print("GUI regression smoke passed");
