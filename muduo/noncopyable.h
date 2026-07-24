#pragma once
class noncopyable
{
protected:   //只有自己和自己的子类可以访问
    noncopyable() = default;
    ~noncopyable() = default;
    noncopyable( const noncopyable& ) = delete;
    const noncopyable& operator=( const noncopyable& ) = delete;
};