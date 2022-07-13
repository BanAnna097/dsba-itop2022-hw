#include "dateeditdelegate.h"

#include <QItemDelegate>
#include <QDateEdit>

DateEditDelegate::DateEditDelegate(QObject *parent ) : QItemDelegate(parent)
{
}

QWidget *DateEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    combo = new QDateEdit(parent);
    return combo;
}

void DateEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    model->setData( index, static_cast<QDateEdit*>( editor )->text() );
}


void DateEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry( option.rect );
}

void DateEditDelegate::setData(int val)
{
}
