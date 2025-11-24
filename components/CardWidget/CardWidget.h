// CardWidget.h
#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QPixmap>

class CardWidget : public QWidget {
    Q_OBJECT
public:
    explicit CardWidget(
                        const QString &title,
                        int number,
                        QWidget *parent = nullptr);
 void updateValue(int newValue); 
private:

    QLabel* titleLabel;
    QLabel* numberLabel;
};
