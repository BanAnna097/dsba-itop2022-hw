#include "confirmdelete.h"
#include "ui_confirmdelete.h"

ConfirmDelete::ConfirmDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmDelete)
{
    ui->setupUi(this);
    QObject::connect(ui->yesButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(ui->noButton, SIGNAL(clicked()), this, SLOT(reject()));
}

ConfirmDelete::~ConfirmDelete()
{
    delete ui;
}
