// CustomInput.cpp
#include "CustomInput.h"

CustomInput::CustomInput(QWidget *parent, const QString &placeholder, bool isPassword)
    : QLineEdit(parent)
{
    setPlaceholderText(placeholder);
    if (isPassword)
        setEchoMode(QLineEdit::Password);

    QString lineEditStyle = R"(
        QLineEdit {
            background-color: #2e2e40;
            color: white;
            border: 2px solid #3f3f5f;
            border-radius: 10px;
            padding: 8px;
            font-size: 16px;
        }
        QLineEdit:focus {
            border-color: #00b4d8;
            background-color: #3a3a55;
        }
    )";

    setStyleSheet(lineEditStyle);
}
