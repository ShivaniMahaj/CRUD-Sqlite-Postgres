#pragma once

#ifndef POSTGRESS_MANAGER_HXX
#define POSTGRESS_MANAGER_HXX

#include <iostream>
#include <string>
#include "IDatabaseManager.hxx"
#include <odb/pgsql/database.hxx>
#include <odb/transaction.hxx>
#include <odb/schema-catalog.hxx>

using namespace std;
using namespace odb::core;


class PostgressManager : public IDatabaseManager {
private:
    std::shared_ptr<odb::pgsql::database> db_;

public:
    PostgressManager();
    ~PostgressManager();

    bool create_table() override;
    bool insert_name(const std::string& name) override;
    bool update_name(int id, const std::string& newName) override;
    bool delete_name(int id) override;
    bool list_all() override;
};

#endif POSTGRESS_MANAGER_HXX
