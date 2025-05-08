#ifndef MYAPPINFO_H
#define MYAPPINFO_H

#include <QString>
#include <QMutex>
#include <QVariant>
#include <QSettings>

#include "myappcondition.h"

class MyAppInfo
{
private:
    MyAppInfo();
public:
    ~MyAppInfo();
public:
    // 单实例
    static MyAppInfo *m_MyAppInfo;
    static MyAppInfo *getInstance()
    {
        QMutex mutex;
        if (MyAppInfo::m_MyAppInfo == nullptr)
        {
            QMutexLocker locker(&mutex);
            return new MyAppInfo();
        }
        return MyAppInfo::m_MyAppInfo;
    }

    //=======================配置文件=========================/
    // 读取配置文件
    void readIniFile();
    // 写入配置文件
    void writeIniFile();

    // 配置文件
    void fixAutoLoginWay(int autoLogin);
    void fixRememberLoginWay(int rememberLogin);


    //=======================系统初始配置文件部分=========================//
    // 服务器
    static QString m_MyAppServerIP;                 // 服务器ip地址
    static int m_MsgServerPort;                     // 消息服务器端口
    static int m_FileServerPort;                    // 文件服务器端口
    static QString m_MyAppPath;                     // 应用程序路径
    static QString m_MyAppIconPath;                 // 程序图标

    // 数据库
    static QString m_DatabasePath;                  // 数据库目录
    static QString m_MyAppIniPath;                  // 初始配置文件目录
    static QString m_DatabaseDriverType;            // 数据库驱动类型
    static QString m_DatabaseName;                  // 数据库名称

    // 管理员
    static QString m_AdminAccount;                  // 管理员账号
    static QString m_AdminPassword;                 // 管理员密码
    static int m_AutoLoginWay;                      // 自动登录状态
    static int m_RememberLoginWay;                  // 记住用户密码


//    static QString m_BackupPath;      // 配置目录
//    static QString m_RecvPath;        // 文件接收保存目录
//    static QString m_HeadPath;        // 用户头像保存(可存放数据库)
};

#endif // MYAPPINFO_H
