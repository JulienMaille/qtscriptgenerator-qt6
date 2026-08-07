function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

function contains(list, value) {
    for (var i = 0; i < list.length; ++i) {
        if (list[i] === value)
            return true;
    }
    return false;
}

check(typeof QUiLoader === "function", "QUiLoader binding was not imported");

var loader = new QUiLoader();
check(contains(loader.availableWidgets(), "QWidget"),
      "QUiLoader does not advertise QWidget");
check(contains(loader.availableLayouts(), "QVBoxLayout"),
      "QUiLoader does not advertise QVBoxLayout");

loader.setLanguageChangeEnabled(true);
loader.setTranslationEnabled(false);
check(loader.isLanguageChangeEnabled(), "language-change option failed");
check(!loader.isTranslationEnabled(), "translation option failed");

var ui = '<?xml version="1.0" encoding="UTF-8"?>' +
    '<ui version="4.0">' +
    '<class>Qt6UiToolsSmoke</class>' +
    '<widget class="QWidget" name="uiToolsRoot">' +
    '<property name="accessibleIdentifier"><string>qt6LoadedRoot</string></property>' +
    '<property name="windowTitle"><string>Qt 6 UI Tools</string></property>' +
    '<layout class="QVBoxLayout" name="verticalLayout">' +
    '<item><widget class="QLabel" name="messageLabel">' +
    '<property name="text"><string>Loaded from memory</string></property>' +
    '</widget></item>' +
    '<item><widget class="QPushButton" name="actionButton">' +
    '<property name="text"><string>Activate</string></property>' +
    '</widget></item>' +
    '</layout>' +
    '</widget>' +
    '<resources/><connections/>' +
    '</ui>';

var buffer = new QBuffer();
buffer.setData(new QByteArray(ui));
check(buffer.open(new QIODevice.OpenMode(QIODevice.ReadOnly)),
      "opening the in-memory UI buffer failed");

var root = loader.load(buffer);
check(root !== null, "loading the UI failed: " + loader.errorString());
check(root.objectName === "uiToolsRoot", "loaded root object name is invalid");
check(root.windowTitle === "Qt 6 UI Tools", "loaded window title is invalid");
check(root.accessibleIdentifier === "qt6LoadedRoot",
      "Qt 6 accessibleIdentifier was not loaded");

var children = root.children();
var label = null;
var button = null;
for (var i = 0; i < children.length; ++i) {
    if (children[i].objectName === "messageLabel")
        label = children[i];
    else if (children[i].objectName === "actionButton")
        button = children[i];
}
check(label !== null && label.text === "Loaded from memory",
      "loaded QLabel is missing or invalid");
check(button !== null && button.text === "Activate",
      "loaded QPushButton is missing or invalid");

buffer.close();
root.close();

