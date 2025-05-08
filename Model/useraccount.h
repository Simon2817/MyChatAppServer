#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <QJsonObject>
#include <QString>



class UserAccount
{
public:
    UserAccount(){id = -1; account = nullptr; password = nullptr;}
    UserAccount(QString _account, QString _paaswrd)
    {
        id = -1;
        account = _account;
        password = _paaswrd;
    }
    UserAccount(int _id, QString _account, QString _paaswrd)
    {
        id = _id;
        account = _account;
        password = _paaswrd;
    }

    // 生成账号
    void generateAccount();

    // 验证密码
    bool verityPsw(QString _password);

    QJsonObject toJsonObj();
    
    QString toString()
    {
        return "id: " + QString::number(id)
                + "account: " + account
                + "password: " + password;
    }

public:
    int id;
    QString account;
    QString password;
};

#endif // USERACCOUNT_H
