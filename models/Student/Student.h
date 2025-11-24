#pragma once
#include <QString>
#include <QList>

struct StudentData {
    int id;
    QString name;
    QString phone;
    QString phoneParent;
    QString groupName;
    QString stage;
    bool absenceWarning;
};

class Student {
public:
    static QList<StudentData> getAllStudents();
    static int getCountAll();
    static StudentData getStudentById(int id);
    static bool addStudent(const StudentData& s);
    static bool updateStudent(const StudentData& s);
    static bool deleteStudent(int id);
};
