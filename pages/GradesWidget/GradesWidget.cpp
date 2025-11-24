#include "GradesWidget.h"
#include <QHeaderView>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QDialog>
#include "../../components/CustomButton/CustomButton.h"

GradesWidget::GradesWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel("المراحل الدراسية", this);
    QFont f; f.setPointSize(16); f.setBold(true);
    titleLabel->setFont(f);
    mainLayout->addWidget(titleLabel);

    
    addGradeBtn = new CustomButton(this,"➕ إضافة مرحلة جديدة");
    //addGradeBtn->setStyleSheet("background-color: #4CAF50; color: white; font-weight: bold; padding: 5px; border-radius: 5px;");
    mainLayout->addWidget(addGradeBtn);

    // table
    table = new QTableWidget(this);
    table->setColumnCount(3); 
    QStringList headers = {"اسم المرحلة", "تعديل", "حذف"};
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(table);

   
    grades = Stage::getAllStages();

    populateTable();

    setLayout(mainLayout);

    connect(addGradeBtn, &QPushButton::clicked, this, &GradesWidget::showAddGradeDialog);
}

void GradesWidget::populateTable()
{
    table->setRowCount(0);
    int row = 0;
    for (const StageData &g : grades) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(g.name));

        
        QPushButton* editBtn = new QPushButton("✏️ تعديل");
        editBtn->setStyleSheet("background-color: #2196F3; color: white; padding: 2px 5px; border-radius: 3px;");
        table->setCellWidget(row, 1, editBtn);
        connect(editBtn, &QPushButton::clicked, this, [=, &g]() {
            QDialog dialog(this);
            dialog.setWindowTitle("تعديل المرحلة");
            QFormLayout* form = new QFormLayout(&dialog);

            QLineEdit* nameEdit = new QLineEdit(g.name);
            form->addRow("اسم المرحلة:", nameEdit);

            QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            form->addWidget(buttons);

            connect(buttons, &QDialogButtonBox::accepted, [&]() {
               // g.name = nameEdit->text();
                populateTable();
                dialog.accept();
            });
            connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
            dialog.exec();
        });

        
        QPushButton* deleteBtn = new QPushButton("🗑️ حذف");
        deleteBtn->setStyleSheet("background-color: #f44336; color: white; padding: 2px 5px; border-radius: 3px;");
        table->setCellWidget(row, 2, deleteBtn);
        connect(deleteBtn, &QPushButton::clicked, this, [=, &g]() {
            int ret = QMessageBox::question(this, "تأكيد الحذف", "هل تريد حذف هذه المرحلة؟", QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes) {
               // grades.removeOne(g);
                populateTable();
            }
        });

        ++row;
    }
}

void GradesWidget::showAddGradeDialog()
{
    QDialog dialog(this);
    dialog.setWindowTitle("إضافة مرحلة جديدة");
    QFormLayout* form = new QFormLayout(&dialog);

    QLineEdit* nameEdit = new QLineEdit();
    form->addRow("اسم المرحلة:", nameEdit);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    form->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, [&]() {
       // StageData g{nameEdit->text()};
       // grades.append(g);
        populateTable();
        dialog.accept();
    });
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    dialog.exec();
}
