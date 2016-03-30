#include"chessboard.h"

#include<QtGui>



chessboard::chessboard()
{
    init_chessmans();
    init_images();
   set_role_actived(chessman::RED_MAN);
   //  set_role_actived(chessman::GREEN_MAN);
    chessman_selected=NULL;
    chessman_last_moved=NULL;
    footprint_clear();
}

chessboard::~chessboard(){}

void chessboard::do_selected(int x,int y)
{
    qDebug()<<"do_selected";
    if(chessman_selected != NULL)
        chessman_selected->setimage_unselected();
    if(chessman_last_moved!=NULL)
        chessman_last_moved->setimage_unselected();
    chessman_selected = chess[y][x];
    chessman_selected->setimage_selected();
    footprint_clear();
    emit need_update();
}

chessboard::ACT_TYPE chessboard::judge_action(int x, int y)
{
    enum ACT_TYPE ret;
    if(chess[y][x]!= NULL)
    {
        if(chessman_selected==NULL)
        {
            if(chess[y][x]->role() != role_actived())
                ret= INVALID;
            else
                ret = SELECT;
        }
        else
        {
            if(chess[y][x]->role() != role_actived())
                ret = EAT;
            else
                ret = SELECT;
        }
    }
    else
    {
        if(chessman_selected ==NULL)
            ret = INVALID;
        else
            ret = MOVE;
    } 

    return ret;
}

void chessboard::action_in_chessboard(int x, int y)
{
    ACT_TYPE type;
    qDebug()<<"action_in_chessboard";
    if(chessman_last_moved!=NULL)
        chessman_last_moved->setimage_unselected();

    if(chessman_selected!=NULL)
    {
        qDebug()<<"chessman_selected != NULL";
        footprint.setX(chessman_selected->pos.x());
        footprint.setY(chessman_selected->pos.y());
    }

    qDebug()<<"==========="<<y<<" "<<x<<" "<<footprint_y()<<" "<<footprint_x();
    chess[footprint.y()][footprint.x()] = NULL;
    if(chess[y][x] != NULL)
    {
        type = EAT;
        qDebug()<<"chess[y][x] != NULL ";
        chess[y][x]->setdead(true);
        deadstack.push(chess[y][x]);

        if(chess[y][x]->name()==chessman::G_MARSHAL)
        {
            qDebug()<<(tr("redman win !"));

        }
        else if(chess[y][x]->name()==chessman::R_MARSHAL)
        {
            qDebug()<<(tr("greenman win !"));
        }
    }
    else
    {
        type = MOVE;
        qDebug()<<"chess[y][x]==NULL";
    }
    qDebug()<<"before chess[][]=chessman_selected";
    chess[y][x] = chessman_selected;
    chessman_selected->pos.setX(x);
    chessman_selected->pos.setY(y);
    chessman_selected->setimage_selected();
    qDebug()<<"after chessman_selected->...";
    chessman_last_moved = chessman_selected;
    chessman_selected=NULL;

    motion_stack.push( (struct motion_data){QLine(footprint.x(),footprint.y(),x,y), type});

    toggle_role_actived();
    emit need_update();
    qDebug()<<"end of action_in_chessboard";
    point_actived.setX(x);
    point_actived.setY(y);
}

void chessboard::back_in_chessboard()
{
    qDebug()<<"back_in_chessboard";
    if(motion_stack.isEmpty())
        return;
    struct motion_data data = motion_stack.pop();
    QLine motion = data.line;
    motion.x2();
    motion.y2();
    do_selected(motion.x2(),motion.y2());

    qDebug()<<" do_selected in back_in_chessboard";

    footprint.setX(chessman_selected->pos.x());
    footprint.setY(chessman_selected->pos.y());
    chess[footprint.y()][footprint.x()] = NULL;

    chess[motion.y1()][motion.x1()] = chessman_selected;
    chessman_selected->pos.setX(motion.x1());
    chessman_selected->pos.setY(motion.y1());
    chessman_selected->setimage_selected();
    chessman_last_moved = chessman_selected;

    if(!deadstack.isEmpty())
    {
        qDebug()<<"deadstack != NULL ";
        if(data.type==EAT)
        {
            qDebug()<<"data.type==EAT";
            if( ((chessman *)(deadstack.last()))->pos.x()==motion.x2()
                && ((chessman *)(deadstack.last()))->pos.y()==motion.y2() )
        {
            qDebug()<<"before deadstack.pop()";
            chess[motion.y2()][motion.x2()]=deadstack.pop();
            qDebug()<<"before setdead";
            chess[motion.y2()][motion.x2()]->setdead(false);
            qDebug()<<"after setdead";
            footprint_clear();
        }
        }
    }
    toggle_role_actived();
    qDebug()<<"before emit need_update()";
    emit need_update();
    qDebug()<<"end of back_in_chessboard";
}

