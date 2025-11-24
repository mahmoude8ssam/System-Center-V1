#include "HomeWidget.h"
#include <QFont>
#include <QScrollArea>

HomeWidget::HomeWidget(QWidget *parent) : QWidget(parent) {
    mainLayout = new QHBoxLayout(this);
    setWindowTitle("System Center");


    // ========================
    // (Menu)
    // ========================
    menuLayout = new QVBoxLayout();

    dashboardBtn = new QPushButton("لوحة التحكم");
    groupsBtn    = new QPushButton("المجموعات");
    gradesBtn    = new QPushButton("المراحل");
    studentsBtn  = new QPushButton("الطلبة");
    lessonsBtn   = new QPushButton("الحصص");
    teachersBtn  = new QPushButton("المدرسين");
    settingsBtn  = new QPushButton("الإعدادات");

    allButtons = { dashboardBtn, groupsBtn, gradesBtn, studentsBtn, lessonsBtn, teachersBtn, settingsBtn };

    for (auto* btn : allButtons) {
        btn->setFixedHeight(45);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(
            "QPushButton {"
            " background-color: #2d3436;"
            " color: white;"
            " border: none;"
            " font-size: 15px;"
            " border-radius: 8px;"
            " text-align: right;"
            " padding-right: 15px;"
            "}"
            "QPushButton:hover { background-color: #636e72; }"
        );
        menuLayout->addWidget(btn);
    }

    menuLayout->addStretch();

    QFrame* menuFrame = new QFrame();
    menuFrame->setLayout(menuLayout);
    menuFrame->setFrameShape(QFrame::StyledPanel);
    menuFrame->setStyleSheet("background-color: #1e272e;");
    menuFrame->setFixedWidth(200);

    // ========================
    //  content (StackedWidget)
    // ========================
    stackedWidget = new QStackedWidget();

    
    dashboardPage = new DashboardWidget();


   
    groupsPage = new GroupsWidget();

   
    gradesPage = new GradesWidget();

    studentsPage = new StudentsWidget();

    //lessonsPage = new LessonsWidget();

    teachersPage = new TeachersWidget();

    settingsPage = new QWidget();
    {
        QVBoxLayout* layout = new QVBoxLayout(settingsPage);
        layout->addWidget(new QLabel("صفحة الإعدادات ⚙️"));
        layout->addStretch();
    }

    // add pages
    stackedWidget->addWidget(dashboardPage);
    stackedWidget->addWidget(groupsPage);
    stackedWidget->addWidget(gradesPage);
    stackedWidget->addWidget(studentsPage);
    //stackedWidget->addWidget(lessonsPage);
    stackedWidget->addWidget(teachersPage);
    stackedWidget->addWidget(settingsPage);

    // intial
    stackedWidget->setCurrentIndex(0);
    updateActiveButton(dashboardBtn);

    QVBoxLayout* contentLayout = new QVBoxLayout();
    contentLayout->addWidget(stackedWidget);   // primary content here
    auto footer = new FooterWidget(this);
contentLayout->addWidget(footer);          // fixed foot for all pages
contentLayout->setStretch(0, 1);          // خلي الـ stackedWidget ياخد المساحة الأكبر
contentLayout->setStretch(1, 0);          // الفوتر ياخد مساحته فقط

QWidget* contentWidget = new QWidget();
contentWidget->setLayout(contentLayout);
    // ========================
    // comine
    // ========================
    mainLayout->addWidget(contentWidget);
    mainLayout->addWidget(menuFrame);

    // ========================
    // connect signals
    // ========================

connect(studentsPage, &StudentsWidget::studentAdded, dashboardPage, &DashboardWidget::refreshData, Qt::QueuedConnection);
connect(teachersPage, &TeachersWidget::teacherAdded, dashboardPage, &DashboardWidget::refreshData, Qt::QueuedConnection);





    connect(dashboardBtn, &QPushButton::clicked, this, [=](){ showPage(0); updateActiveButton(dashboardBtn); });
    connect(groupsBtn,    &QPushButton::clicked, this, [=](){ showPage(1); updateActiveButton(groupsBtn); });
    connect(gradesBtn,    &QPushButton::clicked, this, [=](){ showPage(2); updateActiveButton(gradesBtn); });
    connect(studentsBtn,  &QPushButton::clicked, this, [=](){ showPage(3); updateActiveButton(studentsBtn); });
    connect(lessonsBtn,   &QPushButton::clicked, this, [=](){ showPage(4); updateActiveButton(lessonsBtn); });
    connect(teachersBtn,  &QPushButton::clicked, this, [=](){ showPage(5); updateActiveButton(teachersBtn); });
    connect(settingsBtn,  &QPushButton::clicked, this, [=](){ showPage(6); updateActiveButton(settingsBtn); });
}

// ========================
// fn
// ========================
void HomeWidget::showPage(int index) {
    stackedWidget->setCurrentIndex(index);
}

void HomeWidget::updateActiveButton(QPushButton* activeButton) {
    for (auto* btn : allButtons) {
        if (btn == activeButton) {
            btn->setStyleSheet(
                "QPushButton {"
                " background-color: #0984e3;"
                " color: white;"
                " border: none;"
                " font-weight: bold;"
                " border-radius: 8px;"
                " text-align: right;"
                " padding-right: 15px;"
                "}"
                "QPushButton:hover { background-color: #8e0220ff; }"
            );
        } else {
            btn->setStyleSheet(
                "QPushButton {"
                " background-color: #2d3436;"
                " color: white;"
                " border: none;"
                " font-size: 15px;"
                " border-radius: 8px;"
                " text-align: right;"
                " padding-right: 15px;"
                "}"
                "QPushButton:hover { background-color: #636e72; }"
            );
        }
    }
}
