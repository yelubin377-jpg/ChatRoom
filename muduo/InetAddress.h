#pragma once


class InetAddress
{
public:
    explicit InetAddress(uint16_t port,std::string ip = "0.0.0.0");
    explicit InetAddress(const struct sockaddr_in& addr);

private:
    struct sockaddr_in addr_;  
};

