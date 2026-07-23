cmake_minimum_required(VERSION 3.10)   #cmake 最低版本
project(ChatRoom)                        #项目名
set(CMAKE_CXX_STANDARD 17)              #用 C++17

set(MUDUO_ROOT "/home/michael-377/build/release-install-cpp11" CACHE PATH "muduo 安装路径")

include_directories(${MUDUO_ROOT}/include)
include_directories(/usr/include/jsoncpp)
link_directories(${MUDUO_ROOT}/lib)

add_executable(chat_server              # 生成的可执行文件名
    main.cc                             # server 目录下的
    ChatServer.cc
    Router.cc
    ../protocal/pack.cpp                # 跨目录引协议层
    ../protocal/unpack.cpp
)

target_link_libraries(chat_server       # 给 chat_server 链接
    muduo_net                           # muduo 网络库
    muduo_base                          # muduo 基础库
    jsoncpp                             # JSON 解析
    pthread                             # 多线程
)