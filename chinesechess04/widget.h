#ifndef WIDGET_H
#define WIDGET_H
#include<QtWidgets>
#include"chessboard.h"


//装载棋盘的窗口部件类
class widget:public QWidget
{
    Q_OBJECT
public:
    enum VS_TYPE{   // 对战类型，有：网络对战、单机自由对谱、对战电脑
        NET_VS,
        FREE_VS,
        PC_VS,
        INVALID
    };

public:
    widget(QWidget *parent=0);
    ~widget();

    inline bool is_net_vs() const { return vstype==NET_VS; }//是否为网络对战状态
    inline void set_vs_type(widget::VS_TYPE type){ vstype=type;}//设置对战类型
    inline bool is_computer_vs() const { return vstype==PC_VS; }//是否为单机对战
    inline bool is_free_vs() const { return vstype==FREE_VS; }//是否为自由对谱
    inline bool is_chess_start()const{ return chess_start;}//是否已开启棋局
    inline void set_chess_start(bool start){ chess_start = start;}//设置棋局开始或结束

    void init_hash_pos();//初始化逻辑位置与像素点矩形的哈希表
    inline bool contains(int x,int y) const { return rect_valid.contains(x,y); }//判断点（x,y)是否在棋盘内
    inline bool contains(QPoint &pos ) const { return rect_valid.contains(pos.x(),pos.y()); }//重载
    inline QRect rect() const {return rect_valid;}//获取棋盘的矩形区域
    inline int dx() const{ return dxvalue; }//返回棋格在x方向的宽度
    inline int dy() const{ return dyvalue; }//返回棋格在y方向的宽度
    inline int xbase() const{ return xbasevalue; }//返回棋子在棋盘上定位所需的基础坐标x
    inline int ybase() const{ return ybasevalue; }//返回棋子在棋盘上定位所需的基础坐标y
    inline int roleplaying() const{ return role; }
    inline void set_roleplaying(int roleplaying) {role=roleplaying;}

public:
    chessboard *board;
    QHash<int,QRect> hash_pos;//逻辑位置与像素点矩形的哈希表
    QPoint point_clicked;//被点中的像素点经转换后的逻辑坐标
    int action_type;//下棋动作类型，由棋局实体board的方法analyse_action（int x,int y)返回接受的值


private:
    bool chess_start;//状态，是否开启棋局下棋
    int vstype;//对战类型；
    QRect rect_valid;//棋盘的有效区域
    int dxvalue;//棋格在x方向的宽度
    int dyvalue;//棋格在y方向的宽度
    int xbasevalue;//棋子在棋盘上定位所需的基础坐标x
    int ybasevalue;//棋子在棋盘上定位所需的基础坐标y
    int role;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

signals:
    void tell_rival_chessboard();//在网络对战时，

};

#endif // WIDGET_H
