#ifndef MYCOMMUNICATIONPROTOCOL_H
#define MYCOMMUNICATIONPROTOCOL_H

#include <QJsonObject>
#include <QObject>
#include <useraccount.h>

#include "myappcondition.h"

class MyCommunicationProtocol : public QObject
{
    Q_OBJECT
public:
    explicit MyCommunicationProtocol(QObject *parent = nullptr);

    // 解析json数据
    void parseJsonByteArray(QByteArray buffer);

    UserAccount parseLogin(QJsonObject jsonObj);

    UserAccount parseRegister(QJsonObject jsonObj);

    QJsonObject encapsulateLoginToJson(QString account, QString password);

    QByteArray encapsulateProtocolToJson(int fromId, int toId, int type, QJsonObject data);

signals:


public:

};

#endif // MYCOMMUNICATIONPROTOCOL_H
