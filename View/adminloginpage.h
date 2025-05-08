#ifndef ADMINLOGINPAGE_H
#define ADMINLOGINPAGE_H

#include "longincontroller.h"
#include "myappcondition.h"

#include <QMutex>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class AdminLoginPage; }
QT_END_NAMESPACE

class AdminLoginPage : public QWidget
{
    Q_OBJECT

private:
    explicit AdminLoginPage(QWidget *parent = nullptr);
    ~AdminLoginPage();

signals:
    // 获取登录方式（自动登录、记住密码）
    void loginWay();
    // 设置登录方式
    void setAutoLoginWay(int autoLogin);
    void setRememberLoginWay(int rememberLogin);

    // 登录账号
    void adminLogin(QString account, QString password);

    // 自动登录
    void adminAutoLogin(int arg);

public slots:
    // 初始化界面
    void initPage();

    /* 单选框（自动登录、记住密码） */
    // 接收登录方式
    void getLoginWay(int autoLogin, int remmenberLoin);
    // 自动登录
    void on_checkBoxAutoLogin_stateChanged(int arg);
    // 记住密码
    void on_checkBoxRemember_stateChanged(int arg);


    /* 登录按钮 */
    void on_pushButtonLogin_clicked();
    // 登录成功
    void on_adminLoginSucceed_handel();
    // 登录失败
    void on_adminLoginFail_handel(QString errorStr);

    /* 输入框 */
    void on_lineEditAccount_textChanged(const QString &arg1);
    void on_lineEditPassword_textChanged(const QString &arg1);

public:
    static AdminLoginPage *m_AdminLoginPage;

    static AdminLoginPage *getInstance()
    {
        QMutex mutex;
        if (AdminLoginPage::m_AdminLoginPage == nullptr)
        {
            QMutexLocker locker(&mutex);
            return new AdminLoginPage();
        }
        return AdminLoginPage::m_AdminLoginPage;
    }



private:
    Ui::AdminLoginPage *ui;
    LonginController *m_controller;
};
#endif // ADMINLOGINPAGE_H
