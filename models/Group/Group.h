#pragma once
#include <QString>
#include <QList>

struct GroupData {
    int id;
    QString name;
    QString stage;
    QString teacherName;
    int teacherId;
};

class Group {
public:
    static QList<GroupData> getAllGroups();
    static int getCountAll();
    static GroupData getGroupById(int id);
    static bool addGroup(const GroupData& g);
    static bool updateGroup(const GroupData& g);
    static bool deleteGroup(int id);
};
