#ifndef TOPWIDGET_H
#define TOPWIDGET_H
#include<QtWidgets>
#include"widget.h"
#include"network.h"


//该下棋软件的顶层窗口类
class topwidget:public QWidget
{
    Q_OBJECT
    enum INSTRUCT_TYPE{
        RETRACT,
        CHESS_ACT
    };

public:
    topwidget(QWidget *parent=0);
    ~topwidget();
public:
    widget * boardwidget;//棋盘窗口
    QImage image;//软件背景图片数据
    QImage sideimage;//左侧图片数据
    network *net;//网络引擎
    inline bool ischatting() const{return chat;}//区分发送的数据是聊天数据还是下棋的动作数据
    inline void setchatting(bool ischat) {chat=ischat;}
    inline bool isback() const{return back;}
    inline void setback(bool isback){back=isback;}


protected:
    void paintEvent(QPaintEvent *);
public:
    QPushButton *quitbutton;//退出按钮
    QPushButton *vs_machinebutton;//人机对战按钮
    QPushButton *vs_networkbutton;//网络对战按钮
    QPushButton *vs_freebutton;
    QPushButton *sendmessagebutton;//发送聊天消息按钮
    QPushButton *backbutton; //悔棋按钮
    QTextBrowser *textbrowser;//显示聊天的文本框
    QLineEdit *inputedit;//聊天消息输入框
    QLineEdit *destipedit;//对方IP地址
    QLineEdit *destportedit;//对方端口号
    QLineEdit *localportedit;//自己的端口号
public:
    bool back; //悔棋标志
    bool chat;//聊天标志


 private:
    void init_subwidgets();//初始化所有的子窗口部件


signals:
    void ready_get_rival_data();//读网络端的下棋数据信号，与棋盘窗口部件的get_rival_data()槽连接，由read_data_slot()槽发射

private slots:
    void start_vs_machine_slot();//开启人机对战功能
    void start_vs_network_slot();//开启网络对战功能
    void start_vs_free_slot();//开启自由对谱功能
    void on_backbutton_slot();//悔棋槽函数
    void back_to_send(); //发送悔棋消息的槽函数
    void chat_to_send();//发送聊天消息的槽,响应发送按钮
    void chess_to_send();//发送下棋动作的数据给网络上的敌方，

    void send_data_slot();//发送string数据的槽，
    void read_data_slot();//读取string数据的槽，与网络引擎net的readyread()信号连接
};


#endif // TOPWIDGET_H
