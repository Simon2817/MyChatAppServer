#include "longincontroller.h"

#include <QDebug>

LonginController::LonginController(QObject *parent) : BaseController(parent)
{

}

void LonginController::on_adminLogin_handel(QString account, QString password)
{
    UserAccount admin = myDatabase->selectUserAccountByAccountAndPassword(account, password);
    if (admin.id == -1)
    {
        emit adminLoginFail("账号或密码错误！");
    }
    else
    {
        emit adminLoginSucceed();
    }
}

void LonginController::on_loginWay_handel()
{
    emit returnLoginWay(myAppInfo->m_AutoLoginWay, myAppInfo->m_RememberLoginWay);
}

void LonginController::on_setAutoLoginWay_handel(int autoLogin)
{
    myAppInfo->fixAutoLoginWay(autoLogin);
}

void LonginController::on_setRememberLoginWay_handel(int rememberLogin)
{
    myAppInfo->fixRememberLoginWay(rememberLogin);
}
