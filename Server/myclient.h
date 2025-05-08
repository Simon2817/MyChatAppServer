#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QTcpSocket>
#include <useraccount.h>
#include <userinfo.h>



class MyClient
{
public:
    MyClient(UserAccount account, UserInfo userInfo, QTcpSocket *socket = nullptr);

    // 获取朋友的id号
    QList<int> *getFriends();

    QJsonObject toJsonObj();

signals:


public:
    UserAccount m_account;
    UserInfo m_userInfo;
    QTcpSocket *m_socket;
    QList<int> *m_friendIdList;
};

#endif // MYCLIENT_H
