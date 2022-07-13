#include "colordelegate.h"

#include <QPainter>
#include <QAbstractItemView>

ColorDelegate::ColorDelegate(QObject* parent, Qt::GlobalColor color) : BaseClass(parent), color(color)
{
}

void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    if (QAbstractItemView* tableView = qobject_cast<QAbstractItemView*>(this->parent()))
//        painter->fillRect(option.rect, color);
    painter->fillRect(option.rect, color);
    BaseClass::paint(painter, option, index);
}
