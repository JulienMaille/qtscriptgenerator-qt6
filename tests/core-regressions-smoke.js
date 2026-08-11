function check(condition, message) {
    if (!condition) throw new Error(message);
}
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

print("Core regression smoke passed");
var settings = new QSettings(settingsPath, QSettings.IniFormat);
settings.setValue("answer", 42);
settings.beginGroup("profile");
settings.setValue("name", "sample");
settings.endGroup();
settings.sync();
var reread = new QSettings(settingsPath, QSettings.IniFormat);
check(reread.value("answer") === 42 && reread.value("profile/name") === "sample",
      "QSettings QVariant persistence failed");
check(reread.childGroups().length === 1 && reread.childGroups()[0] === "profile",
      "QSettings group enumeration failed");
reread.remove("profile");
reread.sync();
check(!reread.contains("profile/name"), "QSettings group removal failed");
QFile.remove(settingsPath);
