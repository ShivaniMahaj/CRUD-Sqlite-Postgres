#include <iostream>
#include <memory>
#include <odb/sqlite/database.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/transaction.hxx>
#include <odb/schema-catalog.hxx>

#include "DatabaseManager.hxx"
#include "PostgressManager.hxx"
#include "Employee.hpp"
#include "Menu.hpp"


int main() {
    std::unique_ptr<IDatabaseManager> dbManager;

    int dbChoice;
    std::cout << "Select Database:\n";
    std::cout << "1. SQLite\n";
    std::cout << "2. PostgreSQL\n";
    std::cout << "Enter choice: ";
    std::cin >> dbChoice;
    std::cin.ignore();

    if (dbChoice == 1) {
        dbManager = std::make_unique<DatabaseManager>("employees.db");
    }
    else if (dbChoice == 2) {
        dbManager = std::make_unique<PostgressManager>();
    }
    else {
        std::cerr << "Invalid database choice.\n";
        return 1;
    }

    Employee employee(*dbManager);
    Menu menu;

    if (!employee.create_table()) {
        std::cerr << "Failed to create employee table.\n";
        return 1;
    }

    int choice;
    bool running = true;

    while (running) {
        menu.show_menu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: menu.create_Employee(employee); break;
        case 2: menu.update_Employee(employee); break;
        case 3: menu.delete_Employee(employee); break;
        case 4: menu.list_Employees(employee); break;
        case 5: running = false; break;
        default: std::cout << "Invalid choice. Please Try again.\n"; break;
        }
    }

    return 0;
}










//int main() {
//    DatabaseManager dbManager("employees.db");
//    Employee employee(dbManager);
//    Menu menu;
//    if (!employee.create_table()) {
//        std::cerr << "Failed to create employee table.\n";
//        return 1;
//    }
//
//    int choice;
//    bool running = true;
//
//    while (running) {
//        menu.show_menu();
//        std::cin >> choice;
//        std::cin.ignore();
//
//        switch (choice) {
//        case 1: menu.create_Employee(employee); break;
//        case 2: menu.update_Employee(employee); break;
//        case 3: menu.delete_Employee(employee); break;
//        case 4: menu.list_Employees(employee); break;
//        case 5: running = false; break;
//        default: std::cout << "Invalid choice. Please Try again.\n"; break;
//        }
//    }
//
//    return 0;
//}
