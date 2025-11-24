#include "LoginWidget.h"
#include <QApplication>
#include <QScreen>

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    // 🟦 عنوان الترحيب
    infoLabel = new QLabel("Welcome to System Center", this);
    infoLabel->setAlignment(Qt::AlignCenter); // center text

    // my class
    Email = new CustomInput(this, "Enter Email");         // غيرنا من QLineEdit لـ CustomInput
    Pass = new CustomInput(this, "Enter Password", true); // true تعني Password

    loginButton = new CustomButton(this, "Login");

    // add to layout
    layout->addWidget(infoLabel);
    layout->addWidget(Email);
    layout->addWidget(Pass);
    layout->addWidget(loginButton);

    // spacing
    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // footer
    auto *footer = new FooterWidget(this);
    layout->addWidget(footer);

    
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(15);
    layout->setContentsMargins(50, 40, 50, 40);

    // first text
    infoLabel->setStyleSheet("background-color: #ff0; color: #000; font-size: 20px; font-weight: bold; text-align: center; padding: 8px; border-radius: 8px;");

    
    connect(loginButton, &QPushButton::clicked, this, &LoginWidget::handleLogin);

    // title and size
    setWindowTitle("System Center");
    resize(600, 400);
}

void LoginWidget::handleLogin()
{
    // here to check
    QString email = Email->text();
    QString pass = Pass->text();
    // now for ex email = 12 and pass = 11 this change when connect api
    if (email == "12" && pass == "11")
    {
        QMessageBox::information(this, "Login", "Login Successful!");

        // create object user
        User::instance().setUserData("Mahmoud Essam", email, 18, "student");
        

        home = new HomeWidget();

        //home->showFullScreen(); حجم كامل
       // home->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);









         QRect available = QApplication::primaryScreen()->availableGeometry();


    int margin = 40;
    QSize newSize(available.width(), available.height() - margin);


    home->move(available.topLeft());
    home->resize(newSize);

    // this dont allow to chang size of window
    home->setFixedSize(newSize);




        //home->resize(QApplication::primaryScreen()->size());
        
    setWindowTitle("System Center");

        home->show();

        this->close(); // close login page
    }
    else
    {

        QMessageBox::warning(this, "error", "error!");
    }
}
