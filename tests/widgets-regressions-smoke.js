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

// Parent every widget to one host and explicitly close it so this test does
// not leave a top-level window behind in headless CI.
host.close();
print("Widgets regression smoke passed");
