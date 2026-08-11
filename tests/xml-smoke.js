function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

check(typeof QDomDocument === "function", "QDomDocument binding was not imported");
check(typeof QDomElement === "function" && typeof QDomNode === "function",
      "Qt XML DOM bindings were not imported");
check(typeof QtXml === "object" && typeof QtXml.ParseOption === "function" &&
      typeof QtXml.ParseOptions === "function", "QtXml parse API was not imported");
check(QtXml.UseNamespaceProcessing.valueOf() === 1 &&
      QtXml.PreserveSpacingOnlyNodes.valueOf() === 2,
      "QtXml parse option values were not exported");
check(QDomDocument.UseNamespaceProcessing.valueOf() === 1 &&
      QDomDocument.ParseOption.UseNamespaceProcessing.valueOf() === 1,
      "QDomDocument nested ParseOption aliases are missing");

var source = '<root id="r1"><item id="one">alpha</item>' +
             '<item id="two"><child/></item></root>';
var document = new QDomDocument("smoke");
var result = document.setContent(new QByteArray(source));
check(result.ok && result.errorMessage === "" && result.errorLine === 0,
      "QDomDocument QByteArray parsing failed");

var root = document.documentElement();
check(root.isElement() && root.tagName() === "root" && root.attribute("id", "") === "r1",
      "QDomElement root or attribute conversion failed");
var items = root.elementsByTagName("item");
check(items.length() === 2 && items.item(0).toElement().text() === "alpha",
      "QDomNodeList traversal or text conversion failed");
check(root.attributes().contains("id") && root.attributes().length() === 1,
      "QDomNamedNodeMap attribute lookup failed");

var added = document.createElement("added");
added.setAttribute("value", 42);
added.appendChild(document.createTextNode("payload"));
root.appendChild(added);
var clone = added.cloneNode(true).toElement();
clone.setAttribute("value", "43");
root.appendChild(clone);
check(root.elementsByTagName("added").length() === 2 &&
      root.lastChildElement().attribute("value", "") === "43",
      "DOM creation, cloning, or appendChild failed");

var imported = document.importNode(items.item(0), true);
check(imported.toElement().attribute("id", "") === "one",
      "QDomDocument.importNode failed");
root.appendChild(imported);
check(root.elementsByTagName("item").length() === 3,
      "imported node was not attached to the document");
check(document.toString(0).indexOf("<added value=\"42\">") !== -1 &&
      document.toByteArray(0).toString().indexOf("<root") !== -1,
      "DOM serialization failed");

var namespaceDocument = new QDomDocument();
var namespaceOptions = new QtXml.ParseOptions(QtXml.UseNamespaceProcessing);
var namespaceResult = namespaceDocument.setContent(
    '<x:root xmlns:x="urn:example"><x:item code="7"/></x:root>', namespaceOptions);
check(namespaceResult.ok, "namespace-aware parsing failed");
var namespaceItem = namespaceDocument.documentElement().elementsByTagNameNS(
    "urn:example", "item").item(0).toElement();
check(namespaceItem.namespaceURI() === "urn:example" && namespaceItem.localName() === "item",
      "namespace-aware DOM lookup failed");
check(new QtXml.ParseOptions(QtXml.PreserveSpacingOnlyNodes).toString() ===
      "PreserveSpacingOnlyNodes", "ParseOptions string conversion failed");

var device = new QBuffer();
device.setData(new QByteArray("<device><value>8</value></device>"));
check(device.open(new QIODevice.OpenMode(QIODevice.ReadOnly)), "QBuffer open failed");
var deviceDocument = new QDomDocument();
check(deviceDocument.setContent(device).ok &&
      deviceDocument.documentElement().tagName() === "device",
      "QIODevice parsing failed");
device.close();

var readerDocument = new QDomDocument();
var reader = new QXmlStreamReader(new QByteArray("<stream><value/></stream>"));
check(readerDocument.setContent(reader).ok &&
      readerDocument.documentElement().tagName() === "stream",
      "QXmlStreamReader parsing failed");

var malformed = new QDomDocument();
var malformedResult = malformed.setContent(new QByteArray("<broken><child></broken>"));
check(!malformedResult.ok && malformedResult.errorMessage.length > 0 &&
      malformedResult.errorLine > 0 && malformedResult.errorColumn > 0,
      "malformed XML diagnostics were not returned");

print("Qt XML DOM smoke test passed");
