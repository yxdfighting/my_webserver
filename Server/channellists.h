#ifndef CHANNELLISTS_H
#define CHANNELLISTS_H
#include<functional>

class ChannelLists
{
public:
    typedef std::function<void()> callback;
    typedef std::function<void(int)> completeCallback;

    ChannelLists(int connfd);
    ~ChannelLists() = default;



private:
    int _fd;
    bool _read_flag;
    bool _write_flag;
    bool _com_flag;

    callback _read_callable;
    callback _write_callable;
    completeCallback _complete_callback;
};

#endif // CHANNELLISTS_H
