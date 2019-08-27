#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    connect(&this->player, &playpage::Regame, this, [&]()
    {
        ui->stackedWidget->setCurrentIndex(0);
    });
    player.hide();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/bg1.jpg"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()
{
    this->close();
}

void Widget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_pushButton_3_clicked()
{
    mode = PVE;
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_7_clicked()
{
    this->close();
}

void Widget::on_pushButton_4_clicked()
{
    mode = PVP;
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_5_clicked()
{
    role = BLACK;
    start = true;
    this->hide();
    player.mode = this->mode;
    player.role = this->role;
    player.start = this->start;
    player.show();
}

void Widget::on_pushButton_6_clicked()
{
    role = WHITE;
    start = true;
    this->hide();
    player.mode = this->mode;
    player.role = this->role;
    player.start = this->start;
    player.show();
}
