#include"topwidget.h"



topwidget::topwidget(QWidget *parent):QWidget(parent)
{
    boardwidget = new widget(this);
    boardwidget->setHidden(true);
    boardwidget->move(360,0);
    setFixedSize(360+458,600);
    init_subwidgets();
    image.load(tr("images/background.jpg"));
    sideimage.load(tr("images/sidebackground.jpg"));
    connect(quitbutton,SIGNAL(clicked()),this,SLOT(close()));
    connect(vs_machinebutton,SIGNAL(clicked()),this,SLOT(start_vs_machine_slot()));
    connect(vs_networkbutton,SIGNAL(clicked()),this,SLOT(start_vs_network_slot()));
    connect(vs_freebutton,SIGNAL(clicked()),this,SLOT(start_vs_free_slot()));
    connect(backbutton,SIGNAL(clicked()),this,SLOT(on_backbutton_slot()));
    net = NULL;
    setchatting(false);
    setback(false);
}

topwidget::~topwidget(){}

void topwidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor color(250,235,215);
    QBrush brush(color);
    painter.setBrush(brush);
    if(!boardwidget->is_chess_start())
        painter.drawImage(0,0,image);
    else
    {
        painter.fillRect(QRect(360,505,458,95),brush);
        painter.drawImage(QRect(0,0,360,600),sideimage);
    }
}

void topwidget::init_subwidgets()
{
    quitbutton = new QPushButton(tr("退出"),this);
    quitbutton->move(360,540);
    quitbutton->setStyleSheet("background-color:transparent");

    vs_machinebutton = new QPushButton(tr("人机对战"),this);
    vs_machinebutton->move(440,540);
    vs_machinebutton->setStyleSheet("background-color:transparent");
    vs_networkbutton = new QPushButton(tr("网络对战"),this);
    vs_networkbutton->move(520,540);
    vs_networkbutton->setStyleSheet("background-color:transparent");
    vs_freebutton = new QPushButton(tr("自由对谱"),this);
    vs_freebutton->move(600,540);
    vs_freebutton->setStyleSheet("background-color:transparent");
    backbutton = new QPushButton(tr("悔棋"),this);
    backbutton->move(680,540);
    backbutton->setStyleSheet("background-color:transparent");

    inputedit = new QLineEdit(this);
    inputedit->setStyleSheet("background-color:transparent");
    inputedit->setFixedSize(180,40);
    inputedit->move(90,360);
    inputedit->setHidden(true);
    textbrowser = new QTextBrowser(this);
    textbrowser->setStyleSheet("background-color:transparent");
    textbrowser->setHidden(true);
    textbrowser->setFixedSize(180,180);
    textbrowser->move(90,170);

    sendmessagebutton = new QPushButton(tr("发送"),this);
    sendmessagebutton->move(230,420);
    sendmessagebutton->setHidden(true);

    destipedit = new QLineEdit(this);
    destipedit->setText(tr("localhost"));
    destportedit = new QLineEdit(this);
    destportedit->setText(QString::number(8888));
    localportedit = new QLineEdit(this);
    localportedit->setText(QString::number(9999));
    destipedit->move(90,420);
    destportedit->move(90,480);
    localportedit->move(90,540);
}

void topwidget::start_vs_machine_slot()
{

    boardwidget->set_vs_type(widget::PC_VS);

    boardwidget->set_chess_start(true);

    boardwidget->setHidden(false);
    inputedit->setHidden(false);
    textbrowser->setHidden(false);
    sendmessagebutton->setHidden(false);
    update();
}

void topwidget::start_vs_network_slot()
{
    if(destipedit->text().isEmpty()||destportedit->text().isEmpty()||localportedit->text().isEmpty())
        return;
    boardwidget->set_vs_type(widget::NET_VS);
    boardwidget->set_chess_start(true);
    boardwidget->setHidden(false);
    inputedit->setHidden(false);
    textbrowser->setHidden(false);
    sendmessagebutton->setHidden(false);
    if(net!=NULL)
        return;
    bool ok=true;
    //开启网络的函数，即new一个network；填入IP，PORT等信息即可打开网络，
    net = new network(true,destipedit->text(),destportedit->text().toInt(&ok),localportedit->text().toInt(&ok));
    connect(sendmessagebutton,SIGNAL(clicked()),this,SLOT(chat_to_send()));
    connect(net,SIGNAL(ready_to_read()),this,SLOT(read_data_slot()));
    connect(boardwidget,SIGNAL(tell_rival_chessboard()),this,SLOT(chess_to_send()));

    update();
}

