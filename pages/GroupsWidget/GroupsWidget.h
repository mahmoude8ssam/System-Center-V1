#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QList>
#include "../../models/Group/Group.h"

class GroupsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GroupsWidget(QWidget *parent = nullptr);

private:
    QLabel *titleLabel;
    QTableWidget *table;
    QPushButton *addGroupBtn;
    QList<GroupData> groups;

    void populateTable();
    void showAddGroupDialog();
};
