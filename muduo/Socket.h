#pragma once
#include "noncopyable.h"

class Socket : noncopyable
{
public:
    explicit Socket(int sockfd) : sockfd_(sockfd){}
    ~Socket() { ::close(sockfd_);}
    int fd() const { return sockfd_; }
private:
    const int sockfd_;
};

void bind(const InetAddress& addr)
{
    ::bind(sockfd_,addr.getSocketAddr(),sizeof(addr));
}
void listen()
{
    ::listen(sockf_,SOMAXCONN);
}

typedef struct AcceptResult
{
    int socket;
    InetAddress& peerAddr;
}result(Accept);

Socket::result(Accept) accept()
{
    sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    int connfd = ::accept4(sockfd_,(sockaddr*)&addr,&addrlen,
                           SOCK_NONBLOCK | SOCK_CLOEXEC);
    if(connfd < 0)
    {
        perror("accept");
    }
    return {connfd,InetAddress(addr)};
}








