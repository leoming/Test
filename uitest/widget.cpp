#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPixmap pixMap(QString::fromUtf8("../boardres.png"));
    QPixmap bord = pixMap.copy(0, 0, 720, 830);
    ui->label->setPixmap(bord);
    bord.save("../board.png");
}

Widget::~Widget()
{
    delete ui;
}
