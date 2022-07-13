#include "comboboxdelegate.h"

#include <QItemDelegate>
#include <QComboBox>

ComboBoxDelegate::ComboBoxDelegate(QObject *parent ):QItemDelegate(parent)
{
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    combo = new QComboBox( parent );
    QObject::connect(combo,SIGNAL(currentIndexChanged(int)),this,SLOT(setData(int)));
    combo->addItems(comboItems);
    combo->setMaxVisibleItems(comboItems.count());
    combo->setEditable(true);
    return combo;
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    model->setData( index, static_cast<QComboBox*>( editor )->currentText() );
}


void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry( option.rect );
}

void ComboBoxDelegate::setData(int val)
{
    emit commitData(combo);
    //emit closeEditor(combo);
}
