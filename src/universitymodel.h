#ifndef UNIVERSITYMODEL_H
#define UNIVERSITYMODEL_H

#include <QAbstractTableModel>

class UniversityModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit UniversityModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void fillDataTableFromFile(QString path);
    void saveDataTableToFile(QString path);
    void appendRow(const QList<QString> &row);
    void removeRow(int idx);

private:
    QList<QList<QString>> dataTable;
    QList<QString> headerList;
};

#endif // UNIVERSITYMODELL_H
