#include "epoll.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<iostream>
int my_epoll::http_epoll_create(int num)
{
    int epfd = epoll_create(num);
    if(epfd == -1)
    {
        perror("epoll_create error");
        exit(-1);
    }
    return epfd;
}
int my_epoll::epoll_add_event(int fd,int state)
{
    struct epoll_event *ev;
    ev->events = state;
    ev->data.fd = fd;
    int err = epoll_ctl(_my_epfd,EPOLL_CTL_ADD,fd,ev);
    if(err == -1)
    {
        perror("epoll add event error");
        exit(-1);
    }
    return 0;
}

 int my_epoll::epoll_delete_event(int fd_del,int state)
 {
     struct epoll_event *ev_del;
     ev_del->events = state;
     ev_del->data.fd = fd_del;

     int err = epoll_ctl(_my_epfd,EPOLL_CTL_DEL,fd_del,ev_del);
     if(err == -1)
     {
         perror("epoll delete event error");
         exit(-1);
     }
     close(fd_del);
     return 0;
 }

 int my_epoll::handle_accept(int listenfd)
 {
     int conn_sock;
     int flags;
     struct sockaddr_in clientaddr;
     socklen_t cliaddr_len;

     while((conn_sock = accept(listenfd,(sockaddr*)&clientaddr,&cliaddr_len)) > 0)
     {
         std::cout<<"client ip:"<< ntohl(clientaddr.sin_addr)<<std::endl;

         flags = fcntl(conn_sock,F_GETFL,0);
         flags |= O_NONBLOCK;
         fcntl(conn_sock,F_SETFL,flags);

         epoll_add_event(conn_sock,EPOLLIN|EPOLLET);
     }
     if(conn_sock == -1)
     {
         if(errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && error!= EINTR)
         {
             perror("accept error");
         }
     }
     return 0;
 }
 //function函数模板 返回值为void 参数为一个int型
int my_epoll::set_callback(std::function<void (int)> &fcn)
{
    read_callback = fcn;
}

int my_epoll::add_to_channel(int fd, ChannelList &work_list)
{
    ChannelList *new_one = new ChannelList(fd);
    new_one->set_read_flag(true);

    std::function<void()> fct = [=]{read_callback(fd);};
    new_one->set_read_callback(fct);

    std::function<void(int)>  fct_int = std::bind(my_epoll::epoll_delete_event,this,std::placeholders::_1);
    new_one->set_complete_callback(fct_int);

    pthread_mutex_lock(_mutex_ptr);
    work_list.push_back(new_one);

    pthread_cond_signal(_cond_ptr);
    pthread_mutex_unlock(_mutex_ptr);
    return 0;
}
int my_epoll::loop(ChannelList &work_list)
{

}
