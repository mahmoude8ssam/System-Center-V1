#pragma once
#include <QString>
#include <QList>

struct TeacherData {
    int id;
    QString name;
    QString phone;
    QString subject;
};

class Teacher {
public:
    static QList<TeacherData> getAllTeachers();
    static int getCountAll();
    static TeacherData getTeacherById(int id);
    static bool addTeacher(const TeacherData& t);
    static bool updateTeacher(const TeacherData& t);
    static bool deleteTeacher(int id);
};
