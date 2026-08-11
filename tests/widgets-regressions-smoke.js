function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

// Model/view data is a more meaningful widget smoke test than construction:
// it crosses QModelIndex, QVariant, and generated non-QObject wrappers.
var host = new QWidget();
var model = new QStandardItemModel(2, 2, host);
model.setHorizontalHeaderLabels(["Name", "Score"]);
var first = new QStandardItem("alpha");
first.setCheckable(true);
first.setCheckState(Qt.Checked);
model.setItem(0, 0, first);
model.setItem(0, 1, new QStandardItem("7"));
var matches = model.findItems("alpha", Qt.MatchExactly, 0);
check(matches.length === 1 && matches[0].text() === "alpha",
      "QStandardItemModel findItems did not return the expected item");
check(model.item(0, 0).checkState().valueOf() === Qt.Checked.valueOf(),
      "QStandardItem check-state conversion failed");
check(model.indexFromItem(first).row() === 0 && model.indexFromItem(first).column() === 0,
      "QStandardItemModel indexFromItem returned the wrong index");

var combo = new QComboBox(host);
combo.addItem("one", 11);
combo.addItem("two", 22);
check(combo.count === 2 && combo.findData(22) === 1,
      "QComboBox item-data lookup failed");
combo.setCurrentIndex(1);
check(combo.currentText === "two" && combo.itemData(1) === 22,
      "QComboBox current item/data conversion failed");

var spin = new QSpinBox(host);
spin.setRange(2, 9);
spin.setValue(4);
var observed = 0;
function onValueChanged(value) { observed = value; }
spin.valueChanged.connect(onValueChanged);
spin.setValue(8);
check(spin.value === 8 && observed === 8,
      "QSpinBox value or typed signal bridge failed");
spin.valueChanged.disconnect(onValueChanged);

// Consumer scripts combine QFileDialog flags before passing them to static
// helpers. Exercise the same flag conversion and non-modal object API without
// opening an interactive dialog in headless CI.
var dialog = new QFileDialog();
dialog.setOption(QFileDialog.DontUseNativeDialog, true);
dialog.setOption(QFileDialog.ShowDirsOnly, true);
check(dialog.testOption(QFileDialog.DontUseNativeDialog),
      "QFileDialog DontUseNativeDialog option was not preserved");
check(dialog.testOption(QFileDialog.ShowDirsOnly),
      "QFileDialog ShowDirsOnly option was not preserved");
var options = new QFileDialog.Options(
    QFileDialog.DontUseNativeDialog | QFileDialog.ShowDirsOnly);
check(options.valueOf() !== 0, "QFileDialog.Options conversion lost flags");
dialog.setNameFilters(["CSV files (*.csv)", "All files (*)"]);
check(dialog.nameFilters().length === 2,
      "QFileDialog name-filter sequence conversion failed");
dialog.selectFile("sample-export.csv");
check(dialog.selectedFiles().length === 1
      && dialog.selectedFiles()[0].indexOf("sample-export.csv") !== -1,
      "QFileDialog selected-files conversion failed");
dialog.close();

// QApplication is intentionally a static-only facade: qs_eval already owns
// the process application and scripts must use qApp for the instance.
check(typeof QApplication === "function", "QApplication binding was not imported");
check(QApplication.style() !== null, "QApplication.style() returned no style");
check(QApplication.font().family().length > 0, "QApplication.font() returned no family");
check(QApplication.font("QWidget").family().length > 0,
      "QApplication.font(className) overload failed");
check(QApplication.palette() !== null, "QApplication.palette() returned no palette");
check(QApplication.palette("QWidget") !== null,
      "QApplication.palette(className) overload failed");
var allWidgets = QApplication.allWidgets();
var topLevelWidgets = QApplication.topLevelWidgets();
check(allWidgets.length >= 1 && topLevelWidgets.length >= 1,
      "QApplication widget-list conversion returned no widgets");
var flashTime = QApplication.cursorFlashTime();
QApplication.setCursorFlashTime(flashTime);
var dragDistance = QApplication.startDragDistance();
var dragTime = QApplication.startDragTime();
check(dragDistance > 0 && dragTime > 0,
      "QApplication drag configuration returned invalid values");

// QDateTimeEdit gained a QTimeZone property in Qt 6.  Use the UTC value type
// so this stays deterministic on machines with different local zones.
var dateTimeEdit = new QDateTimeEdit(host);
dateTimeEdit.setTimeZone(QTimeZone.utc());
check(dateTimeEdit.timeZone.id() === "UTC",
      "QDateTimeEdit QTimeZone property did not round-trip");
dateTimeEdit.close();

// Parent every widget to one host and explicitly close it so this test does
// not leave a top-level window behind in headless CI.
host.close();
print("Widgets regression smoke passed");
