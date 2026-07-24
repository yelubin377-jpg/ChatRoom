#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <cassert>

class Buffer
{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;
    explicit Buffer(size_t initialSize = kInitialSize)
        : buffer_(kCheapPrepend + initialSize),
          readerIndex_(kCheapPrepend),
          writerIndex_(kCheapPrepend)
    {} 
    void swap(Buffer& rhs)
    {
        buffer_.swap(rhs.buffer_);
        std::swap(readerIndex_, rhs.readerIndex_);
        std::swap(writerIndex_, rhs.writerIndex_);
    }
    const char* peek() const
    {
        return begin() + readerIndex_;
    }
    size_t readableBytes() const
    {
        return writerIndex_ - readerIndex_;
    }
    void retrieve(size_t len)
    {
        assert(len <= readableBytes());
        readerIndex_ += len;
    }


    const char* begin() const
    {
        return buffer_.data();
    }
    size_t writableBytes() const
    {
        return buffer_.size() - writerIndex_;
    }
    void ensureWritable(size_t len)
    {
        if(writableBytes() >= len)
        {
            return;
        }
        size_t prependable = readerIndex_;
        if(prependable + writableBytes() >= len + kCheapPrepend)
        {
            size_t prependable = readerIndex_;
            if(prependable + writableBytes() >= len + kCheapPrepend)
            {
                size_t readable = readableBytes();
                std::copy(begin()+readerIndex_,
                          begin()+writerIndex_,
                          begin()+kCheapPrepend);
                readerIndex_ = kCheapPrepend;
                writerIndex_ = readerIndex_ + readable;
            }
            else
            {
                buffer_.resize(writerIndex_ + len);
            }
        }
    }
    void append(const char* data,size_t len)
    {
        ensureWritable(len);
        std::copy(data,data + len,begin() + writerIndex_);
        writerIndex_ += len;
    }
    

    ssize_t readFd(int fd,int* savedErrno)
    {
        char extrabuf[65536];
        struct iovec vec[2];
        const size_t writable = writableBytes();

        vec[0].iov_base = begin() + writerIndex_;
        vec[0].iov_len = writable;
        vec[1].iov_base = extrabuf;
        vec[1].iov_len = sizeof(extrabuf);
        const ssize_t n = ::readv(fd, vec, 2);
        if(n<0)
        {
            *savedErrno = errno;
        }
        else if(static_cast <size_t>(n) <= writable)
        {
            writerIndex_ += n;
        }
        else
        {
            writerIndex_ = buffer_.size();
            append(extrabuf,n - writable);
        }
    }

    
};