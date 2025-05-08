#include "myappinfo.h"

#include <QSettings>
#include <QDebug>
#include <QFile>

// MyAppInfo单实例
MyAppInfo *MyAppInfo::m_MyAppInfo = nullptr;

// 定义枚举类型
QString MyAppInfo::m_MyAppPath;
QString MyAppInfo::m_MyAppIconPath = ":/resource/appicon/APPIcon.png";
QString MyAppInfo::m_MyAppIniPath =  "./resource/profile/MyChatApp.ini";

// [Server]服务器
QString MyAppInfo::m_MyAppServerIP;                 // 服务器ip地址
int MyAppInfo::m_MsgServerPort;                     // 消息服务器端口
int MyAppInfo::m_FileServerPort;                    // 文件服务器端口

// [Database]数据库信息
QString MyAppInfo::m_DatabasePath;
QString MyAppInfo::m_DatabaseDriverType;
QString MyAppInfo::m_DatabaseName;

// [Admin]用户信息
QString MyAppInfo::m_AdminAccount = "123";
QString MyAppInfo::m_AdminPassword = "123";
int MyAppInfo::m_AutoLoginWay;
int MyAppInfo::m_RememberLoginWay;

MyAppInfo::MyAppInfo()
{
    readIniFile();
}

void MyAppInfo::readIniFile()
{
    QSettings *iniFile = new QSettings(m_MyAppIniPath, QSettings::IniFormat);
    qDebug() << "m_MyAppIniPath: " << m_MyAppIniPath;

    // 读取服务器信息
    m_MyAppServerIP = iniFile->value("/Server/MyAppServerIP").toString().toUtf8();
    m_MsgServerPort = iniFile->value("Server/MsgServerPort").toInt();
    m_FileServerPort = iniFile->value("Server/m_FileServerPort").toInt();
    qDebug() << "m_MyAppServerIP: " << m_MyAppServerIP;
    qDebug() << "m_MsgServerPort: " << m_MsgServerPort;
    qDebug() << "m_FileServerPort: " << m_FileServerPort;

    // 读取数据库信息
    m_DatabaseDriverType = iniFile->value("/Database/DriverType").toString().toUtf8();
    m_DatabaseName = iniFile->value("/Database/DatabaseName").toString().toUtf8();
    qDebug() << "m_DatabaseDriverType: " << m_DatabaseDriverType;
    qDebug() << "m_DatabaseName: " << m_DatabaseName;

    // 读取管理员信息
    m_AdminAccount = iniFile->value("/Admin/Account").toString().toUtf8();
    m_AdminPassword = iniFile->value("Admin/Password").toString().toUtf8();
    m_AutoLoginWay = iniFile->value("Admin/AutoLoginWay").toInt();
    m_RememberLoginWay = iniFile->value("Admin/RememberLoginWay").toInt();

    // 释放资源
    iniFile->deleteLater();
}

void MyAppInfo::writeIniFile()
{

}

void MyAppInfo::fixAutoLoginWay(int autoLogin)
{
    QSettings *iniFile = new QSettings(m_MyAppIniPath, QSettings::IniFormat);
    iniFile->setValue("/Admin/AutoLoginWay", autoLogin);
    iniFile->sync(); // 强制同步到磁盘
    // 释放资源
    iniFile->deleteLater();
}

void MyAppInfo::fixRememberLoginWay(int rememberLogin)
{
    QFile file(m_MyAppIniPath);
    QSettings *iniFile = new QSettings(m_MyAppIniPath, QSettings::IniFormat);
    iniFile->setValue("/Admin/RememberLoginWay", rememberLogin);
    iniFile->sync(); // 强制同步到磁盘
    // 释放资源
    iniFile->deleteLater();
}

