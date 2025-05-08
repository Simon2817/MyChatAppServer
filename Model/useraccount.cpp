#include "useraccount.h"


#include <QCryptographicHash>
#include <QJsonObject>
#include <QRandomGenerator>


/**
 * @brief   :
 * 账号由 5位随机数和用户id组成
 * @author  :Simon
 * @date    :2025.03.25
 */
void UserAccount::generateAccount()
{
    // 生成5位随机数
    QString result;
    for (int i = 0; i < 5; ++i) {
        int randomNumber = QRandomGenerator::global()->bounded(10); // 生成 0-9 的随机数
        result.append(QString::number(randomNumber));
    }
    account = id + result;
}

bool UserAccount::verityPsw(QString _password)
{
    return _password == password ? true : false;
}

QJsonObject UserAccount::toJsonObj()
{
    QJsonObject data;
    data["id"] = id;
    data["account"] = account;
    // 密码不可见，不进行传递
    return data;
}
