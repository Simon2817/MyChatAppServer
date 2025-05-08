#ifndef USERINFO_H
#define USERINFO_H

#include <QJsonObject>
#include <QString>



class UserInfo
{
public:
    UserInfo();
    UserInfo(int _uacId, QString username , bool _isOnline, QString _headImg, QString _signature, QString _sex);
    UserInfo(int _id, int _uacId, QString username, bool _isOnline, QString _headImg, QString _signature, QString _sex);

    QString toString()
    {
        return "id: " + QString::number(id)
                + "uacId: " + QString::number(uacId) + "\n"
                + "isOnline: " + QString::number(isOnline) + "\n"
                + "headImg: " + headImg + "\n"
                + "signature: " + signature  + "\n"
                + "sex: " + sex;
    }
    
    QJsonObject toJsonObj();

public:
    int id;
    int uacId;
    QString username;
    bool isOnline;
    QString headImg;
    QString signature;
    QString sex;
};

#endif // USERINFO_H
