function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

check(typeof QDate === "function", "QDate binding was not imported");
var leapDay = new QDate(2024, 2, 29);
check(leapDay.isValid(), "QDate constructor or isValid failed");
check(leapDay.day() === 29 && leapDay.month() === 2, "QDate accessors failed");

check(typeof QByteArray === "function", "QByteArray binding was not imported");
var bytes = new QByteArray("sample");
check(bytes.size() === 6, "QByteArray construction failed");
check(bytes.toString() === "sample", "QByteArray conversion failed");

check(typeof QRegExp === "function", "QRegExp compatibility binding was not imported");
var expression = new QRegExp("s.*e");
check(expression.exactMatch("sample"), "QRegExp compatibility failed");

check(typeof QTextCodec === "undefined" && typeof QTextDecoder === "undefined"
      && typeof QTextEncoder === "undefined", "removed codec facades must not be exported");
check(typeof QStringConverter === "object", "native encoding enum was not imported");
var utf8 = new QStringConverter.Encoding(0);
check(utf8.valueOf() === QStringConverter.Utf8.valueOf() && utf8.toString() === "Utf8",
      "QStringConverter.Encoding construction failed");
var encodedBuffer = new QBuffer();
check(encodedBuffer.open(new QIODevice.OpenMode(QIODevice.ReadWrite)), "encoding buffer open failed");
var encodedStream = new QTextStream(encodedBuffer);
check(encodedStream.encoding().valueOf() === QStringConverter.Utf8.valueOf(),
      "QTextStream default encoding must be UTF-8");
check(typeof encodedStream.codec === "undefined" && typeof encodedStream.setCodec === "undefined",
      "QTextStream must expose native encoding APIs, not codec shims");
encodedStream.setEncoding(utf8);
encodedStream.writeString("caf\u00e9");
encodedStream.flush();
check(encodedBuffer.seek(0) && encodedBuffer.readAll().toHex().toString() === "636166c3a9",
      "native UTF-8 write failed or unexpectedly emitted a BOM");
check(encodedStream.seek(0) && encodedStream.readAll() === "caf\u00e9", "UTF-8 stream round trip failed");
encodedBuffer.close();

check(typeof QXmlStreamReader === "function", "QXmlStreamReader binding was not imported");
var reader = new QXmlStreamReader("<root>value</root>");
check(reader.readNextStartElement(), "QXmlStreamReader failed to find the root element");
check(reader.name() === "root", "QStringView XML result was not converted to a script string");

check(Qt.BackgroundColorRole.valueOf() === 8,
      "legacy Qt enum alias was not preserved");
