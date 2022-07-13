#ifndef COLORDELEGATE_H
#define COLORDELEGATE_H

#include <QStyledItemDelegate>

class ColorDelegate : public QStyledItemDelegate
{
    using BaseClass = QStyledItemDelegate;

public:
    ColorDelegate(QObject* parent = nullptr, Qt::GlobalColor color = Qt::white);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    Qt::GlobalColor color;
};

#endif // COLORDELEGATE_H
