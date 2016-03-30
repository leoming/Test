#include"network.h"


network::network(bool enable_tcpclient, int tcpserverport, QString tcpserverip, QObject *parent)
{
    tcpclient_enable=enable_tcpclient;
    tcpserver_enable=false;
    udp_enable=false;
    type_data_to_read=INVALIDPROTOCOL;

    if(tcpserverip.contains("localhost"))
        serveraddress_tcp = QHostAddress::LocalHost;
    else
        serveraddress_tcp.setAddress(tcpserverip);
    serverport_tcp = tcpserverport;

    socket_tcpclient=NULL;
    socket_tcpserver=NULL;
    socket_session_tcp=NULL;
    socket_udp=NULL;

    if(tcpclient_enable)
        tcpclient_enable=init_tcpclient();
    qDebug()<<"end of the tcpclient construct";

}

network::network(bool enable_tcpserver,int tcpserverport,QObject *parent)
{
    tcpserver_enable=enable_tcpserver;
    tcpclient_enable = false;
    udp_enable=false;
    type_data_to_read=INVALIDPROTOCOL;
    socket_tcpclient=NULL;
    socket_tcpserver=NULL;
    socket_session_tcp=NULL;
    socket_udp=NULL;
    if(tcpserver_enable)
    {
        serveraddress_tcp = QHostAddress::LocalHost;
        serverport_tcp = tcpserverport;
        tcpserver_enable=init_tcpserver();
    }
    qDebug()<<"construct of tcp server end";
}

network::network(bool enable_udp, QString destip, int destport_udp, int bindport,QObject *parent)
{
    udp_enable=enable_udp;
    tcpserver_enable=false;
    tcpclient_enable=false;
    type_data_to_read=network::INVALIDPROTOCOL;
    if(destip.contains("localhost"))
        destaddress = QHostAddress::LocalHost;
    else
        destaddress.setAddress(destip);
    destport = destport_udp;
    bindport_udp = bindport;
    socket_tcpclient=NULL;
    socket_tcpserver=NULL;
    socket_session_tcp=NULL;
    socket_udp=NULL;
    if(udp_enable)
        udp_enable = init_udp();

}

bool network::send_data(QString data, int argprotocol)
{
    int protocol;
    buffer_out.clear();
    buffer_out.append(data);
    outblock.resize(0);
    //outblock.append(buffer_out);
    QDataStream out(&outblock,QIODevice::ReadWrite);
    out<<data;
    if(argprotocol!=network::TCPSERVER && argprotocol!=network::TCPCLIENT && argprotocol!=network::UDP)
        protocol=type_data_to_write;
    else
        protocol=argprotocol;
    if(protocol==network::TCPSERVER && socket_session_tcp!=NULL)
        return send_as_tcpserver();
    else if(protocol==network::TCPCLIENT && socket_tcpclient!=NULL)
        return send_as_tcpclient();
    else if(protocol==network::UDP && socket_udp != NULL)
        return send_as_udp();
    else if(socket_udp!=NULL)
        return send_as_udp();
    else
        return false;

}

bool network::send_bytes_data(QByteArray data, int argprotocol)
{
    int protocol;
    outblock.resize(0);
    outblock=data;
    buffer_out.clear();

    QDataStream out(&outblock,QIODevice::ReadWrite);
    out.device()->seek(0);
    out>>buffer_out;

    if(argprotocol!=network::TCPSERVER && argprotocol!=network::TCPCLIENT && argprotocol!=network::UDP)
        protocol=type_data_to_write;
    else
        protocol=argprotocol;
    if(protocol==network::TCPSERVER && socket_session_tcp!=NULL)
        return send_as_tcpserver();
    else if(protocol==network::TCPCLIENT && socket_tcpclient!=NULL)
        return send_as_tcpclient();
    else if(protocol==network::UDP && socket_udp != NULL)
        return send_as_udp();
    else if(socket_udp!=NULL)
        return send_as_udp();
    else
        return false;

}

QString network::receive_data(int argprotocol)
{
    int protocol=argprotocol;
    if(protocol!=network::TCPSERVER && protocol!=network::TCPCLIENT && protocol != network::UDP)
        protocol = type_data_to_read;

    inblock.resize(0);
    if(protocol==network::TCPSERVER)
        receive_as_tcpserver();
    else if(protocol==network::TCPCLIENT)
        receive_as_tcpclient();
    else if(protocol==network::UDP)
        receive_as_udp();
    buffer_in.clear();
    QDataStream in(&inblock,QIODevice::ReadWrite);
    in.device()->seek(0);
    in >> buffer_in;

    //buffer_in.append(inblock);
    return buffer_in;
}

