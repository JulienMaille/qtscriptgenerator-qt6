function check(condition, message) {
    if (!condition) throw new Error(message);
}
function checkThrows(action, message) {
    var threw = false;
    try { action(); } catch (error) { threw = true; }
    check(threw, message);
}

// Check exact bytes as well as decoding: symmetric conversion bugs can hide
// in round trips, especially for byte order and supplementary characters.
function checkEncoding(encoding, text, hex, bom) {
    var bytes = new QBuffer();
    check(bytes.open(new QIODevice.OpenMode(QIODevice.ReadWrite)), "encoding buffer open");
    var stream = new QTextStream(bytes);
    stream.setEncoding(encoding);
    stream.setGenerateByteOrderMark(bom);
    stream.writeString(text);
    stream.flush();
    check(bytes.seek(0) && bytes.readAll().toHex().toString() === hex, "wrong encoded bytes for " + encoding);
    check(stream.status().valueOf() === QTextStream.Ok.valueOf(), "encoding write status");
    check(stream.encoding().valueOf() === encoding.valueOf(), "encoding getter lost enum type");
    check(stream.seek(0), "encoding stream seek");
    stream.setAutoDetectUnicode(bom);
    check(stream.readAll() === text, "encoding read round trip for " + encoding);
    bytes.close();
}
var unicodeText = "A\u00e9\u03a9\ud83d\ude00";
checkEncoding(QStringConverter.Utf8, unicodeText, "41c3a9cea9f09f9880", false);
checkEncoding(QStringConverter.Utf16LE, unicodeText, "4100e900a9033dd800de", false);
checkEncoding(QStringConverter.Utf16BE, unicodeText, "004100e903a9d83dde00", false);
checkEncoding(QStringConverter.Utf32LE, unicodeText, "41000000e9000000a903000000f60100", false);
checkEncoding(QStringConverter.Utf32BE, unicodeText, "00000041000000e9000003a90001f600", false);
checkEncoding(QStringConverter.Latin1, "caf\u00e9", "636166e9", false);
checkEncoding(QStringConverter.Utf8, unicodeText, "efbbbf41c3a9cea9f09f9880", true);
checkEncoding(QStringConverter.Utf16LE, unicodeText, "fffe4100e900a9033dd800de", true);

var bomBuffer = new QBuffer();
bomBuffer.setData(QByteArray.fromHex(new QByteArray("feff004100e903a9d83dde00")));
check(bomBuffer.open(new QIODevice.OpenMode(QIODevice.ReadOnly)), "BOM input buffer open");
var bomReader = new QTextStream(bomBuffer);
check(bomReader.autoDetectUnicode() && bomReader.readAll() === unicodeText,
      "UTF-16BE BOM autodetection failed with the default UTF-8 encoding");
bomBuffer.close();

var encodingProbe = new QTextStream();
var encodings = [QStringConverter.Utf8, QStringConverter.Utf16, QStringConverter.Utf16LE,
    QStringConverter.Utf16BE, QStringConverter.Utf32, QStringConverter.Utf32LE,
    QStringConverter.Utf32BE, QStringConverter.Latin1, QStringConverter.System];
for (var encodingIndex = 0; encodingIndex < encodings.length; ++encodingIndex) {
    encodingProbe.setEncoding(encodings[encodingIndex]);
    check(encodingProbe.encoding().valueOf() === encodings[encodingIndex].valueOf(), "encoding enum selection");
}
encodingProbe.setEncoding(QStringConverter.Utf8.valueOf());
var typedEncoding = new QStringConverter.Encoding(QStringConverter.Utf16LE.valueOf());
typedEncoding.valueOf = function () { return QStringConverter.Utf8.valueOf(); };
encodingProbe.setEncoding(typedEncoding);
check(encodingProbe.encoding().valueOf() === QStringConverter.Utf16LE.valueOf(),
      "setEncoding used a script valueOf override instead of the typed enum");
