function check(condition, message) {
    if (!condition)
        throw new Error(message);
}

check(QSqlDatabase.isDriverAvailable("QSQLITE"), "Qt SQLite driver is unavailable");
var connectionName = "qt6SqlRegression";
var database = QSqlDatabase.addDatabase("QSQLITE", connectionName);
database.setDatabaseName(":memory:");
check(database.open(), "could not open the SQL regression database");

var query = new QSqlQuery(database);
check(query.exec("CREATE TABLE items (id INTEGER PRIMARY KEY, label TEXT, amount INTEGER)"),
      "could not create SQL regression table");
check(database.transaction(), "SQLite transaction could not start");
check(query.exec("INSERT INTO items(label, amount) VALUES('rolled-back', 1)"),
      "could not insert transaction row");
check(database.rollback(), "SQLite transaction rollback failed");
check(query.exec("SELECT COUNT(*) FROM items"), "could not count after rollback");
check(query.next() && query.value(0) === 0,
      "rolled-back SQL row remained visible");

check(database.transaction(), "second SQLite transaction could not start");
check(query.exec("INSERT INTO items(label, amount) VALUES('committed', 9)"),
      "could not insert committed row");
check(database.commit(), "SQLite transaction commit failed");
check(query.lastInsertId() === 1, "QSqlQuery lastInsertId conversion failed");

// QSqlTableModel exercises the generated model inheritance and the Qt 6
// database value wrapper in a realistic consumer pattern.
var model = new QSqlTableModel(null, database);
model.setTable("items");
check(model.select(), "QSqlTableModel select failed: " + model.lastError().text());
check(model.rowCount() === 1 && model.columnCount() === 3,
      "QSqlTableModel returned the wrong shape");
check(model.data(model.index(0, 1)) === "committed",
      "QSqlTableModel data/index conversion failed");
model.setFilter("amount >= 10");
check(model.select() && model.rowCount() === 0,
      "QSqlTableModel filter did not update the result set");

database.close();
QSqlDatabase.removeDatabase(connectionName);
print("SQL regression smoke passed");
