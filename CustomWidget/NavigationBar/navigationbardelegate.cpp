#include "navigationbardelegate.h"

#include <QPainter>
#include <QDebug>


NavigationBarDelegate::NavigationBarDelegate(ItemData *itemData, QObject *parent)
{
    m_itemData = itemData;
}

QSize NavigationBarDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 60);
}

void NavigationBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    m_itemData->paintClassOutOverried(painter, option, index);
    QStyledItemDelegate::paint(painter, option, index);
}