void topwidget::start_vs_free_slot()
{

    boardwidget->set_vs_type(widget::FREE_VS);

    boardwidget->set_chess_start(true);

    boardwidget->setHidden(false);
    inputedit->setHidden(false);
    textbrowser->setHidden(false);
    sendmessagebutton->setHidden(false);
    update();
}

void topwidget::chat_to_send()
{
    setchatting(true);
    send_data_slot();
    setchatting(false);
}

void topwidget::chess_to_send()
{
    send_data_slot();
}

void topwidget::back_to_send()
{
    qDebug()<<"back_to_send";
    if(isback())
    {
        qDebug()<<"before send_data_slot";
        send_data_slot();
        qDebug()<<"after send_data_slot";
    }

}

void topwidget::on_backbutton_slot()
{
    qDebug()<<"on_backbutton_slot";
    setback(true);
    boardwidget->board->back_in_chessboard();
    if(boardwidget->is_net_vs())
        back_to_send();
    setback(false);
}


void topwidget::send_data_slot()
{

    if( ischatting() && inputedit->text().isEmpty())
    {
        setchatting(false);
        return;
    }
    if(ischatting())
    {
        setchatting(false);
        QString string;
        string.append(':');
        string.append(inputedit->text());
        net->send_data(string,network::INVALIDPROTOCOL);
        inputedit->clear();
        textbrowser->append(inputedit->text());
    }
    else if(!isback())
    {
        QString string;
        qint8 instruct = CHESS_ACT;
        qint8 pos = ((9-(boardwidget->board->point_actived.y()))*10+(8-(boardwidget->board->point_actived.x())));
        qint8 type = (boardwidget->board->last_action_type);
        string.append(tr("%1").arg(instruct));
        string.append(tr(" "));
        string.append(tr("%1").arg(type));
        string.append(tr(" "));
        string.append(tr("%1").arg(pos));
        net->send_data(string,network::INVALIDPROTOCOL);
    }
    else if(isback())
    {
        QString string;
        qint8 instruct =chessboard::BACK;
        string.append(tr("%1").arg(instruct));
        net->send_data(string,network::INVALIDPROTOCOL);
    }
}

void topwidget::read_data_slot()
{
    QString str(net->receive_data(network::INVALIDPROTOCOL));
    if(!str.isEmpty() && *(str.toStdString().c_str())==':')
        textbrowser->append(str);
    else
    {
        QStringList strlist = str.split(" ");
        QStringList::iterator  it = strlist.begin();
        bool ok=true;
        qint8 instruct = static_cast<QString>(*it).toInt(&ok);
        if(instruct==chessboard::BACK)
        {
            qDebug()<<"act back";
            boardwidget->board->back_in_chessboard();
        }
        else if(instruct==CHESS_ACT)
        {
            qDebug()<<"act chess";
            it++;
            qint8 act_type = static_cast<QString>(*it).toInt(&ok);
            it++;
            qint8 pos = static_cast<QString>(*it).toInt(&ok);
            int x = pos%10;
            int y = pos/10;
            boardwidget->action_type=act_type;
            boardwidget->point_clicked.setX(x);
            boardwidget->point_clicked.setY(y);
           // boardwidget->board->point_actived.setX(x);
           // boardwidget->board->point_actived.setY(y);
           // boardwidget->board->last_action_type=(chessboard::ACT_TYPE)(act_type);
            qDebug()<<"y="<<y<<" x="<<x;
            switch(act_type){
            case chessboard::SELECT :qDebug()<<"*** SELECT ***";
                boardwidget->board->do_selected(x,y);break;
            case chessboard::EAT :qDebug()<<"**** EAT ***";
                boardwidget->board->action_in_chessboard(x,y);break;
            case chessboard::MOVE :qDebug()<<"****MOVE ****";
                boardwidget->board->action_in_chessboard(x,y);break;
            default: break;
            }
        }
    }
}


