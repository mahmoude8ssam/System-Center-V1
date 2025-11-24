
#include <QLineEdit>
#include <QString>

class CustomInput : public QLineEdit {
    Q_OBJECT
public:
    explicit CustomInput(QWidget *parent = nullptr,
                         const QString &placeholder = "",
                         bool isPassword = false);
};
