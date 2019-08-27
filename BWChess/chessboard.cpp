#include "chessboard.h"
#include "playpage.h"
#include "ui_chessboard.h"
#include <iostream>
#include <QDebug>

Chessboard::Chessboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chessboard)
{
    ui->setupUi(this);
}

void Chessboard::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QTimer t;
    t.start(1500);
    p.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/bg2.jpg"));
    QPen pen;
    pen.setColor(QColor(0, 0, 0));
    pen.setWidth(1);
    p.setPen(pen);
    for(int i = 1; i <= 9; i ++)// 棋盘画线
    {
        p.drawLine(0, i*50, 400, i*50);
        p.drawLine(i*50, 0, i*50, 400);
    }
    for(int i = 0; i < 8; i ++)
        for(int j = 0; j < 8; j ++)
        {
            if(board[i][j] == BLACK)
                p.drawPixmap(i*50, j*50, 50, 50, QPixmap(":/image/black.png"));
            else if(board[i][j] == WHITE)
                p.drawPixmap(i*50, j*50, 50, 50, QPixmap(":/image/white.png"));
            else
                continue;
        }
}

void Chessboard::mousePressEvent(QMouseEvent *event)
{
    emit send_locale(event->x()/50, event->y()/50);
}

Chessboard::~Chessboard()
{
    delete ui;
}

void Chessboard::page_updating(void *_board)
{
    board = (int(*)[8])_board;
}
