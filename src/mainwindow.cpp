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
#include <QPainter>
#include <QStandardItem>
#include <QRegularExpressionMatch>
#include <iostream>
#include "comboboxdelegate.h"
#include "colordelegate.h"
#include "dateeditdelegate.h"

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
    QObject::connect(ui->colorGendersCheckBox, SIGNAL(clicked()), this, SLOT(colorGenders()));
    QObject::connect(ui->studentsCheckBox, SIGNAL(clicked()), this, SLOT(filterStudents()));


    _universityModel = new UniversityModel(this);
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(_universityModel);
    proxyModel->setFilterKeyColumn(1);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setItemDelegateForColumn(2, new ComboBoxDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn(3, new DateEditDelegate(ui->tableView));
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
    QModelIndex idx1 = ui->tableView->currentIndex();
    if (idx1.isValid())
    {
        QModelIndex idx2 = proxyModel->mapToSource(idx1);
        QModelIndex index = _universityModel->index(idx2.row(), 1);
        QString name = index.data(Qt::DisplayRole).toString();
        index = _universityModel->index(idx2.row(), 2);
        QString gender = index.data(Qt::DisplayRole).toString();
        index = _universityModel->index(idx2.row(), 3);
        QString date = index.data(Qt::DisplayRole).toString();
        index = _universityModel->index(idx2.row(), 4);
        QString position = index.data(Qt::DisplayRole).toString();
        index = _universityModel->index(idx2.row(), 5);
        QString email = index.data(Qt::DisplayRole).toString();
        index = _universityModel->index(idx2.row(), 6);
        QString phone = index.data(Qt::DisplayRole).toString();
        index = _universityModel->index(idx2.row(), 0);
        QString id = index.data(Qt::DisplayRole).toString();
        AddRowDialog d(this, id, name, gender, date, position, email, phone);
        if (d.exec() == QDialog::Accepted)
        {
            _universityModel->appendRow(d.getNewRow());
            _universityModel->removeRow(idx2.row());
        }
    }
}

void MainWindow::deleteRowSlot()
{
    QModelIndex idx1 = ui->tableView->currentIndex();
    if (idx1.isValid())
    {
        ConfirmDelete d(this);
        if (d.exec() == QDialog::Accepted)
        {
            QModelIndex idx2 = proxyModel->mapToSource(idx1);
            _universityModel->removeRow(idx2.row());
        }
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

void MainWindow::filterStudents()
{
    proxyModel->setFilterKeyColumn(4);
    proxyModel->setFilterRegularExpression(QRegularExpression("Student"));
    ui->colorGendersCheckBox->setCheckState(Qt::Unchecked);
    for (int i = 0; i < proxyModel->rowCount(); i++)
        ui->tableView->setItemDelegateForRow(i, new ColorDelegate(ui->tableView, Qt::white));
    colored = false;
}

void MainWindow::updateFilter(const QString & text)
{
    proxyModel->setFilterKeyColumn(1);
    proxyModel->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
    ui->colorGendersCheckBox->setCheckState(Qt::Unchecked);
    for (int i = 0; i < proxyModel->rowCount(); i++)
        ui->tableView->setItemDelegateForRow(i, new ColorDelegate(ui->tableView, Qt::white));
    colored = false;
}

void MainWindow::colorGenders()
{
    if (!colored)
    {
        for (int i = 0; i < proxyModel->rowCount(); i++)
        {
            QModelIndex index = proxyModel->index(i, 2);
            if (index.data().toString().toStdString() == "M")
                ui->tableView->setItemDelegateForRow(i, new ColorDelegate(ui->tableView, Qt::blue));
            if (index.data().toString().toStdString() == "F")
                ui->tableView->setItemDelegateForRow(i, new ColorDelegate(ui->tableView, Qt::magenta));
        }
        colored = true;
        ui->tableView->setSortingEnabled(false);
    }
    else
    {
        for (int i = 0; i < proxyModel->rowCount(); i++)
            ui->tableView->setItemDelegateForRow(i, new ColorDelegate(ui->tableView, Qt::white));
        colored = false;
        ui->tableView->setSortingEnabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
