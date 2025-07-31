#pragma once
#ifndef EMPLOYEE_HXX
#define EMPLOYEE_HXX

#include <string>
#include <odb/core.hxx>

#pragma db object
class Employee
{
public:
    Employee() = default;


    explicit Employee(const std::string& name) : id_(0), name_(name) {
    }


    const std::string& name() const { 
        return name_; 
    }


    void name(const std::string& newName) { 
        name_ = newName; 
    }


    unsigned long id() const {
        return id_; 
    }

private:
    friend class odb::access;

#pragma db id auto
    unsigned long id_;  

    std::string name_;
};

#endif EMPLOYEE_HXX
