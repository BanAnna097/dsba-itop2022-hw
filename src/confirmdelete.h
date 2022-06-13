#ifndef CONFIRMDELETE_H
#define CONFIRMDELETE_H

#include <QDialog>

namespace Ui {
class ConfirmDelete;
}

class ConfirmDelete : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmDelete(QWidget *parent = nullptr);
    ~ConfirmDelete();

private:
    Ui::ConfirmDelete *ui;
};

#endif // CONFIRMDELETE_H