bool chessboard::do_chessboard_analyse(int x, int y)
{
    if(chessman_selected == NULL)
        return false;
    switch(chessman_selected->name())
    {
            case chessman::G_MARSHAL :  return do_marshal_analyse(x,y);
            case chessman::G_SERGEANCY : return do_sergeancy_analyse(x,y);
            case chessman::G_ELEPHANT : return do_elephant_analyse(x,y);
            case chessman::G_HORSE : return do_horse_analyse(x,y);
            case chessman::G_GHARRY : return do_gharry_analyse(x,y);
            case chessman::G_CANNON : return do_cannon_analyse(x,y);
            case chessman::G_SOLDIER : return do_soldier_analyse(x,y);
            case chessman::R_MARSHAL : return do_marshal_analyse(x,y);
            case chessman::R_SERGEANCY : return do_sergeancy_analyse(x,y);
            case chessman::R_ELEPHANT : return do_elephant_analyse(x,y);
            case chessman::R_HORSE : return do_horse_analyse(x,y);
            case chessman::R_GHARRY : return do_gharry_analyse(x,y);
            case chessman::R_CANNON : return do_cannon_analyse(x,y);
            case chessman::R_SOLDIER : return do_soldier_analyse(x,y);
            default: return false;


    }
}

bool chessboard::init_images()
{
    boardimage.load(tr("images/badboard.jpg"));
    boximage.load(tr("images/box.jpg"));
    QImage * im = new QImage(tr("images/1_1.jpg"));
    int i,j;
    for(i=0;i<40;i++)
        for(j=0;j<40;j++)
            if((i-20)*(i-20)+(j-20)*(j-20) > 17*17-12)
                boximage.setAlphaChannel(boximage.createMaskFromColor(im->pixel(i,j),Qt::MaskOutColor));
    delete im;
    return true;
}

