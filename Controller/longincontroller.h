#ifndef LONGINCONTROLLER_H
#define LONGINCONTROLLER_H

#include <QObject>
#include <mydatabase.h>
#include <mymsgserver.h>

#include "basecontroller.h"
#include "myappcondition.h"
#include "myappinfo.h"

class LonginController : public BaseController
{
    Q_OBJECT
public:
    explicit LonginController(QObject *parent = nullptr);

signals:

    /* 登录界面 */
    // 登录账号
    void adminLoginSucceed();
    void adminLoginFail(QString errorStr);

    // 返回登录方式
    void returnLoginWay(int autoLogin, int remmenberLogin);


public slots:
    /* 登录界面 */
    void on_adminLogin_handel(QString account, QString password);

    /*登录方式*/
    // 获取登录方式
    void on_loginWay_handel();
    // 设置登录方式
    void on_setAutoLoginWay_handel(int autoLogin);
    void on_setRememberLoginWay_handel(int rememberLogin);

private:

};

#endif // LONGINCONTROLLER_H
