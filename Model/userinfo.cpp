#include "userinfo.h"

#include <QJsonObject>

UserInfo::UserInfo()
{
    id = -1;
    uacId = -1;
    isOnline = false;
    headImg = signature = sex = nullptr;
}

UserInfo::UserInfo(int _uacId, QString _username, bool _isOnline, QString _headImg, QString _signature, QString _sex)
{
    id = -1;
    uacId = _uacId;
    username = _username;
    isOnline = _isOnline;
    headImg = _headImg;
    signature = _signature;
    sex = _sex;
}

UserInfo::UserInfo(int _id, int _uacId, QString _username, bool _isOnline,
                   QString _headImg, QString _signature, QString _sex)
{
    id = _id;
    uacId = _uacId;
    username = _username;
    isOnline = _isOnline;
    headImg = _headImg;
    signature = _signature;
    sex = _sex;
}

QJsonObject UserInfo::toJsonObj()
{
    QJsonObject data;
    data["id"] = id;
    data["uacId"] = uacId;
    data["username"] = username;
    data["isOnline"] = isOnline;
    data["headImg"] = headImg;
    data["signature"] = signature;
    data["sex"] = sex;
    // 密码不可见，不进行传递
    return data;
}
