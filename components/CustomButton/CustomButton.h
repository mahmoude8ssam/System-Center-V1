#include <QPushButton>
#include <QString>

class CustomButton : public QPushButton {
    Q_OBJECT
public:
    explicit CustomButton(QWidget *parent = nullptr,
                          const QString &text = "",
                          const QString &bgColor = "#00b4d8",
                          const QString &hoverColor = "#0077b6",
                          const QString &pressedColor = "#023e8a");
};
