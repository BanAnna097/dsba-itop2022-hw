#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrowdialog.h"
#include "./ui_addrowdialog.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "confirmdelete.h"
#include <QFileDialog>
#include <QRegularExpression>
#include <QAbstractTableModel>

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
    QObject::connect(ui->nameFilterlineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateFilter(const QString &)));
    QObject::connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(search()));
    QObject::connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteRowSlot()));

    _universityModel = new UniversityModel(this);
//    ui->tableView->setModel(_universityModel);
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(_universityModel);
    proxyModel->setFilterKeyColumn(1);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
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
    proxyModel->setSourceModel(_universityModel);
    ui->tableView->setModel(proxyModel);
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

void MainWindow::updateFilter(const QString & text)
{
    proxyModel->setFilterRegularExpression(QRegularExpression(text));
}

MainWindow::~MainWindow()
{
    delete ui;
}
