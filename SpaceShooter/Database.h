#ifndef DATABASE_H
#define DATABASE_H

#include <ctime>
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

class Database {
	public:
		Database(char *name);
		~Database();
		bool OpenConnection(char *name);
		void CreateTables();
		void InsertHiscore(std::string playerName, int score);
		std::string GetCurrentDateAndTime();
		std::string GetTopTenHiscores();
	private:
		sqlite3 *db;
		char *dbError;
};

#endif