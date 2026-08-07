function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

check(typeof QDate === "function", "QDate binding was not imported");
var leapDay = new QDate(2024, 2, 29);
check(leapDay.isValid(), "QDate constructor or isValid failed");
check(leapDay.day() === 29 && leapDay.month() === 2, "QDate accessors failed");

check(typeof QByteArray === "function", "QByteArray binding was not imported");
var bytes = new QByteArray("blink");
check(bytes.size() === 5, "QByteArray construction failed");
check(bytes.toString() === "blink", "QByteArray conversion failed");

check(typeof QRegExp === "function", "QRegExp compatibility binding was not imported");
var expression = new QRegExp("b.*k");
check(expression.exactMatch("blink"), "QRegExp compatibility failed");

check(typeof QTextCodec === "function", "QTextCodec facade was not imported");
var utf8 = QTextCodec.codecForName(new QByteArray("UTF-8"));
check(utf8 !== null, "UTF-8 codec lookup failed");
var encodedText = utf8.fromUnicode("caf\u00e9");
check(utf8.toUnicode(encodedText) === "caf\u00e9", "UTF-8 codec round trip failed");
var encoder = utf8.makeEncoder();
var decoder = utf8.makeDecoder();
check(decoder.toUnicode(encoder.fromUnicode("streamed")) === "streamed",
      "QTextEncoder/QTextDecoder facade round trip failed");

check(typeof QXmlStreamReader === "function", "QXmlStreamReader binding was not imported");
var reader = new QXmlStreamReader("<root>value</root>");
check(reader.readNextStartElement(), "QXmlStreamReader failed to find the root element");
check(reader.name() === "root", "QStringView XML result was not converted to a script string");

check(Qt.BackgroundColorRole.valueOf() === 8,
      "legacy Qt enum alias was not preserved");
