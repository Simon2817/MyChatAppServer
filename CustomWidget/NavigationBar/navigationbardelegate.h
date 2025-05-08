#ifndef NAVIGATIONBARDELEGATE_H
#define NAVIGATIONBARDELEGATE_H

#include "itemdata.h"

#include <QStyledItemDelegate>



class NavigationBarDelegate : public QStyledItemDelegate
{
public:
    NavigationBarDelegate(ItemData *itemData, QObject *parent = nullptr);

protected:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    ItemData *m_itemData;
};

#endif // NAVIGATIONBARDELEGATE_H
