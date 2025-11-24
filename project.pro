QT += core sql gui widgets charts
CONFIG += c++17

include(components/CardWidget/CardWidget.pri)
include(components/CustomInput/CustomInput.pri)
include(components/CustomButton/CustomButton.pri)
include(components/FooterWidget/FooterWidget.pri)
include(pages/LoginWidget/LoginWidget.pri)
include(pages/HomeWidget/HomeWidget.pri)
include(pages/DashboardWidget/DashboardWidget.pri)
include(pages/StudentsWidget/StudentsWidget.pri)
include(pages/TeachersWidget/TeachersWidget.pri)
include(pages/GradesWidget/GradesWidget.pri)
include(pages/GroupsWidget/GroupsWidget.pri)
include(pages/LessonsWidget/LessonsWidget.pri)
include(models/User/User.pri)
include(models/Teacher/Teacher.pri)
include(models/Group/Group.pri)
include(models/Student/Student.pri)
include(models/Stage/Stage.pri)
include(forms/Student/AddStudentForm.pri)

SOURCES += main.cpp