QByteArray network::receive_bytes_data(int argprotocol)
{
    int protocol=argprotocol;
    if(protocol!=network::TCPSERVER && protocol!=network::TCPCLIENT && protocol != network::UDP)
        protocol = type_data_to_read;

    inblock.resize(0);
    if(protocol==network::TCPSERVER)
        receive_as_tcpserver();
    else if(protocol==network::TCPCLIENT)
        receive_as_tcpclient();
    else if(protocol==network::UDP)
        receive_as_udp();
    /*
    buffer_in.clear();
    QDataStream in(&inblock,QIODevice::ReadWrite);
    in.device()->seek(0);
    in >> buffer_in;
    */
    return inblock;
}



bool network::send_as_tcpserver()
{
    if(socket_session_tcp==NULL)
    {
        qDebug()<<"the socket_sesion_tcp is NULL !!!";
        return false;
    }
    socket_session_tcp->write(outblock);
}

bool network::send_as_tcpclient()
{
    if(socket_tcpclient==NULL)
    {
        qDebug()<<"the socket_tcpclient is NULL !!!";
        return false;
    }
    socket_tcpclient->write(outblock);
}

bool network::send_as_udp()
{
    if(socket_udp==NULL)
    {
        qDebug()<<"the socket_udp is NULL !!!";
        return false;
    }
   socket_udp->writeDatagram(outblock,destaddress,destport);
}

bool network::receive_as_tcpserver()
{
    if(socket_session_tcp==NULL)
    {
        qDebug()<<"the socket_sesion_tcp is NULL !!!";
        return false;
    }
    qDebug()<<"in the network receive_as_tcpserver";
    inblock = socket_session_tcp->readAll();
}

bool network::receive_as_tcpclient()
{
    if(socket_tcpclient==NULL)
    {
        qDebug()<<"the socket_tcpclient is NULL !!!";
        return false;
    }
    qDebug()<<"in the network receive_as_tcpclient";
    inblock.append(socket_tcpclient->readAll());
}

bool network::receive_as_udp()
{
    if(socket_udp==NULL)
    {
        qDebug()<<"the socket_udp is NULL !!!";
        return false;
    }
    if(socket_udp->bytesAvailable()>0)
    {
        QDataStream in(&inblock,QIODevice::ReadWrite);
        inblock.resize(socket_udp->bytesAvailable());
        socket_udp->readDatagram(inblock.data(),inblock.size());
    }
    else
        qDebug()<<"receive_as_udp : bytes <= 0";
    return true;
}



bool network::init_tcpserver()
{
    qDebug()<<"init tcpserver";
    socket_tcpserver = new QTcpServer;
    socket_tcpserver->listen(serveraddress_tcp,serverport_tcp);
    connect(socket_tcpserver,SIGNAL(newConnection()),this,SLOT(set_newconnection()));

}

void network::set_newconnection()
{
    if(socket_session_tcp!= NULL)
        delete socket_session_tcp;
    if(socket_session_tcp==NULL )
        qDebug()<<"before session tcp ==NULL";
    socket_session_tcp = socket_tcpserver->nextPendingConnection();
    if(socket_session_tcp!=NULL )
        qDebug()<<"set_newconnection";
    connect(socket_session_tcp,SIGNAL(readyRead()),this,SLOT(has_data_to_read()));
    type_data_to_write=network::TCPSERVER;
}

bool network::init_tcpclient()
{
    qDebug()<<"init tcpclient";
    socket_tcpclient = new QTcpSocket;
    socket_tcpclient->connectToHost(serveraddress_tcp,serverport_tcp);
    connect(socket_tcpclient,SIGNAL(readyRead()),this,SLOT(has_data_to_read()));
    type_data_to_write=network::TCPCLIENT;
    qDebug()<<"after connect to host in init_tcpclient";
    return true;

}

bool network::init_udp()
{
    qDebug()<<"init udp";
    socket_udp = new QUdpSocket;

    if( socket_udp->bind(QHostAddress::LocalHost,bindport_udp) )
    {
        connect(socket_udp,SIGNAL(readyRead()),this,SLOT(has_data_to_read()));
        type_data_to_write=network::UDP;
        return true;
    }

}


void network::has_data_to_read()
{
    qDebug()<<"in network has_data_to_read";
    if(socket_tcpclient!=NULL && socket_tcpclient->bytesAvailable()>0)
        type_data_to_read = network::TCPCLIENT;
    else if(socket_session_tcp!=NULL && socket_session_tcp->bytesAvailable()>0)
        type_data_to_read = network::TCPSERVER;
    else if(socket_udp != NULL && socket_udp->bytesAvailable()>0)
        type_data_to_read = network::UDP;
    else type_data_to_read = network::INVALIDPROTOCOL;
    if( type_data_to_read != network::INVALIDPROTOCOL )
    {
        qDebug()<<"emit ready_to_read signal";
        emit ready_to_read();
    }
}

network::~network()
{

}



