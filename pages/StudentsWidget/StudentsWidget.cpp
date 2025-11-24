// StudentsWidget.cpp
#include "StudentsWidget.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QRegularExpressionValidator>


StudentsWidget::StudentsWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    
    QHBoxLayout* topLayout = new QHBoxLayout();

    // =============================
    // search input
    // =============================
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("ابحث عن الطالب...");
    searchEdit->setStyleSheet("padding: 5px; font-size: 14px; border: 1px solid #ccc; border-radius: 5px;");
    topLayout->addWidget(searchEdit, 1); // 1 = stretch factor

    // btn
    QPushButton* addBtn = new QPushButton("إضافة طالب", this);
    addBtn->setStyleSheet("background-color: #f39c12; color: white; border-radius: 5px; padding: 5px 15px;");
    topLayout->addWidget(addBtn); 

    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(10); 

    // get data
    students = Student::getAllStudents();

    // table
    table = new QTableWidget(this);
    table->setColumnCount(9);
    QStringList headers = {"اسم الطالب", "رقم الطالب", "رقم ولى الأمر", "المجموعة", "المرحلة", "إنذار الغياب", "عرض البيانات", "تعديل البيانات", "واتساب"};
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainLayout->addWidget(table);

    populateTable();

    setLayout(mainLayout);

    // connect seach input with data table
    connect(searchEdit, &QLineEdit::textChanged, this, [=](const QString &text){
        populateTable(text);
    });

    // add btn 
    connect(addBtn, &QPushButton::clicked, this, &StudentsWidget::openAddStudentForm);


}


void StudentsWidget::populateTable(const QString& filter) {
    table->setRowCount(0);
    int row = 0;
    for (const StudentData& s : students) {
        if (!filter.isEmpty() && !s.name.contains(filter, Qt::CaseInsensitive)) continue;

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(s.name));
        table->setItem(row, 1, new QTableWidgetItem(s.phone));
        table->setItem(row, 2, new QTableWidgetItem(s.phoneParent));
        table->setItem(row, 3, new QTableWidgetItem(s.groupName));
        table->setItem(row, 4, new QTableWidgetItem(s.stage));

        
        QLabel* warningLabel = new QLabel(this);
        if (s.absenceWarning) {
            warningLabel->setText("غائب آخر حصتين");
            warningLabel->setStyleSheet("background-color: red; color: white; font-weight: bold; padding: 3px; border-radius: 5px; text-align: center;");
        }
        table->setCellWidget(row, 5, warningLabel);

        
        QPushButton* viewBtn = new QPushButton("عرض", this);
        viewBtn->setStyleSheet("background-color: #4CAF50; color: white; border-radius: 5px; padding: 3px;");
        table->setCellWidget(row, 6, viewBtn);
        connect(viewBtn, &QPushButton::clicked, this, [=](){
            QMessageBox::information(this, "بيانات الطالب", 
                                     "الاسم: " + s.name + "\nرقم الطالب: " + s.phone + "\nالمجموعة: " + s.groupName + "\nالمرحلة: " + s.stage);
        });

        // edit btn
        QPushButton* editBtn = new QPushButton("تعديل", this);
        editBtn->setStyleSheet("background-color: #2196F3; color: white; border-radius: 5px; padding: 3px;");
        table->setCellWidget(row, 7, editBtn);
        connect(editBtn, &QPushButton::clicked, this, [=](){
            QMessageBox::information(this, "تعديل", "هنا يمكنك تعديل بيانات " + s.name);
        });

        // wapp btn
        QPushButton* whatsappBtn = new QPushButton("واتساب", this);
        whatsappBtn->setStyleSheet("background-color: #25D366; color: white; border-radius: 5px; padding: 3px;");
        table->setCellWidget(row, 8, whatsappBtn);
        connect(whatsappBtn, &QPushButton::clicked, this, [=](){
            QString url = "https://wa.me/+2" + s.phoneParent;
            QDesktopServices::openUrl(QUrl(url));
        });

        ++row;
    }
}




void StudentsWidget::openAddStudentForm() {
    QDialog* form = new QDialog(this); 
    form->setWindowTitle("إضافة طالب جديد");
    form->setModal(true);

    QVBoxLayout* mainLayout = new QVBoxLayout(form);
    QFormLayout* formLayout = new QFormLayout();

    QLineEdit* nameEdit = new QLineEdit();
    QLineEdit* phoneEdit = new QLineEdit();
    QLineEdit* phoneParentEdit = new QLineEdit();
    QLineEdit* groupEdit = new QLineEdit();
    QLineEdit* stageEdit = new QLineEdit();

    QRegularExpression rx("\\d{11}");
    phoneEdit->setValidator(new QRegularExpressionValidator(rx, form));
    phoneParentEdit->setValidator(new QRegularExpressionValidator(rx, form));

    formLayout->addRow("اسم الطالب:", nameEdit);
    formLayout->addRow("رقم الطالب:", phoneEdit);
    formLayout->addRow("رقم ولى الأمر:", phoneParentEdit);
    formLayout->addRow("المجموعة:", groupEdit);
    formLayout->addRow("المرحلة:", stageEdit);

    mainLayout->addLayout(formLayout);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QPushButton* saveBtn = new QPushButton("حفظ");
    QPushButton* cancelBtn = new QPushButton("إلغاء");
    buttonsLayout->addWidget(saveBtn);
    buttonsLayout->addWidget(cancelBtn);
    mainLayout->addLayout(buttonsLayout);

    QObject::connect(cancelBtn, &QPushButton::clicked, form, &QDialog::reject);

    QObject::connect(saveBtn, &QPushButton::clicked, [=]() {
        if (nameEdit->text().isEmpty() || phoneEdit->text().isEmpty() || phoneParentEdit->text().isEmpty()
            || groupEdit->text().isEmpty() || stageEdit->text().isEmpty()) {
            QMessageBox::warning(form, "خطأ", "يرجى ملء جميع الحقول.");
            return;
        }

        if (phoneEdit->text().length() != 11 || phoneParentEdit->text().length() != 11) {
            QMessageBox::warning(form, "خطأ", "رقم الطالب وولي الأمر يجب أن يكون 11 رقمًا.");
            return;
        }

        StudentData s;
        s.name = nameEdit->text();
        s.phone = phoneEdit->text();
        s.phoneParent = phoneParentEdit->text();
        s.groupName = groupEdit->text();
        s.stage = stageEdit->text();

        if (Student::addStudent(s)) {
            students = Student::getAllStudents();
            populateTable(searchEdit->text());
            form->accept();          // close form firstly
            emit studentAdded();     // send signal
            QMessageBox::information(nullptr, "نجاح", "تم إضافة الطالب بنجاح.");
        } else {
            QMessageBox::critical(form, "خطأ", "حدث خطأ أثناء إضافة الطالب.");
        }
    });

    form->exec();
}

