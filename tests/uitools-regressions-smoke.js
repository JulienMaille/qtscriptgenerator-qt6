function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

var loader = new QUiLoader();
var root = new QWidget();
var dynamicLabel = loader.createWidget("QLabel", root, "dynamicLabel");
check(dynamicLabel !== null && dynamicLabel.objectName === "dynamicLabel",
      "QUiLoader.createWidget did not create a named QLabel");
dynamicLabel.text = "created by loader";
check(dynamicLabel.text === "created by loader",
      "dynamically created widget property bridge failed");

var dynamicLayout = loader.createLayout("QVBoxLayout", root, "dynamicLayout");
check(dynamicLayout !== null && dynamicLayout.objectName === "dynamicLayout",
      "QUiLoader.createLayout did not create a named layout");
// Layout population is covered by the XML-loader smoke test; keep this case
// focused on the factory's object/type/name bridge.

// Invalid XML must fail with a useful loader error rather than returning a
// partially initialized widget tree.
var invalid = new QBuffer();
invalid.setData(new QByteArray("<ui><widget class='QWidget'>"));
check(invalid.open(new QIODevice.OpenMode(QIODevice.ReadOnly)),
      "invalid UI buffer could not be opened");
var failed = loader.load(invalid);
check(failed === null || typeof failed === "undefined",
      "QUiLoader accepted malformed XML");
check(loader.errorString().length > 0, "QUiLoader did not report malformed XML");
invalid.close();
root.close();
print("UI Tools regression smoke passed");
