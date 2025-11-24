#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QFrame>
#include "../../components/CardWidget/CardWidget.h"
#include "../../models/User/User.h"
#include "../DashboardWidget/DashboardWidget.h"
#include "../GroupsWidget/GroupsWidget.h"
#include "../StudentsWidget/StudentsWidget.h"
#include "../TeachersWidget/TeachersWidget.h"
//#include "../LessonsWidget/LessonsWidget.h"
#include "../GradesWidget/GradesWidget.h"
#include "../../components/FooterWidget/FooterWidget.h"
class HomeWidget : public QWidget {
    Q_OBJECT
public:
    explicit HomeWidget(QWidget *parent = nullptr);

private slots:
    void showPage(int index);
    void updateActiveButton(QPushButton* activeButton);

private:
    QHBoxLayout* mainLayout;
    QVBoxLayout* menuLayout;
    QStackedWidget* stackedWidget;


    // الأزرار
    QPushButton* dashboardBtn;
    QPushButton* groupsBtn;
    QPushButton* gradesBtn;
    QPushButton* studentsBtn;
    QPushButton* lessonsBtn;
    QPushButton* teachersBtn;
    QPushButton* settingsBtn;

    QList<QPushButton*> allButtons;

    // الصفحات
    DashboardWidget* dashboardPage;
    QWidget* groupsPage;
    QWidget* gradesPage;
    StudentsWidget* studentsPage;
    QWidget* lessonsPage;
    TeachersWidget* teachersPage;
    QWidget* settingsPage;

};
