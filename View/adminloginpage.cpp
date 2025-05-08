#include "adminloginpage.h"
#include "mainwindow.h"
#include "ui_adminloginpage.h"

#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

AdminLoginPage *AdminLoginPage::m_AdminLoginPage = nullptr;

AdminLoginPage::AdminLoginPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminLoginPage)
{
    ui->setupUi(this);
    m_controller = new LonginController(this);

    /* 信号与槽 */
    // 登录账号
    connect(this, &AdminLoginPage::adminLogin, m_controller, &LonginController::on_adminLogin_handel);
    connect(m_controller, &LonginController::adminLoginSucceed, this, &AdminLoginPage::on_adminLoginSucceed_handel);
    connect(m_controller, &LonginController::adminLoginFail, this, &AdminLoginPage::on_adminLoginFail_handel);

    // 初始化界面
    initPage();
}

void AdminLoginPage::initPage()
{
    /* 设置ui界面 */
    // 设置账号lineEdit输入框
    QString accountStr = MyAppInfo::m_AdminAccount;
    if (accountStr != "" && accountStr != nullptr)
        ui->lineEditAccount->setText(accountStr);


    /* 信号与槽 */
    // checkBox按钮
    // 获取登录方式
    connect(this, &AdminLoginPage::loginWay, m_controller, &LonginController::on_loginWay_handel);
    connect(m_controller, &LonginController::returnLoginWay, this, &AdminLoginPage::getLoginWay);

    // 设置登录方式
    connect(this, &AdminLoginPage::setAutoLoginWay, m_controller, &LonginController::on_setAutoLoginWay_handel);
    connect(this, &AdminLoginPage::setRememberLoginWay, m_controller, &LonginController::on_setRememberLoginWay_handel);

    // 在界面启动前，发送请求登录方式信号
    emit loginWay();
}

AdminLoginPage::~AdminLoginPage()
{
    delete ui;
}

// 获取登录方式
// 通过way来得知登录方式
void AdminLoginPage::getLoginWay(int autoLogin, int remmenberLoin)
{
    if (autoLogin == LoginWay::AutoLogin)
    {
        ui->checkBoxAutoLogin->setCheckState(Qt::Checked);
        // 触发登录按钮
        if (remmenberLoin == LoginWay::RememberLogin)
        {   // 当用户选择了记住密码，才能催发登录按钮
            emit adminLogin(MyAppInfo::m_AdminAccount, MyAppInfo::m_AdminPassword);
        }
    }
    else
    {
        ui->checkBoxAutoLogin->setCheckState(Qt::Unchecked);
        this->show();
    }
    if (remmenberLoin == LoginWay::RememberLogin)
    {
        ui->checkBoxRemember->setCheckState(Qt::Checked);
        // 显示用户密码到输入框
        ui->lineEditPassword->setText(MyAppInfo::m_AdminPassword);
    }
    else
        ui->checkBoxRemember->setCheckState(Qt::Unchecked);;
}

// 账号登录按钮
void AdminLoginPage::on_pushButtonLogin_clicked()
{
    // 获取账号密码
    QString account = ui->lineEditAccount->text();
    QString password = ui->lineEditPassword->text();

    // 发出登录信号
    emit adminLogin(account, password);
}

// 登录成功
void AdminLoginPage::on_adminLoginSucceed_handel()
{
    // 进入服务器主界面
    QMessageBox::information(this, tr("My Chat Application"),
                            tr("登录成功！"),
                            QMessageBox::Ok);
    // 关闭登录界面
    this->close();
    // 打开主界面
    MainWindow::getInstance()->show();
}

// 登录失败
void AdminLoginPage::on_adminLoginFail_handel(QString errorStr)
{
    QMessageBox::warning(this, tr("My Chat Application"),
                         tr("登录失败.\n")
                         + tr( errorStr.toStdString().c_str()),
                         QMessageBox::Ok);
    this->show();
}

void AdminLoginPage::on_checkBoxAutoLogin_stateChanged(int arg)
{
    qDebug() << "自动登录状态：" << arg;
    if (arg == Qt::Checked)
    {
        emit setAutoLoginWay(LoginWay::AutoLogin);
    }
    else
    {
       emit setAutoLoginWay(LoginWay::NotAutoLogin);
    }
}

void AdminLoginPage::on_checkBoxRemember_stateChanged(int arg)
{
    qDebug() << "记住密码状态：" << arg;
    if (arg == Qt::Checked)
    {
        emit setRememberLoginWay(LoginWay::RememberLogin);
    }
    else
    {
       emit setRememberLoginWay(LoginWay::NotRememberLogin);
    }
}

void AdminLoginPage::on_lineEditAccount_textChanged(const QString &arg1)
{
    QRegularExpression regE("^[0-9]+$");
    QRegularExpressionValidator *regEV = new QRegularExpressionValidator(regE, this);
    ui->lineEditAccount->setValidator(regEV);
}

void AdminLoginPage::on_lineEditPassword_textChanged(const QString &arg1)
{
}
