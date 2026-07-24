#pragma once
class noncopyable
{
protected:           //只有自己和自己的子类可以访问， 不能创建如：class EventLoop  :  noncopyable 
    noncopyable() = default;
    ~noncopyable() = default;
    
    noncopyable(const noncopyable&) = delete;//不存在noncopyable(const noncopyable&)
    //上面是拷贝构造，下面是拷贝赋值 
    void noncopyable& operator = (noncopyable&) = delete;
}

