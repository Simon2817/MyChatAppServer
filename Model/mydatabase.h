#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QMutex>
#include <QObject>
#include <QSqlDatabase>
#include <QSettings>


#include "useraccount.h"
#include "userinfo.h"


class MyDatabase : public QObject
{
    Q_OBJECT
public:
    explicit MyDatabase(QObject *parent = nullptr);

    // 单实例接口
    static MyDatabase *getInstance()
    {
        static QMutex mutex;
        if (MyDatabase::m_MyDatabase == NULL)
        {
            QMutexLocker locker(&mutex);
            MyDatabase::m_MyDatabase = new MyDatabase();
        }
        return MyDatabase::m_MyDatabase;
    }


    // 打开数据
    bool openDatabase();

    /* 创建表 */
    // 用户账号表
    void createUserAccountTable();
    // 用户信息表
    void createUserInfoTable();

    /* 增加数据 */
    // 密码加密
    QString encryptInputPsw(QString inputPsw);

    // 添加用户账号(user_account)
    void insertUserAccount(QString account, QString password);

    // 添加用户信息(user_info)
    void insertUserInfo(UserInfo userInfo);

    /* 查询数据 */
    // 根据id查询账号(user_account)
    UserAccount selecUserAccounttById(int id);
    // 根据用户账号和密码查询用户(user_account)
    UserAccount selectUserAccountByAccountAndPassword(QString account, QString password);

    // 更具uacId用户账号id查询用户信息(user_info)
    UserInfo selectUserInfoByUacId(int uacId);

    /* 修改数据 */
//    bool updateUserAccount()

    /* 删除数据 */





signals:

public:
    // 实例对象
    static MyDatabase *m_MyDatabase;

public:

    // 数据库对象
    QSqlDatabase m_Database;
    // 数据库驱动类型
    QString m_DriverType;
    // 数据库名称
    QString m_DatabaseName;
    // 打开数据库
    bool m_IsOpen;

};

#endif // MYDATABASE_H
