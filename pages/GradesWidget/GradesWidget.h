#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QList>
#include "../../models/Stage/Stage.h"


class GradesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GradesWidget(QWidget *parent = nullptr);

private:
    QLabel *titleLabel;
    QTableWidget *table;
    QPushButton *addGradeBtn;
    QList<StageData> grades;

    void populateTable();
    void showAddGradeDialog();
};
