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
	const char *createHighscoresTable = "CREATE TABLE IF NOT EXISTS Highscores (id INTEGER PRIMARY KEY, player STRING NOT NULL, score INTEGER NOT NULL, date STRING NOT NULL);";

	if (sqlite3_exec(db, createHighscoresTable, NULL, NULL, &dbError)) {
		printf("Error executing SQLite3 statement: %s\n", sqlite3_errmsg(db));
		sqlite3_free(dbError);
	}
}

void Database::InsertHighscore(std::string playerName, int score) {
	time_t currentTime = time(0);
	std::tm now;
	localtime_s(&now, &currentTime);

	int year = now.tm_year + 1900;
	int month = now.tm_mon + 1;
	int day = now.tm_mday;
	int hour = now.tm_hour;
	int min = now.tm_min;
	int sec = now.tm_sec;
	std::string date = std::to_string(day) + "." + std::to_string(month) + "." 
		+ std::to_string(year) + " " + std::to_string(hour) + ":" + std::to_string(min) + ":" + std::to_string(sec);
	
	

	// (player, score, date)
	std::string insert = "INSERT INTO Highscores VALUES (" + playerName + ", " + std::to_string(score) + "," + date + ");";
	const char *insertIntoHighscoresTable = insert.c_str();


	if (sqlite3_exec(db, insertIntoHighscoresTable, NULL, NULL, &dbError)) {
		printf("Error executing SQLite3 statement: %s\n", sqlite3_errmsg(db));
		sqlite3_free(dbError);
	}

	
}
