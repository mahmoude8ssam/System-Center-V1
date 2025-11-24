#include "TeachersWidget.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QLabel>



TeachersWidget::TeachersWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("المدرسين", this);
    QFont f; f.setPointSize(16); f.setBold(true);
    title->setFont(f);
    mainLayout->addWidget(title);

    // btn add teacher
    addTeacherBtn = new QPushButton("➕ إضافة مدرس");
    addTeacherBtn->setStyleSheet("background-color: #4CAF50; color: white; padding: 5px; border-radius: 5px;");
    mainLayout->addWidget(addTeacherBtn);

    //table
    table = new QTableWidget(this);
    table->setColumnCount(5);
    QStringList headers = {"اسم المدرس", "رقم الهاتف", "المادة", "عرض المزيد", "حذف"};
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(table);

    // get data
    teachers = Teacher::getAllTeachers();
    populateTable();

    setLayout(mainLayout);

    connect(addTeacherBtn, &QPushButton::clicked, this, &TeachersWidget::showAddTeacherDialog);
}

void TeachersWidget::populateTable() {
    table->setRowCount(0);
    int row = 0;

    for (const TeacherData& t : teachers) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(t.name));
        table->setItem(row, 1, new QTableWidgetItem(t.phone));
        table->setItem(row, 2, new QTableWidgetItem(t.subject));

        // btn
        QPushButton* moreBtn = new QPushButton("🔍 عرض المزيد");
        moreBtn->setStyleSheet("background-color: #2196F3; color: white; padding: 2px 5px; border-radius: 3px;");
        table->setCellWidget(row, 3, moreBtn);

        connect(moreBtn, &QPushButton::clicked, this, [=](){
    QDialog dialog(this);
    dialog.setWindowTitle("بيانات المدرس: " + t.name);
    QVBoxLayout* dlgLayout = new QVBoxLayout(&dialog);

    dlgLayout->addWidget(new QLabel("اسم المدرس: " + t.name));
    dlgLayout->addWidget(new QLabel("رقم الهاتف: " + t.phone));
    dlgLayout->addWidget(new QLabel("المادة: " + t.subject));

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok);
    dlgLayout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);

    dialog.exec();
});


        //btn
        QPushButton* deleteBtn = new QPushButton("🗑️ حذف");
        deleteBtn->setStyleSheet("background-color: #f44336; color: white; padding: 2px 5px; border-radius: 3px;");
        table->setCellWidget(row, 4, deleteBtn);
        connect(deleteBtn, &QPushButton::clicked, this, [=](){
    int ret = QMessageBox::question(this, "تأكيد الحذف", "هل تريد حذف هذا المدرس؟", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        Teacher::deleteTeacher(t.id);// delete
        teachers = Teacher::getAllTeachers(); // get data again
        populateTable(); // refresh
    }
});


        ++row;
    }
}

void TeachersWidget::showAddTeacherDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("إضافة مدرس جديد");

    QFormLayout* form = new QFormLayout(&dialog);
    QLineEdit* nameEdit = new QLineEdit();
    QLineEdit* phoneEdit = new QLineEdit();
    QLineEdit* subjectEdit = new QLineEdit();

    form->addRow("اسم المدرس:", nameEdit);
    form->addRow("رقم الهاتف:", phoneEdit);
    form->addRow("المادة:", subjectEdit);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    form->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, [&](){
        if (nameEdit->text().isEmpty() || phoneEdit->text().isEmpty() || subjectEdit->text().isEmpty()) {
            QMessageBox::warning(&dialog, "خطأ", "يرجى ملء جميع الحقول.");
            return;
        }

        TeacherData t;
        t.name = nameEdit->text();
        t.phone = phoneEdit->text();
        t.subject = subjectEdit->text();

       
        if (Teacher::addTeacher(t)) {
            teachers = Teacher::getAllTeachers(); 
            QMessageBox::information(&dialog, "نجاح", "تم إضافة المدرس بنجاح.");
            dialog.accept();

            populateTable();

            // to send signal to dashboard
            emit teacherAdded(); 
        } else {
            QMessageBox::critical(&dialog, "خطأ", "حدث خطأ أثناء إضافة المدرس.");
        }
    });

    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    dialog.exec();
}
