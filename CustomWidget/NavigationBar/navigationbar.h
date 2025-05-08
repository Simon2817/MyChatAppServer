#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include "navigationbardelegate.h"

#include <QStandardItem>
#include <QStyledItemDelegate>
#include <QTreeView>

class NavigationBar : public QTreeView
{
    Q_OBJECT
public:
    explicit NavigationBar(QWidget *parent = nullptr);
    // 给item添加子节点（通过层次遍历是实现）
    void addItemChildren(QStandardItem *item);
    // 将json对象转换成QStandardItem对象
    QStandardItem *jsonObjectToStandardItem(QJsonObject jsonObject);

signals:

public slots:
    void on_QTreeView_clicked(const QModelIndex &index);


private:
    QStandardItemModel *m_Model;
    NavigationBarDelegate *m_Delegate;
};

#endif // NAVIGATIONBAR_H
