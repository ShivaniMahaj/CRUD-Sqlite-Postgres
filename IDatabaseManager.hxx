#pragma once

#ifndef IDATABASE_MANAGER_HXX
#define IDATABASE_MANAGER_HXX

#include <string>

class IDatabaseManager {
public:
    virtual ~IDatabaseManager() {}

    virtual bool create_table() = 0;
    virtual bool insert_name(const std::string& name) = 0;
    virtual bool update_name(int id, const std::string& newName) = 0;
    virtual bool delete_name(int id) = 0;
    virtual bool list_all() = 0;
};

#endif IDATABASE_MANAGER_HXX

