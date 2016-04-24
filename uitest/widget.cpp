#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPixmap pixMap(QString::fromUtf8("../boardres.png"));
    //QPixmap bord = pixMap.copy(730, 763, 60, 40); // lie1
    //QPixmap bord = pixMap.copy(795, 788, 40, 40); // lie2
    // Black Pao 1 Pos
    QPixmap bord = pixMap.copy(816, 262, 60, 42); // lie3
    // get rect
    //QPixmap bord = pixMap.copy(598, 602, 81, 81); // lie3
    ui->label->setPixmap(bord);
    bord.save("/home/zmm/works/Test/syberos-chess/images/red_ma1.png");
}

Widget::~Widget()
{
    delete ui;
}
