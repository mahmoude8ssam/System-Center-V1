#include "GroupsWidget.h"
#include <QHeaderView>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QDialog>

GroupsWidget::GroupsWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel("المجموعات الدراسية", this);
    QFont f; f.setPointSize(16); f.setBold(true);
    titleLabel->setFont(f);
    mainLayout->addWidget(titleLabel);

    
    addGroupBtn = new QPushButton("➕ إضافة مجموعة جديدة", this);
    addGroupBtn->setStyleSheet("background-color: #4CAF50; color: white; font-weight: bold; padding: 5px; border-radius: 5px;");
    mainLayout->addWidget(addGroupBtn);

    
    table = new QTableWidget(this);
    table->setColumnCount(5);
    QStringList headers = {"اسم المجموعة", "المرحلة", "المدرس", "تعديل", "حذف"};
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(table);

    
    groups = Group::getAllGroups();

    populateTable();

    setLayout(mainLayout);

    connect(addGroupBtn, &QPushButton::clicked, this, &GroupsWidget::showAddGroupDialog);
}

void GroupsWidget::populateTable()
{
    table->setRowCount(0);
    int row = 0;
    for (GroupData &g : groups) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(g.name));
        table->setItem(row, 1, new QTableWidgetItem(g.stage));
        table->setItem(row, 2, new QTableWidgetItem(g.teacherName));

        
        QPushButton* editBtn = new QPushButton("✏️ تعديل");
        editBtn->setStyleSheet("background-color: #2196F3; color: white; padding: 2px 5px; border-radius: 3px;");
        table->setCellWidget(row, 3, editBtn);
        connect(editBtn, &QPushButton::clicked, this, [=, &g]() {
            QDialog dialog(this);
            dialog.setWindowTitle("تعديل المجموعة");
            QFormLayout* form = new QFormLayout(&dialog);

            QLineEdit* nameEdit = new QLineEdit(g.name);
            QLineEdit* stageEdit = new QLineEdit(g.stage);
            QLineEdit* teacherEdit = new QLineEdit(g.teacherName);

            form->addRow("اسم المجموعة:", nameEdit);
            form->addRow("المرحلة:", stageEdit);
            form->addRow("اسم المدرس:", teacherEdit);

            QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            form->addWidget(buttons);

            connect(buttons, &QDialogButtonBox::accepted, [&]() {
                g.name = nameEdit->text();
                g.stage = stageEdit->text();
                g.teacherName = teacherEdit->text();
                populateTable();
                dialog.accept();
            });
            connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
            dialog.exec();
        });

        
        QPushButton* deleteBtn = new QPushButton("🗑️ حذف");
        deleteBtn->setStyleSheet("background-color: #f44336; color: white; padding: 2px 5px; border-radius: 3px;");
        table->setCellWidget(row, 4, deleteBtn);
        connect(deleteBtn, &QPushButton::clicked, this, [=, &g]() {
            int ret = QMessageBox::question(this, "تأكيد الحذف", "هل تريد حذف هذه المجموعة؟", QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes) {
                //groups.removeOne(g);
                populateTable();
            }
        });

        ++row;
    }
}

void GroupsWidget::showAddGroupDialog()
{
    QDialog dialog(this);
    dialog.setWindowTitle("إضافة مجموعة جديدة");
    QFormLayout* form = new QFormLayout(&dialog);

    QLineEdit* nameEdit = new QLineEdit();
    QLineEdit* stageEdit = new QLineEdit();
    QLineEdit* teacherEdit = new QLineEdit();

    form->addRow("اسم المجموعة:", nameEdit);
    form->addRow("المرحلة:", stageEdit);
    form->addRow("اسم المدرس:", teacherEdit);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    form->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, [&]() {
        //Group g{nameEdit->text(), stageEdit->text(), teacherEdit->text()};
        //groups.append(g);
        populateTable();
        dialog.accept();
    });
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    dialog.exec();
}
