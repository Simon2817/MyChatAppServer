#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QPainter>
#include <QStandardItem>
#include <QStyleOptionViewItem>

class ItemData : public QObject
{
    Q_OBJECT
public:
    explicit ItemData(QString filePath, QStandardItemModel *model, QObject *parent = nullptr);
    // 解析josn文件
    void processJsonFile(QString filePath);
    // 生成标题栏item对象
    void genericNavigationBar();
    // json对象转item对象
    QStandardItem *jsonObjectToStandardItem(QJsonObject jsonObject);
    // 给根item对象添加子节点
    void addItemChild(QStandardItem *item);
    // 对item在Delegate中的paint函数的重写
    void paintClassOutOverried(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);
signals:

private:
    // 要处理的itemModel
    QStandardItemModel *m_model;

    // 要处理的json数据
    QJsonObject m_jsonRoot;

    // 自定义设置的字段队列
    QJsonArray m_argArray;
    // 最后一个字段为孩子字段（子标签字段）
    int m_childUserRole;
    // 标题队列
    QJsonArray m_navigationBarArray;
};

#endif // ITEMDATA_H
