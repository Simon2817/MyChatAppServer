#ifndef MYAPPCONDITION_H
#define MYAPPCONDITION_H

// 用户登录方式
typedef enum {
    AutoLogin = 0,          // 自动登录
    NotAutoLogin,
    RememberLogin,      // 记住密码
    NotRememberLogin = 3
} LoginWay;

// 用户请求服务器提供服务的类型
typedef enum {
    Login = 4,
    Logout,
    Register,
    SendMsg,
    SendFile,
    UpdateInfo = 10
} RequesetType;

// 用户请求反馈信息
typedef enum {
    LoginSuccess = 11,
    LoginFial,
    RegisterSuccess,
    RegisterFial = 14
} FeedbackValue;

#endif // MYAPPCONDITION_H
