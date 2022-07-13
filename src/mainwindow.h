#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "universitymodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadFile();
    void saveFile();
    void addRowSlot();
    void editRowSlot();
    void deleteRowSlot();
    void showAbout();
    void search();
    void updateFilter(const QString & text);
    void filterStudents();
    void colorGenders();
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    size_t _shownDetailsColumn;
    UniversityModel *_universityModel;
    QSortFilterProxyModel *proxyModel;
    Ui::MainWindow *ui;
    bool colored = false;
};
#endif // MAINWINDOW_H
