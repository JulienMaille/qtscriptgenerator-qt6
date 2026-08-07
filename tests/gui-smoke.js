function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

check(typeof QColor === "function", "QColor binding was not imported");
check(typeof QFont === "function", "QFont binding was not imported");
check(typeof QTransform === "function", "QTransform binding was not imported");
check(typeof QImage === "function", "QImage binding was not imported");
check(typeof QPainterPath === "function", "QPainterPath binding was not imported");
check(typeof QTextDocument === "function", "QTextDocument binding was not imported");

var color = new QColor(10, 20, 30, 40);
check(color.red() === 10 && color.green() === 20 && color.blue() === 30,
      "QColor channel conversion failed");
check(color.alpha() === 40, "QColor alpha conversion failed");

var font = new QFont("Sans Serif", 11);
font.setWeight(QFont.Bold);
check(font.weight() == QFont.Bold,
      "QFont weight conversion failed: expected " + QFont.Bold +
      ", got " + font.weight());
check(QFont.PreferTypoLineMetrics !== undefined,
      "Qt 6 QFont.PreferTypoLineMetrics was not exported");

var transform = new QTransform();
transform.translate(5, 7);
var mapped = transform.map(new QPoint(2, 3));
check(mapped.x() === 7 && mapped.y() === 10, "QTransform mapping failed");

check(typeof QMatrix === "function", "legacy QMatrix compatibility binding is missing");
var matrix = new QMatrix(1, 0, 0, 1, 4, 6);
mapped = matrix.map(new QPoint(1, 2));
check(mapped.x() === 5 && mapped.y() === 8, "QMatrix compatibility mapping failed");

var image = new QImage(16, 12, QImage.Format_ARGB32);
image.fill(color.rgba());
check(image.width() === 16 && image.height() === 12, "QImage construction failed");
check(image.byteCount() > 0, "QImage byteCount compatibility failed");

var path = new QPainterPath();
path.addRoundRect(new QRectF(0, 0, 20, 10), 25);
check(!path.isEmpty(), "QPainterPath rounded rectangle compatibility failed");

var document = new QTextDocument();
document.setPlainText("Qt 6 GUI binding");
check(!document.find("GUI").isNull(), "QTextDocument find failed");
check(document.toHtml("UTF-8").indexOf("Qt 6 GUI binding") !== -1,
      "QTextDocument legacy codec overload failed");

check(QPainter.LosslessImageRendering !== undefined,
      "Qt 6 QPainter.LosslessImageRendering was not exported");
check(typeof QPictureIO === "undefined", "removed QPictureIO must not be exported");
check(typeof QRegExpValidator === "undefined",
      "removed QRegExpValidator must not be exported");
