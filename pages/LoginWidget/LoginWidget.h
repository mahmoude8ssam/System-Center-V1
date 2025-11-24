#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "../HomeWidget/HomeWidget.h"
#include "../../components/CustomButton/CustomButton.h"
#include "../../components/FooterWidget/FooterWidget.h"
#include "../../components/CustomInput/CustomInput.h"
#include "../../models/User/User.h"
#include <QMessageBox>
#include <QSpacerItem>
class LoginWidget : public QWidget {
    Q_OBJECT
public:
    LoginWidget(QWidget *parent = nullptr);

signals:
    void loginSuccessful();

private slots:
    void handleLogin();

private:
    QVBoxLayout* layout;
    CustomInput* Email;
    CustomInput* Pass;
    //QLineEdit* Pass;
    HomeWidget* home;
    QPushButton* loginButton;
    QLabel* infoLabel;
};
