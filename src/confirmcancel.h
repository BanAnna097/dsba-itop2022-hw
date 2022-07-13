#ifndef CONFIRMCANCEL_H
#define CONFIRMCANCEL_H

#include <QDialog>

namespace Ui {
class ConfirmCancel;
}

class ConfirmCancel : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmCancel(QWidget *parent = nullptr);
    ~ConfirmCancel();

private:
    Ui::ConfirmCancel *ui;
};

#endif // CONFIRMCANCEL_H
