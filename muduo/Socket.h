#pragma once
#include "noncopyable.h"
#include "InetAddress.h"

class Socket : noncopyable
{
public:
    explicit Socket(int sockfd) : sockfd_(sockfd){}
    ~Socket() { ::close(sockfd_);}
    int fd() const { return sockfd_; }
                 
    void bind(const InetAddress& addr)
    {
        ::bind(sockfd_, addr.getSocketAddr(), sizeof(addr));
    }
    void listen()
    {
        ::listen(sockfd_, SOMAXCONN);
    }

    typedef struct
    {
        int socket;
        InetAddress peerAddr;
    }Accept_Result;

    Accept_Result accept()
    {
        sockaddr_in addr;
        socklen_t addrlen = sizeof(addr);
        int connfd = ::accept4(sockfd_, (sockaddr*)&addr, &addrlen,
                               SOCK_NONBLOCK | SOCK_CLOEXEC);
        if(connfd < 0)
        {
            perror("accept");
            return(-1,InetAddress());
        }
        return {connfd, InetAddress(addr)};
    }

private:
    const int sockfd_;
};







