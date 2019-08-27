#include "result.h"
#include "ui_result.h"

Result::Result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
}

void Result::showre(QString str)
{
    ui->label->setText(str);
}

Result::~Result()
{
    delete ui;
}

void Result::on_pushButton_2_clicked()
{
    emit endgame();
}

void Result::on_pushButton_clicked()
{
    emit regame();
}