encodingProbe.setEncoding(QStringConverter.Utf8);
var invalidEncodings = [-1, 99, 0.5, NaN, Infinity, undefined, null, true, "UTF-8", {}, QTextStream.Ok];
for (var invalidIndex = 0; invalidIndex < invalidEncodings.length; ++invalidIndex) {
    var invalidEncoding = invalidEncodings[invalidIndex];
    checkThrows(function () { encodingProbe.setEncoding(invalidEncoding); }, "invalid encoding accepted");
    check(encodingProbe.encoding().valueOf() === QStringConverter.Utf8.valueOf(), "invalid encoding mutated stream");
}
checkThrows(function () { encodingProbe.setEncoding(); }, "missing encoding accepted");
checkThrows(function () { encodingProbe.setEncoding(0, 1); }, "extra encoding argument accepted");
checkThrows(function () { new QStringConverter.Encoding(-1); }, "invalid encoding enum accepted");
checkThrows(function () { new QStringConverter.Encoding("UTF-8"); }, "string encoding enum accepted");

// With codec selection gone, XML output must still be UTF-8 and escaped.
var xmlBuffer = new QBuffer();
check(xmlBuffer.open(new QIODevice.OpenMode(QIODevice.ReadWrite)), "XML output buffer open");
var xmlWriter = new QXmlStreamWriter(xmlBuffer);
check(typeof xmlWriter.codec === "undefined" && typeof xmlWriter.setCodec === "undefined",
      "XML codec shims remain exported");
xmlWriter.setAutoFormatting(false);
xmlWriter.writeStartDocument();
xmlWriter.writeTextElement("root", "caf\u00e9 & <tag>");
xmlWriter.writeEndDocument();
check(!xmlWriter.hasError(), "UTF-8 XML writer error");
check(xmlBuffer.seek(0), "XML output seek");
var xmlBytes = xmlBuffer.readAll();
check(xmlBytes.toHex().toString().indexOf("636166c3a9") !== -1, "XML not UTF-8");
check(xmlBytes.toString().indexOf("&amp; &lt;tag&gt;") !== -1, "XML not escaped");
check(xmlBuffer.seek(0), "XML buffer seek");
var xmlReader = new QXmlStreamReader(xmlBuffer);
check(xmlReader.readNextStartElement() && xmlReader.readElementText() === "caf\u00e9 & <tag>",
      "UTF-8 XML device round trip failed");
xmlBuffer.close();
var instant = new QDateTime(new QDate(2024, 2, 29), new QTime(23, 59, 58), Qt.UTC);
check(instant.isValid(), "instant");
var next = instant.addSecs(2);
check(next.date().year() === 2024 && next.date().month() === 3
      && next.date().day() === 1 && next.time().second() === 0, "calendar");
check(next.toMSecsSinceEpoch() - instant.toMSecsSinceEpoch() === 2000, "msecs");
check(next.toUTC().timeSpec().valueOf() === Qt.UTC.valueOf(), "utc");
var url = new QUrl("https://user:secret@example.invalid:8443/a%20b?old=1#part");
check(url.isValid() && url.scheme() === "https", "url");
check(url.host() === "example.invalid", "url host conversion failed");
check(url.port() === 8443 && url.hasQuery() && url.hasFragment(), "url state");
url.setQuery("first=1&second=two");
url.setFragment("updated");
check(url.toString().indexOf("first=1&second=two") !== -1
      && url.fragment() === "updated", "url mutate");

// QIODevice buffering and seeking catch regressions in QByteArray/QVariant
// conversion without depending on the filesystem or a network service.
var buffer = new QBuffer();
buffer.setData(new QByteArray("alpha\nbeta"));
check(buffer.open(new QIODevice.OpenMode(QIODevice.ReadOnly)),
      "QBuffer could not be opened for reading");
check(buffer.read(5).toString() === "alpha", "QBuffer read conversion failed");
check(buffer.seek(6) && buffer.readAll().toString() === "beta",
      "QBuffer seek/readAll conversion failed");
buffer.close();

// Base prototypes must exist before derived bindings are created. In Qt 6
// QFile inherits QIODevice through QFileDevice, and QTemporaryFile adds one
// more level. Check usable inherited methods, not just class registration.
check(typeof QFileDevice.prototype.readAll === "function"
      && typeof QFile.prototype.read === "function"
      && typeof QTemporaryFile.prototype.write === "function",
      "file bindings lost the QIODevice prototype chain");
