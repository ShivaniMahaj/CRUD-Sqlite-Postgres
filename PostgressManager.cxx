#include "PostgressManager.hxx"
#include "Employee.hxx"
#include "Employee-odb.hxx"

PostgressManager::PostgressManager() {
    db_ = std::make_shared<odb::pgsql::database>(
        "postgres",       // my postgres username
        "ABCD1234",       // my local password
        "postgres",       // my local database
        "127.0.0.1",      // Host
        5432              // Port
        );
}


PostgressManager::~PostgressManager() {
}


bool PostgressManager::create_table() {
    //try {
    //    odb::transaction t(db_->begin());
    //    odb::schema_catalog::create_schema(*db_);
    //    t.commit();
    //    return true;
    //} catch (const odb::exception& e) {
    //    std::cerr << "Create table failed: " << e.what() << "\n";
    //    return false;
    //}
    return true;
}


bool PostgressManager::insert_name(const std::string& name) {
    try {
        Employee e(name);
        odb::transaction t(db_->begin());
        db_->persist(e);
        t.commit();
        return true;
    }
    catch (const odb::exception& e) {
        std::cerr << "Insert failed: " << e.what() << "\n";
        return false;
    }
}


bool PostgressManager::update_name(int id, const std::string& newName) {
    try {
        odb::transaction t(db_->begin());
        std::shared_ptr<Employee> emp(db_->load<Employee>(id));
        emp->name(newName);
        db_->update(*emp);
        t.commit();
        return true;
    }
    catch (const odb::exception& e) {
        std::cerr << "Update failed: " << e.what() << "\n";
        return false;
    }
}


bool PostgressManager::delete_name(int id) {
    try {
        odb::transaction t(db_->begin());
        db_->erase<Employee>(id);
        t.commit();
        return true;
    }
    catch (const odb::exception& e) {
        std::cerr << "Delete failed: " << e.what() << "\n";
        return false;
    }
}


bool PostgressManager::list_all() {
    try {
        odb::transaction t(db_->begin());
        typedef odb::result<Employee> result;
        result r(db_->query<Employee>());

        for (const Employee& e : r) {
            std::cout << "ID: " << e.id() << ", Name: " << e.name() << "\n";
        }

        t.commit();
        return true;
    }
    catch (const odb::exception& e) {
        std::cerr << "List failed: " << e.what() << "\n";
        return false;
    }
}
