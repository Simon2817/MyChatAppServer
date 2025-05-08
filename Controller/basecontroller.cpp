#include "basecontroller.h"

BaseController::BaseController(QObject *parent) : QObject(parent)
{
    myAppInfo = MyAppInfo::getInstance();
    myDatabase = MyDatabase::getInstance();
    myMsgServer = MyMsgServer::getIntance();
}

void BaseController::on_login_handel(UserAccount accout)
{
    int feedBack = FeedbackValue::LoginFial;
    // 通过数据库校验用户账号
    UserAccount account = myDatabase->selectUserAccountByAccountAndPassword(accout.account, accout.password);
    UserInfo userInfo;
    if (accout.id != -1)
    {
        // 账号查询成功，查询相应的用户信息
        userInfo = myDatabase->selectUserInfoByUacId(accout.id);
        feedBack = FeedbackValue::LoginSuccess;
    }
    // 反馈用户登录
    MyClient *client = new MyClient(accout, userInfo);
    feedBackLogin(client, feedBack);
}

void BaseController::on_register_handel(MyClient *client)
{
    int feedBack = FeedbackValue::RegisterFial;

    // 创建临时账号
    UserAccount userAccount;
    userAccount.generateAccount();
    userAccount.password = client->m_account.password;
    myDatabase->insertUserAccount(userAccount.account, userAccount.password);
    // 再次查询新用户的账号
    userAccount = myDatabase->selectUserAccountByAccountAndPassword(userAccount.account, userAccount.password);
    if (userAccount.id != -1)
    {
        // 生成正式的账号
        userAccount.generateAccount();
        // 更新数据库中的账号信息
//        myDatabase->
    }

//    UserInfo userInfo();
//    myDatabase->insertUserInfo();

    // 反馈用户登录
//    MyClient *client = new MyClient(accout, userInfo);
}
