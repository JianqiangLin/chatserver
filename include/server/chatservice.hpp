#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include<unordered_map>
#include<functional>
#include<muduo/net/TcpConnection.h>
#include "nlohmann/json.hpp"
#include<mutex>
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
using json=nlohmann::json;
using namespace std;
using namespace muduo;
using namespace muduo::net;
#include "usermodel.hpp"
#include "redis.hpp"
//表示处理消息的事件回调方法类型
using MsgHandler=std::function<void(const TcpConnectionPtr &conn,json*js ,Timestamp)>;
//聊天服务器业务类
class ChatService{
    public:
    //获取单例对象的接口函数
    static ChatService*instance();
    //处理登录业务
    void login(const TcpConnectionPtr &conn,json*js,Timestamp time);
    //处理注册业务
    void reg(const TcpConnectionPtr &conn,json*js,Timestamp time);
    //一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn,json*js,Timestamp time);
    //添加好友业务操作
    void addFriend(const TcpConnectionPtr &conn,json*js,Timestamp time);
    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    void clientCloseException(const TcpConnectionPtr &conn);
    //服务器异常，业务重置方法
    //创建群组
    void createGroup(const TcpConnectionPtr &conn,json*js,Timestamp time);
    //加入群组
    void addGroup(const TcpConnectionPtr &conn,json*js,Timestamp time);
    //群组聊天业务
    void groupChat(const TcpConnectionPtr &conn,json*js,Timestamp time);
    //处理注销业务
    void loginout(const TcpConnectionPtr &conn,json*js,Timestamp time);
    void redis_subscribe_message_handler(int channel, string message);

    void reset();
    private:
    ChatService();
    //存储消息id和其对应的业务处理方法
    unordered_map<int,MsgHandler> _msgHandlerMap;

    //数据操作类对象
    UserModel _userModel;

    //存储在线用户的通信连接
    unordered_map<int,TcpConnectionPtr> _userConnMap;
    
    //定义互斥锁，保证_userConnMap的线程安全

    mutex _connMutex;
    OfflineMsgModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;
    Redis _redis;

};


#endif