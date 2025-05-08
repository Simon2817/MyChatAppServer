#include "myclient.h"


MyClient::MyClient(UserAccount account, UserInfo userInfo, QTcpSocket *socket)
    : m_account(account), m_userInfo(userInfo), m_socket(socket)
{

}

QList<int> *MyClient::getFriends()
{
    if (m_friendIdList != nullptr)
        return m_friendIdList;
    QList<int> *list;

    list = m_friendIdList;
    return list;
}

QJsonObject MyClient::toJsonObj()
{
    QJsonObject data;
    data["UserAccount"] = m_account.toJsonObj();
    data["UserInfo"] = m_userInfo.toJsonObj();
    return data;
}
