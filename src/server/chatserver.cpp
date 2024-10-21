#include "chatserver.hpp"
#include<functional>
#include<cstring>
#include "nlohmann/json.hpp"
#include "chatservice.hpp"
#include<iostream>
using namespace std;
using namespace std::placeholders;
using json=nlohmann::json;
ChatServer::ChatServer(EventLoop* loop,
            const InetAddress& listenAddr,
            const string& nameArg)
    : _server(loop,listenAddr,nameArg),_loop(loop)  
{
        //注册链接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection,this,_1));
        //注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2,_3));
        //设置线程数
    _server.setThreadNum(1);
}
    //启动服务
void ChatServer::start()
    {
        _server.start();
    }
    //上报链接相关信息的回调函数

void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
  

    if (!conn->connected()) {
        
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }

}
    //上报读写事件相关信息的回调函数
void ChatServer::onMessage(const TcpConnectionPtr &conn,Buffer *buffer,Timestamp time)
{

    string buf=buffer->retrieveAllAsString();
    cout<<buf;
    json js=json::parse(buf);
    auto msgHandler=ChatService::instance()->getHandler(js["msgid"].get<int>());
    msgHandler(conn,&js,time);
}

