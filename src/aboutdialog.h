#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QPainter>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

private:
    Ui::AboutDialog *ui;
};

class LogoWidget : public QWidget
{
  Q_OBJECT
public:
  LogoWidget (QWidget */*parent*/) {}
protected:
  void paintEvent (QPaintEvent *event) override;
};

#endif // ABOUTDIALOG_H
