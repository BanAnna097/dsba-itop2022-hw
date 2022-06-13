#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrowdialog.h"
#include "./ui_addrowdialog.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "confirmdelete.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(loadFile()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    QObject::connect(ui->editButton, SIGNAL(clicked()), this, SLOT(editRowSlot()));
    QObject::connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addRowSlot()));
    QObject::connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(search()));
    QObject::connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteRowSlot()));
    QObject::connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeActiveRow(QModelIndex)));

    _universityModel = new UniversityModel(this);
    ui->tableView->setModel(_universityModel);
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{

}

void MainWindow::loadFile()
{
    delete _universityModel;

    _universityModel = new UniversityModel(this);
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "../",
                                                    "Data (*.csv)");
    _universityModel->fillDataTableFromFile(fileName);
    ui->tableView->setModel(_universityModel);

}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Open File",
                                                    "../",
                                                    "Data (*.csv)");
    _universityModel->saveDataTableToFile(fileName);
}

void MainWindow::addRowSlot()
{
    AddRowDialog d(this);
    if (d.exec() == QDialog::Accepted)
    {
        _universityModel->appendRow(d.getNewRow());
    }
}

void MainWindow::editRowSlot()
{
    _universityModel->removeRow((ui->tableView->currentIndex()).row());
    AddRowDialog d(this);
    if (d.exec() == QDialog::Accepted)
    {
        _universityModel->appendRow(d.getNewRow());
    }
}

void MainWindow::deleteRowSlot()
{
    ConfirmDelete d(this);
    if (d.exec() == QDialog::Accepted)
    {
        _universityModel->removeRow((ui->tableView->currentIndex()).row());
    }
}

void MainWindow::showAbout()
{
    AboutDialog d;
    d.exec();
}

void MainWindow::search()
{
    SearchDialog d(this);
    d.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
