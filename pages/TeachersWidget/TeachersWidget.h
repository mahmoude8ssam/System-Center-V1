#include "../../models/Teacher/Teacher.h"
#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QList>


class TeachersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TeachersWidget(QWidget *parent = nullptr);
signals:
    void teacherAdded();
private:
    QLabel *titleLabel;
    QTableWidget *table;
    QPushButton *addTeacherBtn;
    QList<TeacherData> teachers;

    void populateTable();
    void showAddTeacherDialog();
};