bool chessboard::init_chessmans()
{

    int i,j;
    for(i=0;i<10;i++)
        for(j=0;j<9;j++)
            chess[i][j]=NULL;

    chess[0][0] = new chessman(chessman::GREEN_MAN,chessman::G_GHARRY,tr("images/5_1.jpg"),tr("images/5_2.jpg"));
    chess[0][1] = new chessman(chessman::GREEN_MAN,chessman::G_HORSE,tr("images/4_1.jpg"),tr("images/4_2.jpg"));
    chess[0][2] = new chessman(chessman::GREEN_MAN,chessman::G_ELEPHANT,tr("images/3_1.jpg"),tr("images/3_2.jpg"));
    chess[0][3] = new chessman(chessman::GREEN_MAN,chessman::G_SERGEANCY,tr("images/2_1.jpg"),tr("images/2_2.jpg"));
    chess[0][4] = new chessman(chessman::GREEN_MAN,chessman::G_MARSHAL,tr("images/1_1.jpg"),tr("images/1_2.jpg"));
    chess[0][5] = new chessman(chessman::GREEN_MAN,chessman::G_SERGEANCY,tr("images/2_1.jpg"),tr("images/2_2.jpg"));
    chess[0][6] = new chessman(chessman::GREEN_MAN,chessman::G_ELEPHANT,tr("images/3_1.jpg"),tr("images/3_2.jpg"));
    chess[0][7] = new chessman(chessman::GREEN_MAN,chessman::G_HORSE,tr("images/4_1.jpg"),tr("images/4_2.jpg"));
    chess[0][8] = new chessman(chessman::GREEN_MAN,chessman::G_GHARRY,tr("images/5_1.jpg"),tr("images/5_2.jpg"));
    chess[2][1] = new chessman(chessman::GREEN_MAN,chessman::G_CANNON,tr("images/6_1.jpg"),tr("images/6_2.jpg"));
    chess[2][7] = new chessman(chessman::GREEN_MAN,chessman::G_CANNON,tr("images/6_1.jpg"),tr("images/6_2.jpg"));
    chess[3][0] = new chessman(chessman::GREEN_MAN,chessman::G_SOLDIER,tr("images/7_1.jpg"),tr("images/7_2.jpg"));
    chess[3][2] = new chessman(chessman::GREEN_MAN,chessman::G_SOLDIER,tr("images/7_1.jpg"),tr("images/7_2.jpg"));
    chess[3][4] = new chessman(chessman::GREEN_MAN,chessman::G_SOLDIER,tr("images/7_1.jpg"),tr("images/7_2.jpg"));
    chess[3][6] = new chessman(chessman::GREEN_MAN,chessman::G_SOLDIER,tr("images/7_1.jpg"),tr("images/7_2.jpg"));
    chess[3][8] = new chessman(chessman::GREEN_MAN,chessman::G_SOLDIER,tr("images/7_1.jpg"),tr("images/7_2.jpg"));


    chess[9][0] = new chessman(chessman::RED_MAN,chessman::R_GHARRY,tr("images/12_1.jpg"),tr("images/12_2.jpg"));
    chess[9][1] = new chessman(chessman::RED_MAN,chessman::R_HORSE,tr("images/11_1.jpg"),tr("images/11_2.jpg"));
    chess[9][2] = new chessman(chessman::RED_MAN,chessman::R_ELEPHANT,tr("images/10_1.jpg"),tr("images/10_2.jpg"));
    chess[9][3] = new chessman(chessman::RED_MAN,chessman::R_SERGEANCY,tr("images/9_1.jpg"),tr("images/9_2.jpg"));
    chess[9][4] = new chessman(chessman::RED_MAN,chessman::R_MARSHAL,tr("images/8_1.jpg"),tr("images/8_2.jpg"));
    chess[9][5] = new chessman(chessman::RED_MAN,chessman::R_SERGEANCY,tr("images/9_1.jpg"),tr("images/9_2.jpg"));
    chess[9][6] = new chessman(chessman::RED_MAN,chessman::R_ELEPHANT,tr("images/10_1.jpg"),tr("images/10_2.jpg"));
    chess[9][7] = new chessman(chessman::RED_MAN,chessman::R_HORSE,tr("images/11_1.jpg"),tr("images/11_2.jpg"));
    chess[9][8] = new chessman(chessman::RED_MAN,chessman::R_GHARRY,tr("images/12_1.jpg"),tr("images/12_2.jpg"));
    chess[7][1] = new chessman(chessman::RED_MAN,chessman::R_CANNON,tr("images/13_1.jpg"),tr("images/13_2.jpg"));
    chess[7][7] = new chessman(chessman::RED_MAN,chessman::R_CANNON,tr("images/13_1.jpg"),tr("images/13_2.jpg"));
    chess[6][0] = new chessman(chessman::RED_MAN,chessman::R_SOLDIER,tr("images/14_1.jpg"),tr("images/14_2.jpg"));
    chess[6][2] = new chessman(chessman::RED_MAN,chessman::R_SOLDIER,tr("images/14_1.jpg"),tr("images/14_2.jpg"));
    chess[6][4] = new chessman(chessman::RED_MAN,chessman::R_SOLDIER,tr("images/14_1.jpg"),tr("images/14_2.jpg"));
    chess[6][6] = new chessman(chessman::RED_MAN,chessman::R_SOLDIER,tr("images/14_1.jpg"),tr("images/14_2.jpg"));
    chess[6][8] = new chessman(chessman::RED_MAN,chessman::R_SOLDIER,tr("images/14_1.jpg"),tr("images/14_2.jpg"));

    for(i=0;i<10;i++)
        for(j=0;j<9;j++)
            if( chess[i][j]!=NULL )
            {
                chess[i][j]->pos.setX(j);
                chess[i][j]->pos.setY(i);
                hash_chessman.insert(chess[i][j]->name(),chess[i][j]);
            }
    return true;
}

bool chessboard::do_marshal_analyse(int x,int y)
{
    if( !(x>2 && x < 6) )
        return false;
    if( chessman_selected->role()== chessman::GREEN_MAN && y>2)
        return false;
    if( chessman_selected->role()== chessman::RED_MAN && y<7 )
        return false;

    int dx = x-chessman_selected->pos.x();
    int dy = y-chessman_selected->pos.y();
    if(dx * dy !=0 || dx >1 || dx < -1 || dy > 1 || dy < -1)
        return false;
    return true;
}

