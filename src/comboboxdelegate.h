#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <QComboBox>

class ComboBoxDelegate: public QItemDelegate
{
 Q_OBJECT
public:
    ComboBoxDelegate(QObject *parent = 0);

    QWidget *createEditor( QWidget *parent,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index ) const;

    void setModelData( QWidget *editor,
                            QAbstractItemModel *model,
                            const QModelIndex &index ) const;

    void updateEditorGeometry( QWidget *editor,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index ) const;

    QStringList comboItems = {"M", "F"};

    mutable QComboBox *combo;

private slots:

    void setData(int val);

};

#endif // COMBOBOXDELEGATE_H
