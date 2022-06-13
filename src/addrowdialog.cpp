#include "addrowdialog.h"
#include "ui_addrowdialog.h"
#include <QMessageBox>

AddRowDialog::AddRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRowDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveAddedRow()));
}

void AddRowDialog::saveAddedRow()
{
    newRow.push_back(ui->nameLineEdit->text());
    newRow.push_back(ui->nameLineEdit->text());
    newRow.push_back(ui->comboBox->currentText());
    newRow.push_back(ui->genderLineEdit->text());
    newRow.push_back(ui->birthLineEdit->text());
    newRow.push_back(ui->phoneLineEdit->text());
    newRow.push_back(ui->emailLineEdit->text());

    QMessageBox::information(this, "Success!", "New profile added");

    accept();
}

const QList<QString>& AddRowDialog::getNewRow()
{
    return newRow;
}


AddRowDialog::~AddRowDialog()
{
    delete ui;
}

