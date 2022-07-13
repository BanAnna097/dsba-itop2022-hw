#include "addrowdialog.h"
#include "ui_addrowdialog.h"
#include "confirmcancel.h"
#include <QMessageBox>

AddRowDialog::AddRowDialog(QWidget *parent, QString id, QString name, QString gender, QString date, QString position, QString email, QString phone) :
    QDialog(parent),
    ui(new Ui::AddRowDialog),
    id(id)
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(name);
    ui->genderComboBox->setCurrentText(gender);
    QDate birth = QDate::fromString(date, "dd.MM.yyyy");
    ui->birthDateEdit->setDate(birth);
    ui->comboBox->setCurrentText(position);
    ui->phoneLineEdit->setText(phone);
    ui->emailLineEdit->setText(email);

    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveAddedRow()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

void AddRowDialog::cancel()
{
    ConfirmCancel d(this);
    if (d.exec() == QDialog::Accepted)
        reject();
}

void AddRowDialog::saveAddedRow()
{
    newRow.push_back(id);
    newRow.push_back(ui->nameLineEdit->text());
    newRow.push_back(ui->genderComboBox->currentText());
    newRow.push_back(ui->birthDateEdit->text());
    newRow.push_back(ui->comboBox->currentText());
    newRow.push_back(ui->emailLineEdit->text());
    newRow.push_back(ui->phoneLineEdit->text());

    QMessageBox::information(this, "Success!", "Profile added");

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

