#ifndef CHESS_H
#define CHESS_H
#include<QtGui>
#include"chessman.h"

//#define CURRENT_ROLE chessman::RED_MAN
#define CURRENT_ROLE chessman::GREEN_MAN

//中国象棋棋盘类
class chessboard : public QObject
{
    Q_OBJECT
public:
    enum ACT_TYPE  //下棋动作类型，分为无效，选中，移动，吃子,悔棋
    {
        INVALID,
        SELECT,
        MOVE,
        EAT,
        BACK
    };
    struct motion_data
    {
        QLine line;
        ACT_TYPE type;
    };

public:
    chessboard();
    ~chessboard();

    inline void setfootprint(QPoint &point){footprint=point;}//移动之后要设置脚印
    inline void setfootprint(int x,int y){ footprint.setX(x);footprint.setY(y);}//重载设置函数
    inline void footprint_clear(){ footprint.setX(-1); }//清除脚印
    inline bool footprint_isEmpty(){ return footprint.x()==-1; }//判断有无脚印
    inline int footprint_x() const { return footprint.x();}//获取脚印的X值
    inline int footprint_y() const { return footprint.y();}//获取脚印的Y值 

    inline int role_actived() const { return roleactived; }//获取当前应该下棋的角色方
    inline void toggle_role_actived() { roleactived = -roleactived; }//反转当前应该下棋的角色
    inline void set_role_actived(chessman::ROLE role){ roleactived=role; }//设置当前应该下棋的角色

public:
    class chessman * chess[10][9];//10 X 9 个落子点的棋子指针，落子点无棋子时就为空
    class chessman * chessman_selected;//被选中的棋子指针，如无棋子被选中，则为空指针，
    class chessman * chessman_last_moved;//某棋子从A移动到B之后，该指针指向该棋子，chessman_selected指针被指空

    QStack<struct motion_data> motion_stack;//供悔棋动作操作的过往动作堆栈数据
    QStack<class chessman *> deadstack;//状态为死亡的棋子堆栈，在吃子动作时应该将死亡棋子压入栈中
    QHash<int,class chessman *> hash_chessman;//哈希表，保存着以棋子名称为键值的棋子指针
    QImage boardimage;//棋盘背景图片数据结构
    QImage boximage;//脚印图片数据结构
    enum ACT_TYPE last_action_type;
    QPoint point_actived;

public:
    void do_selected(int x,int y);//执行选子动作
    bool do_chessboard_analyse(int x,int y);//根据棋子名称来将分析任务分发给相应的棋子分析引擎
    void action_in_chessboard(int x,int y);//执行移动或吃子的动作，完成坐标变换，更新脚印等任务 
    void back_in_chessboard();
private:

    QPoint footprint;//脚印坐标
    int roleactived;//当前该下棋的角色值
    bool init_chessmans();//初始化所有棋子
    bool init_images();//初始化棋盘的图片背景
    bool do_marshal_analyse(int x,int y);   //“帅”的分析引擎
    bool do_sergeancy_analyse(int x,int y); //“士”的分析引擎
    bool do_elephant_analyse(int x,int y);  //“象”的分析引擎
    bool do_horse_analyse(int x,int y);     //“马”的分析引擎
    bool do_gharry_analyse(int x,int y);    //“车”的分析引擎
    bool do_cannon_analyse(int x,int y);    //“炮”的分析引擎
    bool do_soldier_analyse(int x,int y);   //“兵”的分析引擎

signals:
    void need_update();
    void need_send_backdata();

public slots:
    chessboard::ACT_TYPE judge_action(int x,int y);//动作判断的slot，返回动作类型

};




#endif // CHESS_H
