// User.h
#pragma once
#include <QString>

class User {
public:
    //Prevent creating more than one object
    static User& instance() {
        static User _instance;
        return _instance;
    }

    // ===============================
    //   (Setters)
    // ===============================
    void setName(const QString& n) { name = n; }
    void setEmail(const QString& e) { email = e; }
    void setAge(int a) { age = a; }
    void setRole(const QString& r) { role = r; }

    void setUserData(const QString& n, const QString& e, int a, const QString& r) {
        name = n;
        email = e;
        age = a;
        role = r;
    }

    // ===============================
    //  (Getters)
    // ===============================
    QString getName() const { return name; }
    QString getEmail() const { return email; }
    int getAge() const { return age; }
    QString getRole() const { return role; }

    bool isLoggedIn() const { return !email.isEmpty(); }

private:

    QString name;
    QString email;
    int age;
    QString role;

    //Prevent creating more than one object
    User() : name(""), email(""), age(0), role("") {}
    User(const User&) = delete;
    void operator=(const User&) = delete;
};
