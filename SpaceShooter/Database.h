#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <sqlite3.h>

class Database {
	public:
		Database(char *name);
		~Database();
		bool OpenConnection(char *name);
		void CreateTables();
	private:
		sqlite3 *db;
		char *dbError;
};

#endif