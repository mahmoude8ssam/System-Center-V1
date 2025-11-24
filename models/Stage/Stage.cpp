#include "Stage.h"
#include <QSqlQuery>
#include <QVariant>

QList<StageData> Stage::getAllStages() {
    QList<StageData> list;
    QSqlQuery query("SELECT * FROM Stages");
    while(query.next()){
        StageData g;
        g.id = query.value("id").toInt();
        g.name = query.value("name").toString();
        list.append(g);
    }
    return list;
}

int Stage::getCountAll() {
    QSqlQuery query("SELECT COUNT(*) FROM Stages");
    if(query.next()) return query.value(0).toInt();
    return 0;
}

StageData Stage::getStageById(int id) {
    StageData g;
    QSqlQuery query;
    query.prepare("SELECT * FROM Stages WHERE id=:id");
    query.bindValue(":id", id);
    if(query.exec() && query.next()){
        g.id = query.value("id").toInt();
        g.name = query.value("name").toString();
    }
    return g;
}

bool Stage::addStage(const StageData& g) {
    QSqlQuery query;
    query.prepare("INSERT INTO Stages (name) VALUES (:name)");
    query.bindValue(":name", g.name);
    return query.exec();
}

bool Stage::updateStage(const StageData& g) {
    QSqlQuery query;
    query.prepare("UPDATE Stages SET name=:name WHERE id=:id");
    query.bindValue(":name", g.name);
    query.bindValue(":id", g.id);
    return query.exec();
}

bool Stage::deleteStage(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM Stages WHERE id=:id");
    query.bindValue(":id", id);
    return query.exec();
}
