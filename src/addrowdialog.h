#ifndef ADDROWDIALOG_H
#define ADDROWDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class AddRowDialog;
}

class AddRowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRowDialog(QWidget *parent = nullptr, QString id = "", QString name = "", QString gender = "", QString date = "", QString position = "", QString email = "", QString phone = "");
    ~AddRowDialog();
    const QList<QString>& getNewRow();

private slots:
    void saveAddedRow();
    void cancel();


private:
    QList<QString> newRow;
    Ui::AddRowDialog *ui;
    QString id = "0";
};

#endif // ADDROWDIALOG_H
