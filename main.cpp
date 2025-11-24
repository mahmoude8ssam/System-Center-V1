#include <QApplication>
#include <QPushButton>
#include <QtSql>

#include <QDebug>

#include "pages/LoginWidget/LoginWidget.h"
#include "pages/HomeWidget/HomeWidget.h"


void createDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("center.db");

    if (!db.open()) {
        qDebug() << "not open";
        return;
    }

    QSqlQuery query;

    // جدول الطلاب
    query.exec("CREATE TABLE IF NOT EXISTS students ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT, "
               "phone TEXT, "
               "phoneparent TEXT, "
               "groupName TEXT, "
               "stage TEXT)");

    // جدول المدرسين
    query.exec("CREATE TABLE IF NOT EXISTS teachers ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT, "
               "phone TEXT, "
               "subject TEXT)");

    // جدول المجموعات
    query.exec("CREATE TABLE IF NOT EXISTS groups ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
           "name TEXT, "
           "stage TEXT, "
           "teacher_id INTEGER, "
           "FOREIGN KEY(teacher_id) REFERENCES teachers(id)"
           ");");
               

    // جدول المراحل الدراسية
    query.exec("CREATE TABLE IF NOT EXISTS stages ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT)");
    
    qDebug() << "success ";
}

bool isLoggedIn() {
    return false;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle("Fusion");

    createDatabase();

    QWidget* window = nullptr;
    if (isLoggedIn()) {
        window = new HomeWidget();
    } else {
        window = new LoginWidget();
    }

    window->show();
    return app.exec();
}

