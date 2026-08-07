function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

check(typeof QSqlDatabase === "function", "QSqlDatabase binding was not imported");
check(typeof QSqlQuery === "function", "QSqlQuery binding was not imported");
check(typeof QSqlError === "function", "QSqlError binding was not imported");
check(QSqlDatabase.isDriverAvailable("QSQLITE"), "Qt SQLite driver is unavailable");

var database = QSqlDatabase.addDatabase("QSQLITE", "qt6SqlSmoke");
database.setDatabaseName(":memory:");
check(database.open(), "opening the in-memory SQLite database failed: " +
      database.lastError().text());

var query = new QSqlQuery(database);
check(query.exec("CREATE TABLE sample (id INTEGER PRIMARY KEY, name TEXT, score INTEGER)"),
      "creating the test table failed: " + query.lastError().text());

check(query.prepare("INSERT INTO sample(name, score) VALUES(:name, :score)"),
      "preparing a named query failed");
query.bindValue(":name", "alpha");
query.bindValue(":score", 7);
check(query.boundValueName(0) === ":name", "Qt 6 boundValueName failed");
var boundNames = query.boundValueNames();
check(boundNames.length === 2 && boundNames[1] === ":score",
      "Qt 6 boundValueNames failed");
check(query.exec(), "executing the named query failed: " + query.lastError().text());

query.clear();
query.setPositionalBindingEnabled(true);
check(query.isPositionalBindingEnabled(),
      "Qt 6 positionalBindingEnabled property failed");
check(query.prepare("INSERT INTO sample(name, score) VALUES(?, ?)"),
      "preparing a positional query failed");
query.addBindValue("beta");
query.addBindValue(11);
check(query.exec(), "executing the positional query failed: " + query.lastError().text());

check(query.exec("SELECT id, name, score FROM sample ORDER BY id"),
      "selecting test rows failed: " + query.lastError().text());
check(query.next(), "first result row is missing");
check(query.value("name") === "alpha" && query.value(2) === 7,
      "named or indexed result conversion failed");
var record = query.record();
check(record.count() === 3 && record.fieldName(1) === "name",
      "QSqlRecord conversion failed");
check(query.next() && query.value(1) === "beta" && query.value("score") === 11,
      "second result row is invalid");
check(!query.next(), "unexpected extra result row");

var error = new QSqlError("driver", "database", QSqlError.ConnectionError, "E6");
check(error.nativeErrorCode() === "E6", "Qt 6 nativeErrorCode failed");
error.setNumber(42);
check(error.number() === 42 && error.nativeErrorCode() === "42",
      "legacy numeric QSqlError compatibility failed");
error.setDriverText("updated driver");
check(error.driverText() === "updated driver" && error.databaseText() === "database",
      "legacy mutable QSqlError compatibility failed");

database.close();

