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
	const char *createHiscoresTable = "CREATE TABLE IF NOT EXISTS Hiscores (id INTEGER PRIMARY KEY, player TEXT NOT NULL, score INTEGER NOT NULL, date TEXT NOT NULL);";

	if (sqlite3_exec(db, createHiscoresTable, NULL, NULL, &dbError)) {
		printf("Error executing SQLite3 statement: %s\n", sqlite3_errmsg(db));
		sqlite3_free(dbError);
	}
}

void Database::InsertHiscore(std::string playerName, int score) {
	std::string insert = "INSERT INTO Hiscores VALUES (NULL, '" + playerName + "', " + std::to_string(score) + ",'" + GetCurrentDateAndTime() + "');";
	const char *insertIntoHighscoresTable = insert.c_str();

	if (sqlite3_exec(db, insertIntoHighscoresTable, NULL, NULL, &dbError)) {
		printf("Error executing SQLite3 statement: %s\n", sqlite3_errmsg(db));
		sqlite3_free(dbError);
	}
}

std::string Database::GetCurrentDateAndTime() {
	time_t currentTime = time(0);
	std::tm now;
	localtime_s(&now, &currentTime);

	std::string year = std::to_string(now.tm_year + 1900);
	std::string month = std::to_string(now.tm_mon + 1);
	std::string day = std::to_string(now.tm_mday);
	std::string hour = now.tm_hour < 10 ? "0" + std::to_string(now.tm_hour) : std::to_string(now.tm_hour);
	std::string min = now.tm_min < 10 ? "0" + std::to_string(now.tm_min) : std::to_string(now.tm_min);
	std::string sec = now.tm_sec < 10 ? "0" + std::to_string(now.tm_sec) : std::to_string(now.tm_sec);
	return day + "." + month + "." + year + " " + hour + ":" + min + ":" + sec;
}

std::string Database::GetTopTenHiscores() {
	std::vector<std::string> result;
	for (int i = 0; i < 10; i++) {
		result.push_back(std::string());
	}

	const char *selectTopTenHiscores = "SELECT * FROM Hiscores ORDER BY score DESC LIMIT 10";
	sqlite3_stmt *stmt;

	sqlite3_prepare_v2(db, "SELECT * FROM Hiscores ORDER BY score DESC LIMIT 10;", -1, &stmt, NULL);
	sqlite3_step(stmt);

	std::string kappalul = std::string((char *)sqlite3_column_text(stmt, 0));

	while (sqlite3_column_text(stmt, 0)) {
		for (int i = 0; i < 3; i++) {
			result.at(i) = std::string((char *)sqlite3_column_text(stmt, i));
			sqlite3_step(stmt);
		}
	}

	sqlite3_finalize(stmt);


	return "kappa123";
}
