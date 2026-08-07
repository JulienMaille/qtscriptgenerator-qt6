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
var settings = new QSettings(settingsPath, QSettings.IniFormat);
settings.setValue("answer", 42);
settings.beginGroup("profile");
settings.setValue("name", "blink");
settings.endGroup();
settings.sync();
var reread = new QSettings(settingsPath, QSettings.IniFormat);
check(reread.value("answer") === 42 && reread.value("profile/name") === "blink",
      "QSettings QVariant persistence failed");
check(reread.childGroups().length === 1 && reread.childGroups()[0] === "profile",
      "QSettings group enumeration failed");
reread.remove("profile");
reread.sync();
check(!reread.contains("profile/name"), "QSettings group removal failed");
QFile.remove(settingsPath);