bool chessboard::do_sergeancy_analyse(int x,int y)
{
    if( !(x>2 && x < 6) )
        return false;
    if( chessman_selected->role()== chessman::GREEN_MAN && y>2)
        return false;
    if( chessman_selected->role()== chessman::RED_MAN && y<7 )
        return false;
    int dx = x-chessman_selected->pos.x();
    int dy = y-chessman_selected->pos.y();
    if(dx==0 ||dy==0 || dx >1 || dx < -1 || dy > 1 || dy < -1)
        return false;
    return true;
}

bool chessboard::do_elephant_analyse(int x,int y)
{
    int dx = x-chessman_selected->pos.x();
    int dy = y-chessman_selected->pos.y();
    if(!( ((dx==2)||(dx==-2)) && ((dy==2)||(dy==-2)) ) )
        return false;
    if( (y<5 && chessman_selected->role()==chessman::RED_MAN) ||
            (y>4 && chessman_selected->role()==chessman::GREEN_MAN) )
        return false;
    if( chess[(y+chessman_selected->pos.y())/2][(x+chessman_selected->pos.x())/2]!=NULL )
       return false;

    return true;
}

bool chessboard::do_horse_analyse(int x,int y)
{
    int dx = x-chessman_selected->pos.x();
    int dy = y-chessman_selected->pos.y();
    if( !( dx*dy==2||dx*dy==-2) )
        return false;

    if(chess[chessman_selected->pos.y()+dy/2][chessman_selected->pos.x()+dx/2]!=NULL)
        return false;
    return true;
}

bool chessboard::do_gharry_analyse(int x,int y)
{
    int dx = x-chessman_selected->pos.x();
    int dy = y-chessman_selected->pos.y();
    if( dx!=0&&dy!= 0)
        return false;
    int i;
    if(dx==0)
    {
        int min = qMin(chessman_selected->pos.y(),y);
        int max = qMax(chessman_selected->pos.y(),y);
        for(i=min+1;i<max;i++)
        {
            if(chess[i][x]!= NULL)
                return false;
        }
    }
    if(dy==0)
    {
        int min = qMin(chessman_selected->pos.x(),x);
        int max = qMax(chessman_selected->pos.x(),x);
        for(i=min+1;i<max;i++)
        {
            if(chess[y][i]!= NULL)
                return false;
        }
    }
    return true;
}

bool chessboard::do_cannon_analyse(int x,int y)
{

    if(chess[y][x]==NULL)
        return do_gharry_analyse(x,y);
    int dx = x-chessman_selected->pos.x();
    int dy = y-chessman_selected->pos.y();
    if( dx!=0&&dy!= 0)
        return false;
    int i;
    if(dx==0)
    {
        int count=0;
        int min = qMin(chessman_selected->pos.y(),y);
        int max = qMax(chessman_selected->pos.y(),y);
        for(i=min+1;i<max;i++)
        {
            if(chess[i][x]!= NULL)
                count++;
        }
        if(count!=1)
            return false;
    }
    if(dy==0)
    {
        int count=0;
        int min = qMin(chessman_selected->pos.x(),x);
        int max = qMax(chessman_selected->pos.x(),x);
        for(i=min+1;i<max;i++)
        {
            if(chess[y][i]!= NULL)
                count++;
        }
        if(count!=1)
            return false;
    }
    return true;
}

bool chessboard::do_soldier_analyse(int x,int y)
{
    int dx = x-chessman_selected->pos.x();
    int dy = y-chessman_selected->pos.y();
    if( dx!=0&&dy!= 0)
        return false;
    if(dx+dy != 1 &&dx+dy !=-1)
        return false;

    if(chessman_selected->role()==chessman::RED_MAN)
    {
        if(dy>0)
            return false;
        if(chessman_selected->pos.y()>4 && dx!=0)
            return false;
    }
    if(chessman_selected->role()==chessman::GREEN_MAN)
    {
        if(dy<0)
            return false;
        if(chessman_selected->pos.y()<5 && dx!=0)
            return false;
    }
    return true;
}