var rawTemporary = new QTemporaryFile();
var rawFile = null;
try {
    check(rawTemporary.open(), "raw temporary file open failed");
    check(rawTemporary.write(new QByteArray("alpha\nbeta")) === 10,
          "QTemporaryFile inherited write failed");
    check(rawTemporary.flush() && rawTemporary.size() === 10,
          "QTemporaryFile QFileDevice flush/QIODevice size failed");
    check(rawTemporary.seek(0) && rawTemporary.readAll().toString() === "alpha\nbeta",
          "QTemporaryFile inherited seek/readAll failed");
    var rawPath = rawTemporary.fileName();
    rawTemporary.close();
    rawFile = new QFile(rawPath);
    check(rawFile.open(new QIODevice.OpenMode(QIODevice.ReadOnly)), "raw QFile open failed");
    check(rawFile.isOpen() && rawFile.isReadable() && !rawFile.isSequential(),
          "QFile inherited device-state predicates failed");
    check(rawFile.peek(5).toString() === "alpha" && rawFile.pos() === 0,
          "QFile inherited peek advanced its position");
    check(rawFile.read(2).toString() === "al" && rawFile.pos() === 2,
          "QFile inherited read/pos failed");
    check(rawFile.seek(0) && rawFile.readLine().toString() === "alpha\n",
          "QFile inherited seek/readLine failed");
    check(rawFile.readAll().toString() === "beta" && rawFile.atEnd(),
          "QFile inherited readAll/atEnd failed");
} finally {
    if (rawFile !== null) rawFile.close();
    rawTemporary.close();
    rawTemporary.remove();
}

// INI settings exercise QVariant persistence, groups, enumeration, and
// removal while keeping the test self-contained and deterministic.
var settingsPath = QDir.tempPath() + "/qtscriptgenerator-qt6-core-regression.ini";
QFile.remove(settingsPath);

// QMutex compatibility covers the nonrecursive usage expected by consumer
// scripts. Qt 6 keeps the lock/tryLock/unlock API but no longer exposes Qt 5's
// RecursionMode constructor argument.
check(typeof QMutex === "function", "QMutex binding was not imported");
check(typeof QMutex.RecursionMode === "undefined",
      "Qt 5 RecursionMode leaked into the Qt 6 QMutex binding");
var mutex = new QMutex();
check(mutex.toString() === "QMutex", "QMutex prototype conversion failed");
check(mutex.tryLock(), "QMutex.tryLock() failed on an unlocked mutex");
check(!mutex.tryLock(5),
      "a nonrecursive QMutex.tryLock(timeout) unexpectedly reacquired the lock");
mutex.unlock();
mutex.lock();
check(!mutex.tryLock(5), "QMutex.tryLock(timeout) did not report a held mutex");
mutex.unlock();
check(mutex.tryLock(0), "QMutex.tryLock(0) failed after unlock");
mutex.unlock();

// Consumer CSV scripts use QTextStream over a QIODevice and rely on the
// QtScript compatibility spelling writeString(). Use a deterministic
// temporary file so both the write and read paths observe the same bytes.
var csvPath = QDir.tempPath() + "/qtscriptgenerator-qt6-csv-smoke.csv";
QFile.remove(csvPath);
var writeFile = new QFile(csvPath);
check(writeFile.open(new QIODevice.OpenMode(QIODevice.WriteOnly)),
      "QFile could not be opened for QTextStream writing");
var writer = new QTextStream(writeFile);
writer.writeString("name,score\nsample,42\n");
writer.flush();
check(writer.status().valueOf() === QTextStream.Ok.valueOf(),
      "QTextStream reported a write failure");
writeFile.close();
var readFile = new QFile(csvPath);
check(readFile.open(new QIODevice.OpenMode(QIODevice.ReadOnly)),
      "QFile could not be reopened for QTextStream reading");
var reader = new QTextStream(readFile);
check(reader.readAll() === "name,score\nsample,42\n",
      "QTextStream CSV round trip failed");
readFile.close();
QFile.remove(csvPath);

