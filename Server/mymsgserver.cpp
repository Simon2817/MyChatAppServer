#include "mycommunicationprotocol.h"
#include "mymsgserver.h"

#include <QDebug>
#include <QFuture>
#include <QTcpSocket>
#include <QtConcurrent/QtConcurrent>

MyMsgServer *MyMsgServer::m_MyMsgServer = nullptr;

MyMsgServer::MyMsgServer(QString ip, int port, QObject *parent)
    : QTcpServer(parent)
{
    m_Server = new QTcpServer(this);
    if (!m_Server->listen(QHostAddress("ip"), port))
    {
        qDebug() << "消息服务器连接失败！" << m_Server->errorString();
    }
    qDebug() << "【" << ip << ":" << port << "】消息服务器连接成功！";

    connect(m_Server, &QTcpServer::newConnection, this, &MyMsgServer::on_newConnection_handel);
}

void MyMsgServer::msgServerSendMsg(int fromId, int toId, int type, QJsonObject data)
{
    // 异步发送数据
    QFuture<void> future = QtConcurrent::run([this, fromId, toId, type, data](){
        // 封装协议
        MyCommunicationProtocol protocol;
        QByteArray buffer = protocol.encapsulateProtocolToJson(fromId, toId, type, data);
        // 根据用户id发送数据
        QTcpSocket *clientSocket;
        {
            QMutex mutex;
            QMutexLocker locker(&mutex);
            clientSocket = m_ClientList[toId]->m_socket;
        }
        clientSocket->write(buffer);
    });
}

void MyMsgServer::on_newConnection_handel()
{
    if (!m_Server->hasPendingConnections())
        return;
    QTcpSocket *clientSocket = m_Server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &MyMsgServer::on_socketReadyRead_handel);
}

void MyMsgServer::on_socketReadyRead_handel()
{
    // 异步处理socekt数据接收
    QFuture<void> future = QtConcurrent::run([this](){
        // 接收用户请求
        QTcpSocket * client = qobject_cast<QTcpSocket*>(sender());
        // 读取到的信息
        QByteArray buffer = client->readAll();

        // 解析json数据
        MyCommunicationProtocol protocol;

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(buffer, &error);
        if (error.error != QJsonParseError::NoError) {
            qDebug() << "JSON解析错误:" << error.errorString();
            return;
        }

        QJsonObject jsonObj = doc.object();

        // 获取请求类型
        int type = jsonObj["type"].toInt();
        switch (type)
        {
            case RequesetType::Login:
            {
                UserAccount account = protocol.parseLogin(jsonObj);
                emit m_login(account);
            }
                break;
            case RequesetType::Register:
            {
                UserAccount account = protocol.parseRegister(jsonObj);
                emit m_register(account);
            }
            break;
        }

    });
}

void MyMsgServer::on_controllerLoginResult(MyClient *client)
{
    // 如果id = -1，客户端接收后，表明请求服务失败
    this->msgServerSendMsg(-1, client->m_account.id, RequesetType::Login, client->toJsonObj());
}

void MyMsgServer::on_controllerRegisterResult(MyClient *client)
{
    // 如果id = -1，客户端接收后，表明请求服务失败
    this->msgServerSendMsg(-1, client->m_account.id, RequesetType::Register, client->toJsonObj());

    if (client->m_account.id != -1)
    {
        // 将该客户端加入到队列中
        QMutex mutex;
        QMutexLocker locker(&mutex);
        m_ClientList.push_back(client);
    }
}

