#include "mydatabase.h"
#include "myappinfo.h"


#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>


// 定义数据库单实例
MyDatabase *MyDatabase::m_MyDatabase = nullptr; // 静态成员变量的定义

MyDatabase::MyDatabase(QObject *parent) : QObject(parent)
{
    /* 读取数据库信息 */
    // 根据MyAppInfo获取数据库信息
    MyAppInfo *appInfo = MyAppInfo::getInstance();
    m_DriverType = appInfo->m_DatabaseDriverType;
    m_DatabaseName = appInfo->MyAppInfo::m_DatabaseName;

    /* 初始化数据 */
    // 打开数据库
    m_IsOpen = openDatabase();
    if (m_IsOpen == false)
    {
        qDebug() << "数据库打开失败！";
    }
    else
    {
        qDebug() << "数据库打开成功！";
        createUserAccountTable();
        createUserInfoTable();
    }

    /* 查询管理员账号 */
    UserAccount admin = selectUserAccountByAccountAndPassword(MyAppInfo::m_AdminAccount,MyAppInfo::m_AdminPassword);
    if (admin.id == -1)
    {   // 管理员账号不存在，添加账号
        insertUserAccount(MyAppInfo::m_AdminAccount,MyAppInfo::m_AdminPassword);
    }
}


bool MyDatabase::openDatabase()
{
    m_Database = QSqlDatabase::addDatabase("QSQLITE");
    m_Database.setDatabaseName("network_chat.db");
    return m_Database.open();
}

void MyDatabase::createUserAccountTable()
{
    QSqlQuery query;

    // 创建用户表
    QString createUserAccount = "CREATE TABLE IF NOT EXISTS user_account("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "account TEXT NOT NULL,"
                                "password TEXT NOT NULL)";
    if (query.exec(createUserAccount))
    {
        qDebug() << "用户账号表创建成功！";
    }
    else
    {
        qDebug() << "用户账号表创建失败！";
    }
}

void MyDatabase::createUserInfoTable()
{
    QSqlQuery query;

    // 创建用户信息表
    QString createUserInfo = "CREATE TABLE IF NOT EXISTS user_info("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "uacId INTEGER NOT NULL,"
                             "username TEXT,"
                             "headImg TEXT,"
                             "signature TEXT,"
                             "sex TEXT,"
                             "isOnline BOOLEAN)";
    if (query.exec(createUserInfo))
    {
        qDebug() << "用户信息表创建成功！";
    }
    else
    {
        qDebug() << "用户信息表创建失败！";
    }
}

QString MyDatabase::encryptInputPsw(QString inputPsw)
{
    QByteArray hash = QCryptographicHash::hash(inputPsw.toUtf8(), QCryptographicHash::Sha256);
    return hash;
}

void MyDatabase::insertUserAccount(QString account, QString password)
{
    QSqlQuery query;
    QString insertUserAccount = "INSERT INTO user_account (account, password)"
                                " VALUES(:account, :password)";
    query.prepare(insertUserAccount);
    query.bindValue(":account", account);
    query.bindValue(":password", encryptInputPsw(password));
    if (!query.exec()) {
        qDebug() << "Error(insertUserAccount): 用户账号插入失败." << query.lastError();
    } else {
        qDebug() << "用户账号插入成功!";
    }
}

void MyDatabase::insertUserInfo(UserInfo userInfo)
{
    QSqlQuery query;
    QString insert = "INSERT INTO user_info ("
                     "uacId, headImg, username,"
                     "signature, sex, isOnline)"
                     " VALUES("
                     ":uacId, :headImg, :username,"
                     ":signature, :sex, :isOnline)";
    query.prepare(insert);
    query.bindValue(":uacId", userInfo.uacId);
    query.bindValue(":headImg", userInfo.headImg);
    query.bindValue(":username", userInfo.username);
    query.bindValue(":signature", userInfo.signature);
    query.bindValue(":sex", userInfo.sex);
    query.bindValue(":isOnline", userInfo.isOnline);

    if (!query.exec()) {
        qDebug() << "Error(insertUserInfo): 用户信息插入失败." << query.lastError();
    } else {
        qDebug() << "用户信息插入成功!";
    }
}

UserAccount MyDatabase::selecUserAccounttById(int id)
{
    QSqlQuery query;
    QString select = "SELECT * FROM user_account WHERE id = :id";
    query.prepare(select);
    query.bindValue(":id", id);
    if (query.exec()) {
        while (query.next()) {
            int _id = query.value("id").toInt();
            QString _account = query.value("account").toString().toUtf8();
            QString _password = query.value("password").toString().toUtf8();
            qDebug() << "ID:" << _id << "account:" << _account << "password:" << _password;
            return UserAccount(_id, _account, _password);
        }
    }
    qDebug() << "Error（selectByAccountAndPassword）: 用户查询失败." << query.lastError();
    // 调用无参构造，id默认为-1，即表示查询失败
    return UserAccount();
}

UserAccount MyDatabase::selectUserAccountByAccountAndPassword(QString account, QString password)
{
    QSqlQuery query;
    QString select = "SELECT * FROM user_account WHERE account = :account AND password = :password";
    query.prepare(select);
    query.bindValue(":account", account);
    query.bindValue(":password", encryptInputPsw(password));
    if (query.exec()) {
        while (query.next()) {
            int _id = query.value("id").toInt();
            QString _account = query.value("account").toString().toUtf8();
            QString _password = query.value("password").toString().toUtf8();
            qDebug() << "ID:" << _id << "account:" << _account << "password:" << _password;
            return UserAccount(_id, _account, _password);
        }
    }
    qDebug() << "Error（selectByAccountAndPassword）: 用户查询失败." << query.lastError();
    // 调用无参构造，id默认为-1，即表示查询失败
    return UserAccount();
}

UserInfo MyDatabase::selectUserInfoByUacId(int uacId)
{
    QSqlQuery query;
    QString select = "SELECT * FROM user_info WHERE uacId = :uacId";
    query.prepare(select);
    query.bindValue(":uacId", uacId);
    if (query.exec()) {
        while (query.next()) {
            int _id = query.value("id").toInt();
            int _uacId = query.value("uacId").toInt();
            bool _isOnline = query.value("isOnline").toBool();
            QString _username = query.value("username").toString().toUtf8();
            QString _headImg = query.value("headImg").toString().toUtf8();
            QString _signature = query.value("signature").toString().toUtf8();
            QString _sex = query.value("sex").toString().toUtf8();
            return UserInfo(_id, _uacId, _username, _isOnline, _headImg, _signature, _sex);
        }
    }
    qDebug() << "Error（selectByAccountAndPassword）: 用户查询失败." << query.lastError();
    // 调用无参构造，id默认为-1，即表示查询失败
    return UserInfo();
}

