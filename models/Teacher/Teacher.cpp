#include "Teacher.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

QList<TeacherData> Teacher::getAllTeachers() {
    QList<TeacherData> list;
    QSqlQuery query("SELECT * FROM teachers");
    while (query.next()) {
        TeacherData t;
        t.id = query.value("id").toInt();
        t.name = query.value("name").toString();
        t.phone = query.value("phone").toString();
        t.subject = query.value("subject").toString();
        list.append(t);
    }
    return list;
}

int Teacher::getCountAll() {
    QSqlQuery query("SELECT COUNT(*) FROM teachers");
    if (query.next()) return query.value(0).toInt();
    return 0;
}

TeacherData Teacher::getTeacherById(int id) {
    TeacherData t;
    QSqlQuery query;
    query.prepare("SELECT * FROM teachers WHERE id=:id");
    query.bindValue(":id", id);
    if(query.exec() && query.next()){
        t.id = query.value("id").toInt();
        t.name = query.value("name").toString();
        t.phone = query.value("phone").toString();
        t.subject = query.value("subject").toString();
    }
    return t;
}

bool Teacher::addTeacher(const TeacherData& t) {
    QSqlQuery query;
    query.prepare("INSERT INTO teachers (name, phone, subject) VALUES (:name, :phone, :subject)");
    query.bindValue(":name", t.name);
    query.bindValue(":phone", t.phone);
    query.bindValue(":subject", t.subject);
    return query.exec();
}

bool Teacher::updateTeacher(const TeacherData& t) {
    QSqlQuery query;
    query.prepare("UPDATE teachers SET name=:name, phone=:phone, subject=:subject WHERE id=:id");
    query.bindValue(":name", t.name);
    query.bindValue(":phone", t.phone);
    query.bindValue(":subject", t.subject);
    query.bindValue(":id", t.id);
    return query.exec();
}

bool Teacher::deleteTeacher(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM teachers WHERE id=:id");
    query.bindValue(":id", id);
    return query.exec();
}
