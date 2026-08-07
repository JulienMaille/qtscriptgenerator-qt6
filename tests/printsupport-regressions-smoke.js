function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

var outputFile = QDir.tempPath() + "/qtscriptgenerator-qt6-printsupport-regression.pdf";
QFile.remove(outputFile);
var printer = new QPrinter(QPrinter.ScreenResolution);
printer.setOutputFormat(QPrinter.PdfFormat);
printer.setOutputFileName(outputFile);
printer.setPageSizeMM(new QSizeF(80, 120));
printer.setPageMargins(4, 5, 6, 7, QPrinter.Millimeter);
printer.setFullPage(false);
printer.setColorMode(QPrinter.GrayScale);
printer.setResolution(144);

check(printer.isValid(), "configured PDF printer is not valid");
check(printer.resolution() === 144, "QPrinter resolution did not round-trip");
check(printer.colorMode().valueOf() === QPrinter.GrayScale.valueOf(),
      "QPrinter color mode enum did not round-trip");
var pageRect = printer.pageRect(QPrinter.Millimeter);
check(pageRect.width() > 0 && pageRect.height() > 0,
      "QPrinter pageRect returned an empty page");

var painter = new QPainter();
check(painter.begin(printer), "QPainter could not begin configured PDF output");
painter.drawLine(0, 0, 30, 30);
painter.drawText(5, 50, "QtScript PrintSupport regression");
check(painter.end(), "QPainter could not finish configured PDF output");

var info = new QFileInfo(outputFile);
check(info.exists() && info.size() > 512, "configured PDF output is unexpectedly small");
check(QFile.remove(outputFile), "PrintSupport regression PDF could not be removed");
print("PrintSupport regression smoke passed");
