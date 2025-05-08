#include "itemdata.h"
#include "navigationbar.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQueue>

NavigationBar::NavigationBar(QWidget *parent) : QTreeView(parent)
{
    // 给视图设置模型
    m_Model = new QStandardItemModel(this);
    this->setModel(m_Model);

    // 隐藏头表
    this->setHeaderHidden(true);
    // 去掉下拉按钮（三角按钮）
    this->setRootIsDecorated(false);
    // 设置视图的编辑方式
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 通过自定义的ItemData给m_Model模型设置item项
    ItemData *itemData = new ItemData(":/resource/navigation_bar.json", m_Model, this);
    itemData->genericNavigationBar();

    // 给视图设置代理
    m_Delegate = new NavigationBarDelegate(itemData, this);
    this->setItemDelegate(m_Delegate);

    /* 信号与槽 */
    connect(this, &QTreeView::clicked, this, &NavigationBar::on_QTreeView_clicked);
}


void NavigationBar::addItemChildren(QStandardItem *item)
{
    QQueue<QStandardItem*> queue;
    queue.enqueue(item);
    while (!queue.isEmpty())
    {
        // 被遍历的当前根点出队
        QStandardItem *rootItem = queue.dequeue();
        // 遍历rootItem的孩子节点
        QJsonArray children = rootItem->data(Qt::UserRole + 2).toJsonArray();
//        qDebug() << "rootItem->data(Qt::UserRole + 2): " << rootItem->data(Qt::UserRole + 2);
//        qDebug() << "children: " << children;
        for (auto child : children)
        {
            // 为当前的子树的根节点，添加其子节点
            QStandardItem *childItem = jsonObjectToStandardItem(child.toObject());
            childItem->setData(child.toObject()["chidren"].toArray(), Qt::UserRole + 2);
            rootItem->appendRow(childItem);

            // 将孩子入队
            queue.enqueue(childItem);
        }
    }
}

QStandardItem *NavigationBar::jsonObjectToStandardItem(QJsonObject jsonObject)
{
    QStandardItem *item = new QStandardItem();
    item->setData(jsonObject["title"].toString(), Qt::UserRole);
    item->setData(jsonObject["img"].toString(), Qt::UserRole + 1);
    item->setData(jsonObject["children"].toArray(), Qt::UserRole + 2);

//    qDebug() << "jsonObjectToStandardItem('chidren'): " << item->data(Qt::UserRole + 2).toJsonArray();
    return item;
}


void NavigationBar::on_QTreeView_clicked(const QModelIndex &index)
{
    qDebug() << index.data() << "被点击";
    if (this->isExpanded(index))
    {
        this->setExpanded(index, false);
    }
    else
    {
        this->expand(index);
    }

}
