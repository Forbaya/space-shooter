#ifndef DATABASE_H
#define DATABASE_H

#include <ctime>
#include <iostream>
#include <sqlite3.h>
#include <string>

class Database {
	public:
		Database(char *name);
		~Database();
		bool OpenConnection(char *name);
		void CreateTables();
		void InsertHighscore(std::string playerName, int score);
	private:
		sqlite3 *db;
		char *dbError;
};

#endif