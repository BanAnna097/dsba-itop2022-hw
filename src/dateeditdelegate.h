#ifndef DATEEDITDELEGATE_H
#define DATEEDITDELEGATE_H

#include <QItemDelegate>
#include <QDateEdit>

class DateEditDelegate: public QItemDelegate
{
 Q_OBJECT
public:
    DateEditDelegate(QObject *parent = 0);

    QWidget *createEditor( QWidget *parent,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index ) const;

    void setModelData( QWidget *editor,
                            QAbstractItemModel *model,
                            const QModelIndex &index ) const;

    void updateEditorGeometry( QWidget *editor,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index ) const;

    mutable QDateEdit *combo;

private slots:

    void setData(int val);

};

#endif // DATEEDITDELEGATE_H
