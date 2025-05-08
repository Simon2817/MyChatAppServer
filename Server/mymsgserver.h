#ifndef MSGSERVER_H
#define MSGSERVER_H

#include "myclient.h"

#include <QMutex>
#include <QObject>
#include <QTcpServer>
#include <myappinfo.h>

class MyMsgServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyMsgServer(QString ip, int port, QObject *parent = nullptr);

    void msgServerSendMsg(int fromId, int toId, int type, QJsonObject data);

    static MyMsgServer *m_MyMsgServer;
    static MyMsgServer *getIntance()
    {
        QMutex mutex;
        if (MyMsgServer::m_MyMsgServer == nullptr)
        {
            QMutexLocker locker(&mutex);
            return new MyMsgServer(MyAppInfo::m_MyAppServerIP, MyAppInfo::m_MsgServerPort);
        }
        return MyMsgServer::m_MyMsgServer;
    }

signals:
    // 登录账号
    void m_login(UserAccount account);
    // 注册
    void m_register(UserAccount account);

private slots:
    void on_newConnection_handel();
    void on_socketReadyRead_handel();
    // 控制层返回登录结果
    void on_controllerLoginResult(MyClient *client);
    void on_controllerRegisterResult(MyClient *client);

private:
    QTcpServer *m_Server;
    QList<MyClient *> m_ClientList;
};

#endif // MSGSERVER_H
