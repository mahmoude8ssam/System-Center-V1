#include "FooterWidget.h"

FooterWidget::FooterWidget(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    //auto *footerLabel = new QLabel("Developed by Three Man in middle", this);
    auto *footerLabel = new QLabel("Developed by Eng/ Mahmoud Essam", this);

    footerLabel->setAlignment(Qt::AlignCenter);
    footerLabel->setStyleSheet("color: #888; font-size: 22px; font-style: italic; margin-top: 0px;");

    layout->addWidget(footerLabel);
    layout->setContentsMargins(0, 10, 0, 0);
}