// Qt 6 exposes event-category predicates on QEvent. A plain user event must
// remain outside the input/pointer hierarchy while retaining accept state.
var baseEvent = new QEvent(QEvent.User);
check(!baseEvent.isInputEvent() && !baseEvent.isPointerEvent()
      && !baseEvent.isSinglePointEvent(),
      "plain QEvent was incorrectly classified as an input event");
baseEvent.ignore();
check(!baseEvent.isAccepted(), "QEvent.ignore() did not clear acceptance");
baseEvent.accept();
check(baseEvent.isAccepted(), "QEvent.accept() did not restore acceptance");

// Qt 6 locale and time-zone value types are useful in scripts that format
// dates for users.  Cover BCP-47/code conversion, deterministic separators,
// IANA/fixed zones, and QDateTime's new QTimeZone representation methods.
var locale = new QLocale("en_US");
check(locale.name() === "en_US" && locale.bcp47Name().indexOf("en") === 0
      && locale.country().valueOf() === 248,
      "QLocale name/BCP-47 conversion failed");
check(QLocale.languageToCode(QLocale.English) === "en"
      && QLocale.codeToLanguage("de").valueOf() === 94,
      "QLocale language code conversion failed");
check(locale.createSeparatedList(["one", "two"]) === "one and two",
      "QLocale separated-list formatting failed");
check(locale.uiLanguages().length > 0 && locale.decimalPoint().toString().length === 1,
      "QLocale locale metadata is incomplete");

var utcZone = new QTimeZone("UTC");
check(utcZone.isValid() && utcZone.id() === "UTC"
      && !utcZone.hasDaylightTime() && typeof utcZone.isUtcOrFixedOffset === "function",
      "QTimeZone UTC construction failed");
check(QTimeZone.utc().id() === "UTC"
      && QTimeZone.isTimeZoneIdAvailable("UTC")
      && QTimeZone.availableTimeZoneIds().length > 0,
      "QTimeZone discovery helpers failed");
var fixedZone = QTimeZone.fromSecondsAheadOfUtc(3600);
check(fixedZone.isValid()
      && fixedZone.fixedSecondsAheadOfUtc() === 3600,
      "QTimeZone fixed-offset construction failed");
var zonedInstant = instant.toTimeZone(fixedZone);
check(zonedInstant.offsetFromUtc() === 3600
      && zonedInstant.timeZone().offsetFromUtc(zonedInstant) === 3600
      && zonedInstant.toSecsSinceEpoch() === instant.toSecsSinceEpoch(),
      "QDateTime QTimeZone conversion changed the instant");
check(zonedInstant.startOfDay().date().equals(zonedInstant.date())
      && zonedInstant.endOfDay().date().equals(zonedInstant.date()),
      "QDateTime start/end-of-day helpers returned the wrong date");

var settings = new QSettings(settingsPath, QSettings.IniFormat);
check(typeof settings.iniCodec === "undefined" && typeof settings.setIniCodec === "undefined",
      "INI codec shims remain exported");
settings.setValue("answer", 42);
settings.setValue("unicode", "caf\u00e9 \u03a9 \ud83d\ude00");
settings.beginGroup("profile");
settings.setValue("name", "sample");
settings.endGroup();
settings.sync();
var reread = new QSettings(settingsPath, QSettings.IniFormat);
check(reread.value("unicode") === "caf\u00e9 \u03a9 \ud83d\ude00", "Unicode INI persistence failed");
var iniBytes = new QFile(settingsPath);
check(iniBytes.open(new QIODevice.OpenMode(QIODevice.ReadOnly)), "INI bytes open failed");
check(iniBytes.readAll().toHex().toString().indexOf("636166c3a920cea920f09f9880") !== -1,
      "INI output is not UTF-8");
iniBytes.close();
check(reread.value("answer") === 42 && reread.value("profile/name") === "sample",
      "QSettings QVariant persistence failed");
check(reread.childGroups().length === 1 && reread.childGroups()[0] === "profile",
      "QSettings group enumeration failed");
reread.remove("profile");
reread.sync();
check(!reread.contains("profile/name"), "QSettings group removal failed");
QFile.remove(settingsPath);
print("Core regression smoke passed");
