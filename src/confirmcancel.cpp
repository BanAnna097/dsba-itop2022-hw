#include "confirmcancel.h"
#include "ui_confirmcancel.h"

ConfirmCancel::ConfirmCancel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmCancel)
{
    ui->setupUi(this);
    QObject::connect(ui->yesButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(ui->noButton, SIGNAL(clicked()), this, SLOT(reject()));
}

ConfirmCancel::~ConfirmCancel()
{
    delete ui;
}





