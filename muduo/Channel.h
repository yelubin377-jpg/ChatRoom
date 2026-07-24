#pragma once
#include <functional> //std::function<void()>
#include <memory>  //std::weak_ptr  Tcpconnection把自己绑到channel身上，
//若指针 ：：  我可能指向你，但是不阻止你死
#include <sys/epoll.h>
#include "noncopyable.h"
class EventLoop;
class Channel : noncopyable
{
public:
    typedef std::function<void()> EventCallback;
    Channel(EventLoop* loop,int fd)
            :_loop{loop},
             _fd(fd),
             _events(0),
             _reallyevents(0),
             _index(-1)
    {
        
    }
    ~Channel(){};
private:
    EventLoop* _loop;
    const int _fd; //const 只读，防止出问题
    int _events; //EPOLL_IN,EPOLL_OUT,EPOLL_WAIT
    int _reallyevents;//实际发生的事情
    int _index;//在Poller数组里的实际下标
};