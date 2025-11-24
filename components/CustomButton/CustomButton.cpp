#include "CustomButton.h"

CustomButton::CustomButton(QWidget *parent,
                           const QString &text,
                           const QString &bgColor,
                           const QString &hoverColor,
                           const QString &pressedColor)
    : QPushButton(text, parent)
{
    setStyleSheet(QString(R"(
        QPushButton {
            background-color: %1;
            color: white;
            font-size: 16px;
            font-weight: bold;
            border-radius: 10px;
            padding: 10px;
        }
        QPushButton:hover { background-color: %2; }
        QPushButton:pressed { background-color: %3; }
    )").arg(bgColor, hoverColor, pressedColor));
    //3️⃣ %1, %2, %3 و .arg(bgColor, hoverColor, pressedColor)
    //%1, %2, %3 هي placeholders.
}
