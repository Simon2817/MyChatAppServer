#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <QObject>
#include <myappinfo.h>
#include <mydatabase.h>
#include <mymsgserver.h>
#include <useraccount.h>
#include <userinfo.h>

class BaseController : public QObject
{
    Q_OBJECT
public:
    explicit BaseController(QObject *parent = nullptr);

signals:
    /* 服务器 */
    void feedBackLogin(MyClient *client, int feedBackValue);
    void feedBackRegister(MyClient *client, int feedBackValue);

public slots:
    /* 服务器的请求 */
    void on_login_handel(UserAccount accout);
    void on_register_handel(MyClient*client);


protected:
    /* Model层 */
    // 配置文件
    MyAppInfo *myAppInfo;
    // 数据库
    MyDatabase *myDatabase;
    // 服务器
    MyMsgServer *myMsgServer;
};

#endif // BASECONTROLLER_H
