#include "itemdata.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QQueue>


ItemData::ItemData(QString filePath, QStandardItemModel *model, QObject *parent) : QObject(parent)
{
    m_model = model;
    processJsonFile(filePath);
}

void ItemData::processJsonFile(QString filePath) {
    // 获取josn数据
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开文件:" << filePath;
        return;
    }
    else
    {
        qWarning() << "打开文件:" << filePath;
    }
    QByteArray jsonByteArray = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonByteArray, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析错误:" << parseError.errorString();
        return;
    }

    // 3. 处理JSON数据
    if (jsonDoc.isObject())
    {
        m_jsonRoot = jsonDoc.object();
    }
    else if (jsonDoc.isArray()) {
        // 获取根json对象
        qWarning() << "JSON解析错误:" << "遍历到json数组，而非json对象";
    }

    // 获取自定义参数列表
    if (m_jsonRoot["args"].isArray())
        m_argArray = m_jsonRoot["args"].toArray();
    else
        qWarning() << "JSON解析错误:找不到自定义参数队列";
    // 获取标题栏接送对象
    if (m_jsonRoot["data"].isArray())
        m_navigationBarArray = m_jsonRoot["data"].toArray();
    else
        qWarning() << "JSON解析错误:找不到标题栏队列";
}

void ItemData::genericNavigationBar()
{

    for (auto obj : m_navigationBarArray)
    {
        QJsonObject jsonObj = obj.toObject();
        QStandardItem *item = jsonObjectToStandardItem(jsonObj);
        // 添加子标题
        addItemChild(item);
        // 将item添加到model中
        m_model->appendRow(item);
    }
}

QStandardItem *ItemData::jsonObjectToStandardItem(QJsonObject jsonObject)
{
    QStandardItem *item = new QStandardItem();
    int UserRole = Qt::UserRole;
    for (auto it : m_argArray)
    {
        QJsonObject obj = it.toObject();
        // 获取参数名
        QString argName =  obj.keys()[0];
        QString argType = obj.value(argName).toString();
        if (argType == "int")
        {
            int data = jsonObject[argName].toInt();
            // 添加UserRole后，每次要自增
            // 当重写在Delegate中的paint方法时
            // 需要通过Qt::UserRole来解析
            item->setData(data, UserRole++);
        }
        else if (argType == "QString")
        {
            QString data = jsonObject[argName].toString();
            item->setData(data, UserRole++);
        }
        else if (argType == "QJsonArray")
        {
            QJsonArray data = jsonObject[argName].toArray();
            item->setData(data, UserRole++);
        }
//        qDebug() << "UserRole: " << UserRole;
    }
    m_childUserRole = UserRole - 1;
//    qDebug() << "m_childUserRole: " << m_childUserRole;
    return item;
}

void ItemData::addItemChild(QStandardItem *item)
{
    QQueue<QStandardItem*> queue;
    queue.enqueue(item);
    while (!queue.isEmpty())
    {
        // 被遍历的当前根点出队
        QStandardItem *rootItem = queue.dequeue();
        // 遍历rootItem的孩子节点
        QJsonArray children = rootItem->data(m_childUserRole).toJsonArray();
        for (auto child : children)
        {
            // 为当前的子树的根节点，添加其子节点
            QStandardItem *childItem = jsonObjectToStandardItem(child.toObject());
            childItem->setData(child.toObject()["chidren"].toArray(), m_childUserRole);
            rootItem->appendRow(childItem);

            // 将孩子入队
            queue.enqueue(childItem);
        }
    }
}

void ItemData::paintClassOutOverried(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    int UserRole = Qt::UserRole;
    // 预先定义要设置的属性
    QString title;
    QString img;
    int align;
//    int font;

    for (auto it : m_argArray)
    {
        QJsonObject obj = it.toObject();
        // 获取参数名
        QString argName =  obj.keys()[0];
        QString argType = obj.value(argName).toString();

        if (argName == "title")
        {
            title = index.data(UserRole++).toString().toUtf8();
        }
        else if (argName == "img")
        {
            img = index.data(UserRole++).toString();
        }
        else if (argName == "align")
        {
            QString alignStr = index.data(UserRole++).toString();
            if (alignStr == "left")
            {
                align = Qt::AlignLeft;
            }
            else if (alignStr == "center")
            {
                align = Qt::AlignCenter;
            }
        }
        else if (argName == "font")
        {
            QFont font = option.font;
            font.setPixelSize(index.data(UserRole++).toInt());
            painter->setFont(font);
        }
    }


    painter->drawText(option.rect, align, title);
    if (img != nullptr && img != "")
        painter->drawPixmap(option.rect.x() + 5, option.rect.y() + 5, 50, 50, QPixmap(img));
}
