#include "Client.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <json/json.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>

int main()
{
    LOG_INFO << " pid = " << getpid();
    muduo::net::EventLoop loop;
    muduo::net::InetAddress Addr("127.0.0.1",2026);
    ChatClient client(&loop,Addr);
    client.start();
    std::thread stdinThread([&]()
    {
        std::string line;
        while(std::getline(std::cin , line))
        {
            Json::Value body;
            body["msg"] = line;
            loop.runInLoop([&client , body]()
        {
            client.send(1,body);
        });
        }
        loop.quit();
    });
    stdinThread.detach();
    loop.loop();

        
}