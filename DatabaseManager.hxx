#pragma once
#ifndef DATABASE_MANAGER_HXX
#define DATABASE_MANAGER_HXX

#include <iostream>
#include <string>
#include <sqlite3.h>
#include "IDatabaseManager.hxx"

class DatabaseManager : public IDatabaseManager {
private:
    sqlite3* dbConnection;

public:
    explicit DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

    bool execute_query(const std::string& sqlQuery);
    bool execute_query_with_callback(const std::string& sqlQuery, int (*callback)(void*, int, char**, char**));

    sqlite3* get_connection();

    bool create_table() override;
    bool insert_name(const std::string& name) override;
    bool update_name(int id, const std::string& newName) override;
    bool delete_name(int id) override;
    bool list_all() override;
};

#endif DATABASE_MANAGER_HXX