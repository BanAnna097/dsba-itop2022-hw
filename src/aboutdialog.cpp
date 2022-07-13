#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void LogoWidget::paintEvent (QPaintEvent */*event*/)
{
  QPainter painter (this);
  // Pen    lines,
  // Brush  fill
  painter.setBackground(QBrush (Qt::white));
  painter.setPen (QPen(Qt::green));
  painter.setBrush (QBrush(Qt::red));

  QPoint center_widget (width () / 2, height () / 2);
  int radius   = std::min (width (), height ()) / 3;
  painter.drawEllipse (center_widget, radius, radius);
}
