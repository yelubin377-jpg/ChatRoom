cmake_minimum_required(VERSION 3.10)
project(ChatRoomClient)
set(CMAKE_CXX_STANDARD 17)

set(MUDUO_ROOT "/home/michael-377/build/release-install-cpp11" CACHE PATH "muduo 安装路径")
include_directories(${MUDUO_ROOT}/include)
include_directories(/usr/include/jsoncpp)
link_directories(${MUDUO_ROOT}/lib)

add_executable(chat_client
    main.cc
    Client.cc
    ../server/Router.cc
    ../protocal/pack.cpp
    ../protocal/unpack.cpp
)

target_link_libraries(chat_client
    muduo_net
    muduo_base
    jsoncpp
    pthread
)