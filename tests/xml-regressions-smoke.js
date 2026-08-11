function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

// Qt 6 removed the QXmlReader/QXmlInputSource SAX surface. The DOM plugin
// must not accidentally publish those stale classes while retaining stream
// parsing through QtCore.
var removed = ["QXmlReader", "QXmlInputSource", "QXmlSimpleReader",
               "QXmlDefaultHandler", "QXmlContentHandler"];
for (var i = 0; i < removed.length; ++i)
    check(typeof this[removed[i]] === "undefined",
          removed[i] + " was unexpectedly exported by QtXml");
check(typeof QXmlStreamReader === "function", "QtCore QXmlStreamReader disappeared");

// Keep the two Qt 6 parse flags composable and reject arbitrary option types.
var options = new QtXml.ParseOptions(QtXml.UseNamespaceProcessing,
                                     QtXml.PreserveSpacingOnlyNodes);
check(options.valueOf() === 3 && options.equals(new QtXml.ParseOptions(3)),
      "QtXml.ParseOptions flags did not compose");
var doc = new QDomDocument();
var parsed = doc.setContent("<r>  <x/>  </r>", options);
check(parsed.ok, "combined Qt 6 parse options failed");
var invalidOptionsRaised = false;
try {
    doc.setContent("<r/>", "not-options");
} catch (error) {
    invalidOptionsRaised = true;
}
check(invalidOptionsRaised, "invalid QDomDocument ParseOptions were accepted");

// A failed parse returns diagnostics without corrupting the existing tree.
var failure = doc.setContent("<r><unclosed></r>");
check(!failure.ok && doc.documentElement().tagName() === "r",
      "failed setContent corrupted the existing DOM: ok=" + failure.ok +
      ", root=" + doc.documentElement().tagName());

// Namespaced lookup must distinguish local names from qualified names.
var namespaced = new QDomDocument();
check(namespaced.setContent("<a:root xmlns:a='urn:a'><a:item/><item/></a:root>",
                            QtXml.UseNamespaceProcessing).ok,
      "namespace option compatibility failed");
check(namespaced.documentElement().elementsByTagName("item").length() === 2 &&
      namespaced.documentElement().elementsByTagNameNS("urn:a", "item").length() === 1,
      "namespace filtering returned the wrong nodes");

print("Qt XML DOM regression smoke test passed");
