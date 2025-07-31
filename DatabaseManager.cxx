#include "DatabaseManager.hxx"

DatabaseManager::DatabaseManager(const std::string& dbName) {
	if (sqlite3_open(dbName.c_str(), &dbConnection)) {
       std::cerr << "Failed to open database: " << sqlite3_errmsg(dbConnection) << std::endl;
    } else {
        std::cout << "Database connected: " << dbName << std::endl;
    }
}


DatabaseManager::~DatabaseManager() {
    sqlite3_close(dbConnection);
    std::cout << "Database connection closed.\n";
}


bool DatabaseManager::execute_query(const std::string& sqlQuery) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(dbConnection, sqlQuery.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "SQL Error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}


bool DatabaseManager::execute_query_with_callback(const std::string& sqlQuery, int(*callback)(void*, int, char**, char**)) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(dbConnection, sqlQuery.c_str(), callback, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "SQL Error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}


sqlite3* DatabaseManager::get_connection() {
    return dbConnection;
}


bool DatabaseManager::create_table() {
    std::string sql = "CREATE TABLE IF NOT EXISTS employees ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT, " " name TEXT NOT NULL);";
    return execute_query(sql);
}


bool DatabaseManager::insert_name(const std::string& name) {
    std::string sql = "INSERT INTO employees (name) VALUES ('" + name + "');";
    return execute_query(sql);
}


bool DatabaseManager::update_name(int id, const std::string& newName) {
    std::string sql = "UPDATE employees SET name = '" + newName + "' WHERE id = " + std::to_string(id) + ";";
    return execute_query(sql);
}


bool DatabaseManager::delete_name(int id) {
    std::string sql = "DELETE FROM employees WHERE id = " + std::to_string(id) + ";";
    return execute_query(sql);
}


bool DatabaseManager::list_all() {
    std::string sql = "SELECT * FROM employees;";
    return execute_query_with_callback(sql, [](void*, int colCount, char** values, char** columns) -> int {
        for (int i = 0; i < colCount; ++i) {
            std::cout << columns[i] << " = " << (values[i] ? values[i] : "NULL") << "\n";
        }
        return 0;
        });
}