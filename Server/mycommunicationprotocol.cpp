#include "mycommunicationprotocol.h"

#include <QJsonParseError>
#include <QJsonParseError>
#include <QDebug>
#include <QJsonObject>

MyCommunicationProtocol::MyCommunicationProtocol(QObject *parent) : QObject(parent)
{

}

void MyCommunicationProtocol::parseJsonByteArray(QByteArray buffer)
{

}

UserAccount MyCommunicationProtocol::parseLogin(QJsonObject jsonObj)
{
    // 登录请求的信息
    QJsonObject data = jsonObj["data"].toObject();
    // 获取账号和密码
    QString account = data["account"].toString().toUtf8();
    QString password = data["password"].toString().toUtf8();
    // 发出登录请求信号
    return UserAccount(account, password);
}

UserAccount MyCommunicationProtocol::parseRegister(QJsonObject jsonObj)
{
    // 注册请求的信息
    QJsonObject data = jsonObj["data"].toObject();
    // 获取账号和密码
    QString account = data["account"].toString().toUtf8();
    QString password = data["password"].toString().toUtf8();
    // 发出注册请求信号
    return UserAccount(account, password);
}

QJsonObject MyCommunicationProtocol::encapsulateLoginToJson(QString account, QString password)
{
    QJsonObject data;
    data["account"] = account;
    data["password"] = password;
    return data;
}

QByteArray MyCommunicationProtocol::encapsulateProtocolToJson(int fromId, int toId, int type, QJsonObject data)
{
    QJsonObject jsonObj;
    jsonObj["fromId"] = fromId;
    jsonObj["toId"] = toId;
    jsonObj["type"] = type;
    jsonObj["data"] = data;
    QJsonDocument doc(jsonObj);
    // 紧凑模式，不带缩进
    QByteArray buffer = doc.toJson(QJsonDocument::Compact);
    return buffer;
}
