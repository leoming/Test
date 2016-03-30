#ifndef NETWORK_H
#define NETWORK_H
#include<QtNetwork>
#include<QObject>
#include<QtGui>
#define SERVER_PORT_TCP 9898

/*
  network是将TCP和UDP封装在一起，用户在使用network时的用法如下：
     例如 使用UDP ：     network * net = new network(true,dest_ip,dest_port,local_port);//其中的参数依次是 true,目的IP，目的端口，本地端口
                       connect(net,SIGNAL(ready_to_read()),this,SLOT(read_data_slot()));//network类有一个准备读数据的信号，
                       //用户要从网络读取数据就要自己定义一个读数据的槽函数例如（read_data_slot()）与这个信号相连即可
                       QString str("the data to send");
                       net->send_data(str,network::UDP); //发送数据str
                       QString sstr = net->receive_data(network::UDP);接收数据给str

         使用TCP客户端： network * net = new network(true,server_port,server_ip);//其中参数依次是 true,TCP服务器端口号，TCP服务器IP
                       connect(net,SIGNAL(ready_to_read()),this,SLOT(read_data_slot()));//network类有一个准备读数据的信号，
                       //用户要从网络读取数据就要自己定义一个读数据的槽函数例如(read_data_slot())与这个信号相连即可
                       QString str("the data to send");
                       net->send_data(str,network::TCPCLIENT);
                       QString sstr=net->receive_data(network::TCPCLIENT);

         使用TCP服务端： network * net = new network(true,server_port);//其中参数依次是 true,TCP服务器端口号，即自己要绑定的端口用于QTcpServer初始化
                       connect(net,SIGNAL(ready_to_read()),this,SLOT(read_data_slot()));//network类有一个准备读数据的信号，
                       //用户要从网络读取数据就要自己定义一个读数据的槽函数例如（read_data_slot()）与这个信号相连即可
                       QString str("the data to send");
                       net->send_data(str,network::TCPSERVER);
                       QString sstr=net->receive_data(network::TCPSERVER);

*/

class network:public QObject
{
    Q_OBJECT
public:
    enum ROLE_PROTOCOL
    {
        TCPSERVER,
        TCPCLIENT,
        UDP,
        INVALIDPROTOCOL
    };
    network(bool enable_tcpclient,int serverport,QString serverip,QObject *parent=0);//
    network(bool enable_tcpserver,int serverport,QObject *parent=0);//
    network(bool enable_udp,QString destip,int destport_udp,int bindport,QObject*parent=0);//
     ~network();

    inline bool isenable_tcpserver(){return tcpserver_enable;}//
    inline bool isenable_tcpclient(){return tcpclient_enable;}//
    inline bool isenable_udp(){return udp_enable;}//

public:
    QHostAddress destaddress;//目的主机
    QHostAddress serveraddress_tcp;//TCP服务器端口
    int destport;//目的端口
    int bindport_udp;//UDP本地绑定端口
    int serverport_tcp;//TCP服务器端口

    QTcpSocket *socket_tcpclient;//TCP客户端套接字
    QTcpServer *socket_tcpserver;//TCP服务端套接字用于侦听
    QTcpSocket *socket_session_tcp;//TCP服务端新开的套接字用于通信
    QUdpSocket *socket_udp;//UDP套接字
    QString buffer_out;//客户发送数据时会将数据暂存在此
    QString buffer_in;//客户接收数据时会从此处拿走数据
    QByteArray outblock;//输出缓冲区
    QByteArray inblock;//输入缓冲区
    int type_data_to_read;//需要读取的数据的类型
    int type_data_to_write;//需要发送的数据的类型
    bool send_data(QString data,int protocol);//发送数据
    bool send_bytes_data(QByteArray data,int protocol);//发送数据
    QString receive_data(int protocol);//接收数据
    QByteArray receive_bytes_data( int protocol);

private:
    bool tcpserver_enable;//TCP服务器使能标志
    bool tcpclient_enable;//TCP客户端使能标志
    bool udp_enable;//UDP使能标志

    bool init_tcpserver();//初始化TCP服务器
    bool init_tcpclient();//初始化TCP客户端
    bool init_udp();//初始化UDP

signals:
    void ready_to_read();//准备读取数据的信号
    void explains();//保留

private slots:
    bool send_as_tcpserver();//以TCP服务器的角色发送数据
    bool send_as_tcpclient();//以TCP客户端的角色发送数据
    bool send_as_udp();//以UDP的角色发送数据
    bool receive_as_tcpserver();//以TCP服务器的角色接收数据
    bool receive_as_tcpclient();//以TCP客户端的角色接收数据
    bool receive_as_udp();//以UDP的角色接收数据
    void has_data_to_read();//有数据需要读取的槽函数，
    void set_newconnection();//TCP服务器有新的连接请求时设置好新的连接
};



#endif // NETWORK_H
