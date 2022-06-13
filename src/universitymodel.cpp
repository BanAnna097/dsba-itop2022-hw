#include "universitymodel.h"
#include <QFile>

UniversityModel::UniversityModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}


void UniversityModel::fillDataTableFromFile(QString path)
{
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    QString firstline = inputStream.readLine();
    for (QString& item : firstline.split(";")) {
        headerList.append(item);
    }

    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();

        QList<QString> dataRow;
        for (QString& item : line.split(";")) {
            dataRow.append(item);
        }
        dataTable.append(dataRow);
    }
    inputFile.close();
}

void UniversityModel::saveDataTableToFile(QString path)
{
    QFile outputFile(path);
    outputFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream outputStream(&outputFile);

    bool first = true;
    for (QString& item : headerList) {
        if (first)
        {
            outputStream << item;
            first = false;
        }
        else
        {
            outputStream << ";";
            outputStream << item;
        }
    }
    outputStream << "\n";

    for (QList<QString>& row: dataTable)
    {
        bool first = true;
        for (QString& item : row) {
            if (first)
            {
                outputStream << item;
                first = false;
            }
            else
            {
                outputStream << ";";
                outputStream << item;
            }
        }
        outputStream << "\n";
    }

    outputFile.close();
}

int UniversityModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return dataTable.size();
}

int UniversityModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (dataTable.empty())
    {
        return 0;
    }

    return dataTable[0].size();
}

QVariant UniversityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headerList[section];
    }
    return QVariant();
}

QVariant UniversityModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int row = index.row();
        int col = index.column();
        return dataTable[row][col];
    }
    return QVariant();
}

bool UniversityModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        int row = index.row();
        int col = index.column();
        dataTable[row][col] = value.toString();
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags UniversityModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void UniversityModel::appendRow(const QList<QString> &row)
{
    size_t newRowNumber = rowCount();
    beginInsertRows(QModelIndex(), newRowNumber, newRowNumber);
    dataTable.append(row);
    endInsertRows();
}

void UniversityModel::removeRow(int idx)
{
    beginRemoveRows(QModelIndex(), idx, idx);
    dataTable.remove(idx);
    endRemoveRows();
}
