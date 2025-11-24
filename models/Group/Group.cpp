#include "Group.h"
#include <QSqlQuery>
#include <QVariant>

QList<GroupData> Group::getAllGroups() {
    QList<GroupData> list;
    QSqlQuery query("SELECT * FROM groups");
    while(query.next()){
        GroupData g;
        g.id = query.value("id").toInt();
        g.name = query.value("name").toString();
        g.stage = query.value("stage").toString();
        g.teacherName = query.value("teacherName").toString();
        list.append(g);
    }
    return list;
}

int Group::getCountAll() {
    QSqlQuery query("SELECT COUNT(*) FROM groups");
    if(query.next()) return query.value(0).toInt();
    return 0;
}

GroupData Group::getGroupById(int id) {
    GroupData g;
    QSqlQuery query;
    query.prepare("SELECT * FROM groups WHERE id=:id");
    query.bindValue(":id", id);
    if(query.exec() && query.next()){
        g.id = query.value("id").toInt();
        g.name = query.value("name").toString();
        g.stage = query.value("stage").toString();
        g.teacherName = query.value("teacherName").toString();
    }
    return g;
}

bool Group::addGroup(const GroupData& g) {
    QSqlQuery query;
    query.prepare("INSERT INTO groups (name, stage, teacherName) VALUES (:name, :stage, :teacherName)");
    query.bindValue(":name", g.name);
    query.bindValue(":stage", g.stage);
    query.bindValue(":teacherName", g.teacherName);
    return query.exec();
}

bool Group::updateGroup(const GroupData& g) {
    QSqlQuery query;
    query.prepare("UPDATE groups SET name=:name, stage=:stage, teacherName=:teacherName WHERE id=:id");
    query.bindValue(":name", g.name);
    query.bindValue(":stage", g.stage);
    query.bindValue(":teacherName", g.teacherName);
    query.bindValue(":id", g.id);
    return query.exec();
}

bool Group::deleteGroup(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM groups WHERE id=:id");
    query.bindValue(":id", id);
    return query.exec();
}
