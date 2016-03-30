#ifndef CHESSMAN_H
#define CHESSMAN_H
#include<QObject>
#include<QtGui>

//中国象棋棋子类
class chessman : public QObject
{
    Q_OBJECT
public:
    enum ROLE     //红绿角色枚举值
    {
        RED_MAN = -1,
        GREEN_MAN = 1
    };
    enum Chessman_name{
        G_MARSHAL = -1,  //绿帅
        G_SERGEANCY = -2,    //绿士
        G_ELEPHANT = -3,     //绿象
        G_HORSE = -4,        //绿马
        G_GHARRY = -5,       //绿车
        G_CANNON = -6,       //绿炮
        G_SOLDIER = -7,      //绿兵

        R_MARSHAL = 1,      //红帅
        R_SERGEANCY = 2,    //红士
        R_ELEPHANT = 3,     //红象
        R_HORSE = 4,        //红马
        R_GHARRY = 5,       //红车
        R_CANNON = 6,       //红炮
        R_SOLDIER =7      //红兵
    };
public:
    chessman();
    chessman(class chessman &man);
    chessman( chessman::ROLE roleplaying, chessman::Chessman_name chessmanname,QString imagefilename1,QString imagefilename2);
    ~chessman();
    inline bool isdead(){return deadflag;}//判断棋子的生死状态
    inline void setdead(bool life){deadflag=life;}//设置棋子的生死状态
    const chessman::Chessman_name name();//获取棋子名称，返回的是枚举值
    inline int role()const{return rolevalue;}//返回棋子角色红或绿
    inline void setrole(chessman::ROLE role_arg){rolevalue=role_arg;}//设置棋子角色红或绿
    inline int power()const{return powervalue;}//返回棋子的棋力
    inline void setpower(int power_arg){powervalue=power_arg;}//设置棋子的棋力
    inline void setimage_unselected(){image_to_show=&image1;}//非选中状态下的棋子正常显示图片
    inline void setimage_selected(){image_to_show=&image2;}//选中状态下的棋子正常显示图片
public:
    QPoint pos;//棋子在棋盘上的位置，逻辑坐标
    QImage * image_to_show;//需要送外显示的棋子外观
private:
    enum Chessman_name chessmanname;//棋子名称
    bool deadflag;//死亡标志
    int powervalue;//棋力值
    int rolevalue;//角色值
    QString imagefilename1;//图片文件一（非选中状态下）名
    QString imagefilename2;//图片文件二（选中状态下）名
    QImage image1;//图片一的结构数据
    QImage image2;//图片二的结构数据
private:
    bool init_images();//初始化棋子的图片结构
    inline void setname(chessman::Chessman_name name){chessmanname=name;}//设置棋子的名称（枚举值）
};

#endif // CHESSMAN_H
