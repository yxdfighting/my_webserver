#ifndef EPOLL_H
#define EPOLL_H
#include<sys/epoll.h>
#include<functional>
#include<list>
class my_epoll
{
public:
    my_epoll(int listen,pthread_mutex_t *mutex,pthread_cond_t *cond):
        _listenfd(listen), _my_epfd(0),_mutex_ptr(mutex), _cond_ptr(cond) { }
    ~my_epoll() = default;
    int handle_accept(int listenfd);
    int loop(ChannelList & work_list);
    int http_epoll_create(int num);
    int epoll_add_event(int fd,int state);
    int epoll_delete_event(int fd_del,int state);
    int set_callback(std::function<void(int)> &fcn);
    int add_to_channel(int fd,ChannelList &work_list);
 private:
    int _listenfd;
    int _my_epfd;
    pthread_mutex_t * _mutex_ptr;
    pthread_cond_t * _cond_ptr;
    typedef std::list<Channel *> ChannelList;
    std::function<void(int)> read_callback;
};

#endif // EPOLL_H
