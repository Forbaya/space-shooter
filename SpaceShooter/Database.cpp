#include "Database.h"

Database::Database(char *name) {
	bool connection = OpenConnection(name);

	if (connection) {
		CreateTables();
	}
	
}

Database::~Database() {
	sqlite3_close(db);
}

bool Database::OpenConnection(char *name) {
	if (sqlite3_open(name, &db)) {
		printf("Error opening SQLite3 database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return false;
	}

	return true;
}

void Database::CreateTables() {
	const char *createHighscoresTable = "CREATE TABLE IF NOT EXISTS Highscores (id INTEGER PRIMARY KEY, player STRING NOT NULL, score INTEGER NOT NULL);";

	if (sqlite3_exec(db, createHighscoresTable, NULL, NULL, &dbError)) {
		printf("Error executing SQLite3 statement: %s\n", sqlite3_errmsg(db));
		sqlite3_free(dbError);
	}
}
