// CardWidget.cpp
#include "CardWidget.h"

CardWidget::CardWidget(
                       const QString &title,
                       int number,
                       QWidget *parent)
    : QWidget(parent)
{
    // tit;e
    titleLabel = new QLabel(title, this);
    QFont titleFont;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    // count below
    numberLabel = new QLabel(QString::number(number), this);
    QFont numberFont;
    numberFont.setPointSize(18);
    numberFont.setBold(true);
    numberLabel->setFont(numberFont);
    numberLabel->setStyleSheet("color: #4CAF50");
    numberLabel->setAlignment(Qt::AlignCenter);

    // Arrange items vertically
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addSpacing(5);
    layout->addWidget(titleLabel);
    layout->addWidget(numberLabel);
    layout->addStretch();
    layout->setContentsMargins(15, 15, 15, 15);

    setLayout(layout);

    
    setStyleSheet(R"(
        QWidget {
            background-color: #ffffff;
            border-radius: 12px;
            padding: 10px;
            border: 1px solid #ddd;
        }
        QWidget:hover {
            background-color: #f5f5f5;
            border: 1px solid #aaa;
        }
    )");


}

void CardWidget::updateValue(int newValue) {
    numberLabel->setText(QString::number(newValue));
}