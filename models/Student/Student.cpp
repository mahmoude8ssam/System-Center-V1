#include "Student.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

QList<StudentData> Student::getAllStudents() {
    QList<StudentData> list;
    QSqlQuery query("SELECT * FROM students");
    while (query.next()) {
        StudentData s;
        s.id = query.value("id").toInt();
        s.name = query.value("name").toString();
        s.phone = query.value("phone").toString();
        s.phoneParent = query.value("phoneparent").toString();
        s.groupName = query.value("groupName").toString();
        s.stage = query.value("stage").toString();
        //s.absenceWarning = query.value("absenceWarning").toString();
        s.absenceWarning = "";
        list.append(s);
    }
    return list;
}


int Student::getCountAll() {
    QSqlQuery query("SELECT COUNT(*) FROM students");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}


StudentData Student::getStudentById(int id) {
    StudentData s;
    QSqlQuery query;
    query.prepare("SELECT * FROM students WHERE id=:id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        s.id = query.value("id").toInt();
        s.name = query.value("name").toString();
        s.phone = query.value("phone").toString();
        s.phoneParent = query.value("phoneparent").toString();
        s.groupName = query.value("groupName").toString();
        s.stage = query.value("stage").toString();
        //s.absenceWarning = query.value("absenceWarning").toString();
        s.absenceWarning = "";
    }
    return s;
}

bool Student::addStudent(const StudentData& s) {
    QSqlQuery query;
    query.prepare("INSERT INTO students (name, phone, phoneparent, groupName, stage) "
                  "VALUES (:name, :phone, :phoneparent, :groupName, :stage)");
    query.bindValue(":name", s.name);
    query.bindValue(":phone", s.phone);
    query.bindValue(":phoneparent", s.phoneParent);
    query.bindValue(":groupName", s.groupName);
    query.bindValue(":stage", s.stage);
    return query.exec();
}

bool Student::updateStudent(const StudentData& s) {
    QSqlQuery query;
    query.prepare("UPDATE students SET name=:name, phone=:phone, phoneparent=:phoneparent, "
                  "groupName=:groupName, stage=:stage WHERE id=:id");
    query.bindValue(":name", s.name);
    query.bindValue(":phone", s.phone);
    query.bindValue(":phoneparent", s.phoneParent);
    query.bindValue(":groupName", s.groupName);
    query.bindValue(":stage", s.stage);
    query.bindValue(":id", s.id);
    return query.exec();
}

bool Student::deleteStudent(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM students WHERE id=:id");
    query.bindValue(":id", id);
    return query.exec();
}
