function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

check(typeof QWidget === "function", "QWidget binding was not imported");
check(typeof QVBoxLayout === "function", "QVBoxLayout binding was not imported");
check(typeof QLabel === "function", "QLabel binding was not imported");
check(typeof QPushButton === "function", "QPushButton binding was not imported");

var window = new QWidget();
window.objectName = "widgetsSmokeWindow";
window.resize(320, 120);

var layout = new QVBoxLayout(window);
var label = new QLabel("Qt 6 widget binding", window);
var button = new QPushButton("Activate", window);
layout.addWidget(label, 0, new Qt.Alignment());
layout.addWidget(button, 0, new Qt.Alignment());

check(window.objectName === "widgetsSmokeWindow", "QObject property bridge failed");
check(label.text === "Qt 6 widget binding", "QLabel property bridge failed");
check(layout.count() === 2, "QLayout method dispatch failed");
check(window.width === 320 && window.height === 120,
      "QWidget resize or QSize conversion failed");

var clickCount = 0;
function onClicked() { ++clickCount; }
button.clicked.connect(onClicked);
button.click();
check(clickCount === 1, "QPushButton signal bridge failed");
button.clicked.disconnect(onClicked);

window.close();
