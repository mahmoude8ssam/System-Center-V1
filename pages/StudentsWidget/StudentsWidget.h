// StudentsWidget.h
#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "../../models/Student/Student.h"

class StudentsWidget : public QWidget {
    Q_OBJECT
public:
    explicit StudentsWidget(QWidget *parent = nullptr);
signals:
    void studentAdded();
private:
    QLineEdit* searchEdit;
    QTableWidget* table;
    QVector<StudentData> students;

    void openAddStudentForm();

    void populateTable(const QString& filter = "");
};
