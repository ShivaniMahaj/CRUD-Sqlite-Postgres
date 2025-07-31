#pragma once
#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <iostream>
#include <string>
#include "DatabaseManager.hxx"

class Employee {
private:
    IDatabaseManager& database;

public:
    explicit Employee(IDatabaseManager& dbManager);

    bool create_table();
    bool add_employee(const std::string& name);
    bool update_employee_name(int id, const std::string& newName);
    bool delete_employee(int id);
    void list_all_employees();
};

#endif EMPLOYEE_HPP