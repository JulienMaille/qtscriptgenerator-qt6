function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

check(typeof QPrinter === "function", "QPrinter was not exported");
check(typeof QPrintDialog === "function", "QPrintDialog was not exported");

var outputFile = QDir.tempPath() + "/qtscriptgenerator-qt6-printsupport-smoke.pdf";
QFile.remove(outputFile);

var printer = new QPrinter(QPrinter.HighResolution);
printer.setOutputFormat(QPrinter.PdfFormat);
printer.setOutputFileName(outputFile);
printer.setDocName("QtScript PrintSupport smoke test");
printer.setCreator("qtscriptgenerator-qt6");
printer.setCopyCount(2);
printer.setOrientation(QPrinter.Landscape);
printer.setPageSizeMM(new QSizeF(100, 150));

check(printer.outputFormat().valueOf() === QPrinter.PdfFormat.valueOf(),
      "PDF output format was not retained");
check(printer.copyCount() === 2, "copyCount did not round-trip");
check(printer.numCopies() === 2, "Qt 5 numCopies compatibility adapter failed");
check(printer.orientation().valueOf() === QPrinter.Landscape.valueOf(),
      "orientation did not round-trip");

var dialog = new QPrintDialog(printer);
dialog.setOption(QAbstractPrintDialog.PrintSelection, true);
check(dialog.testOption(QAbstractPrintDialog.PrintSelection),
      "print-dialog option did not round-trip");
check(dialog.isOptionEnabled(QAbstractPrintDialog.PrintSelection),
      "Qt 5 isOptionEnabled compatibility adapter failed");

var painter = new QPainter();
check(painter.begin(printer), "QPainter could not begin PDF output");
painter.drawText(20, 40, "QtScript PrintSupport on Qt 6");
check(painter.end(), "QPainter could not finish PDF output");

var info = new QFileInfo(outputFile);
check(info.exists(), "PDF output was not created");
check(info.size() > 0, "PDF output is empty");
check(QFile.remove(outputFile), "temporary PDF could not be removed");

print("PrintSupport smoke test passed");
