#include"widget.h"
#include"chessboard.h"
#include<QtGui>


widget::widget(QWidget *parent):QWidget(parent)
{
    dxvalue=49;
    dyvalue=49;
    xbasevalue=12;
    ybasevalue=10;
    rect_valid.setRect(0,0,458,504);

    set_chess_start(false);
    set_vs_type(widget::INVALID);
    board = new chessboard;
    init_hash_pos();
    point_clicked.setX(-1);
    point_clicked.setY(-1);
    setFixedSize(458,504);
    set_roleplaying(chessman::RED_MAN);
    connect(board,SIGNAL(need_update()),this,SLOT(update()));
}

widget::~widget(){}

void widget::init_hash_pos()
{
    int i,j;
    for(i=0;i<10;i++)
        for(j=0;j<9;j++)
            hash_pos.insert(i*10+j, QRect(j*dx()+xbase(),i*dy()+ybase(),40,40));
}

void widget::mousePressEvent(QMouseEvent *event)
{
    if(is_chess_start()  )
    {
        if(!contains(event->pos().x(),event->pos().y()))
            return;
        int x,y;
        x = (event->pos().x()-xbase())/dx();
        y = (event->pos().y()-ybase())/dy();
        point_clicked.setX(x);
        point_clicked.setY(y);
        //网络对战
        if( is_net_vs() && board->role_actived()==roleplaying() )
        {

            chessboard::ACT_TYPE type_act = board->judge_action(x,y);
            if(type_act!=INVALID)
            {
                board->point_actived.setX(x);
                board->point_actived.setY(y);
            }
            board->last_action_type=type_act;
            switch(type_act){

            case chessboard::INVALID : qDebug()<<"INVALID return in judge_action";  return;

            case chessboard::SELECT :  board->do_selected(x,y); emit tell_rival_chessboard();
                qDebug()<<"emit tell_rival_chessboard(x, y) ";break;

            case chessboard::MOVE :
            case chessboard::EAT :  if( board->do_chessboard_analyse(x,y) )
                {
                     board->action_in_chessboard(x,y);
                     emit tell_rival_chessboard();
                     qDebug()<<"emit tell_rival_chessboard(x, y) ";
                } break;
            default : return ;
            }
            update();
        }
        //与电脑对战
        else if(is_computer_vs() && board->role_actived()==roleplaying())
        {
            int type_act = board->judge_action(x,y);
            switch(type_act){

            case chessboard::INVALID :qDebug()<<"INVALID return";  return;

            case chessboard::SELECT : qDebug()<<"*** mouse SELECT ***";board->do_selected(x,y);  break;

            case chessboard::MOVE : qDebug()<<"*** mouse MOVE ***";if(board->do_chessboard_analyse(x,y))
                    board->action_in_chessboard(x,y); break;

            case chessboard::EAT : qDebug()<<"*** mouse EAT ***";if(board->do_chessboard_analyse(x,y))
                    board->action_in_chessboard(x,y);  break;
            default : return;
            }
            update();
        }
        //自由对谱
        else if(is_free_vs())
        {
            int type_act = board->judge_action(x,y);
            switch(type_act){

            case chessboard::INVALID :qDebug()<<"INVALID return";  return;

            case chessboard::SELECT : board->do_selected(x,y);qDebug()<<"do_selected";  break;

            case chessboard::MOVE :

            case chessboard::EAT : if(board->do_chessboard_analyse(x,y))
                    board->action_in_chessboard(x,y); qDebug()<<"do_chessboard_analyse"; break;
            default : return;
            }
            update();
        }
    }   
}

void widget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    if(is_chess_start()==false)
        return;
    painter.drawImage(rect(),board->boardimage);
    int i,j;
    for(i=0;i<10;i++)
        for(j=0;j<9;j++)
            if(board->chess[i][j]!=NULL)
                painter.drawImage(hash_pos.value(i*10+j),*board->chess[i][j]->image_to_show);

    if(!board->footprint_isEmpty())
        painter.drawImage(hash_pos.value(( board->footprint_y() )*10+board->footprint_x()),board->boximage);
}
