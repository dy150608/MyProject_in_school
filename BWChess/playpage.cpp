#include "playpage.h"
#include "chessboard.h"
#include "ui_playpage.h"
#include <QPen>
#include <iostream>
#include <Qpainter>
#include <QDebug>

void _copy(int dest[8][8], int sour[8][8])
{
    for(int i = 0; i < 8; i ++)
        for(int j = 0; j < 8; j ++)
            dest[i][j] = sour[i][j];
}

void playpage::reset_board(int arr[8][8])
{
    for(int i = 0; i < 8; i ++)
        for(int j = 0; j < 8; j ++)
            arr[i][j] = 0;
}

playpage::playpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playpage)
{
    ui->setupUi(this);
    res->hide();
    QString str;
    str = this->role == BLACK ? "黑棋" : "白棋";
    ui->label_2->setText(str);
    this->reset_board(board);
    board[3][3] = board[4][4] = 3;
    board[4][3] = board[3][4] = 4;

    connect(ui->widget, &Chessboard::send_locale, this, &playpage::location);
    connect(this, &playpage::result, this->res, &Result::showre);
    connect(this->res, &Result::regame, this, [&]()
    {
        emit Regame();
    });
    connect(this->res, &Result::endgame, this, [&]()
    {
        this->close();
    });
    time->start(900);
    connect(this->time, &QTimer::timeout, this, [&]()
    {
        if(this->seconds >= 0)
            this->seconds --;
        else
        {
            this->seconds = 30;
            //this->result("you lose.");
        }
        ui->lcdNumber->display(this->seconds);
    });
    connect(this, &playpage::page_update, ui->widget, &Chessboard::page_updating);
    emit page_update((void*)board);
}

void playpage::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/bg1.jpg"));
}

void playpage::location(int _x, int _y)
{
    QString str;
    if(this->end())
    {
        this->final() == BLACK ? str = "黑棋赢" : "白棋赢";
        emit result(str);
    }
    if(judge(this->role, _x, _y))// 判断这个坐标能否落点
    {
        // 人先下，机器后下
        this->x = _x;
        this->y = _y;

        this->a_step(this->role, this->x, this->y);
        emit page_update((void*)board);
        this->role == BLACK ? str = "白棋" : str = "黑棋";
        ui->label_2->setText(str);
        this->seconds = 30;
        if(this->end())
        {
            this->final() == BLACK ? str = "黑棋赢" : "白棋赢";
            emit result(str);
        }
        this->update();

        this->time->start(2000);
        this->mechine(this->turn[this->role%2]);
        emit page_update((void*)board);
        this->role == BLACK ? str = "黑棋" : str = "白棋";
        ui->label_2->setText(str);
        this->seconds = 30;
        if(this->end())
        {
            this->final() == BLACK ? str = "黑棋赢" : "白棋赢";
            ui->label_2->setText(str);
            emit result(str);
        }
        this->update();
    }
    else
        qDebug() << "illeagel input";
}

playpage::~playpage()
{
    delete ui;
}

bool playpage::end()
{
    int black = 0, white = 0;
    for(int i = 0; i < 8; i ++)
        for(int j = 0; j < 8; j ++)
            if(board[i][j] == BLACK)
                black ++;
            else if(board[i][j] == WHITE)
                white ++;
    if(black == 0 || white == 0)
        return true;
    if(black+white == 64)
        return true;
    return false;
}

bool playpage::judge(int _per, int _x, int _y)// _per->player
{
    for(int i = -1; i < 2; i ++)// 一共有8个方向，以落点为中心，所以循环判断
        for(int j = -1; j < 2; j ++)
        {
            if(i == 0 && j == 0) continue;
            int x = _x + i;// x, y是我们要判断的坐标，只要加上i，j的值，就是根据方向移动的点了
            int y = _y + j;
            bool can = false;
            while((x >= 0 && x < 8) && (y >= 0 && y < 8))
            {
                if(board[x][y] == EMPTY)// 坐标为空或颜色和棋手相同则说明此路不通
                    break;
                else if(board[x][y] == _per && can == false)
                    break;
                else if(board[x][y] == _per && can == true)// 当坐标颜色等于棋手并且中间有对手的棋子，说明找到了路
                    return can;// 有一条路就说明这个坐标能用
                else if(board[x][y] == this->turn[_per%2])// 坐标颜色等于对手，就继续移动坐标
                {
                    can = true;
                    x += i;
                    y += j;
                }
            }
        }
    return false;// 全部方向都跑完了就说明没路可走了
}

int playpage::a_step(int _per, int _x, int _y)
{
    int count = 0;
    if(this->mecjud == false)// 如果机器在判断落点，则不改变棋盘
        board[_x][_y] = _per;
    for(int i = -1; i < 2; i ++)
        for(int j = -1; j < 2; j ++)
        {
            if(i == 0 && j == 0)
                continue;
            int x = _x + i;
            int y = _y + j;
            bool can = false;
            /*
             * 这个算法思路挺简单的
             * 按照落点的八个方向遍历
             * 如果遍历方向上有可以吃的子
             * 就让指针往回走，并把子吃掉
             */
            while((x >= 0 && x < 8) && (y >= 0 && y < 8))
            {
                if(board[x][y] == EMPTY)
                    break;
                else if(board[x][y] == _per && can == false)
                    break;
                else if(board[x][y] == _per && can == true)
                {
                    x -= i;
                    y -= j;
                    while(x != _x || y != _y)// 回走，吃子
                    {
                        /*
                         * 那个什么……
                         * 人机对战时，用贪心算法找到合适的坐标
                         * 但找坐标时我只需要用到计数而不想改变棋盘
                         * 我以前没这么用过，不知道行不行得通
                         */
                        if(this->mecjud == false)
                            board[x][y] = _per;
                        count ++;
                        x -= i;
                        y -= j;
                    }
                    break;
                }
                else if(board[x][y] == this->turn[_per%2])// 按照目前的方向遍历
                {
                    can = true;
                    x += i;
                    y += j;
                }
            }
        }
    return count;
}

void playpage::mechine(int _per)
{
    this->mecjud = true;
    int x = 0, y = 0;
    int count = 0;
    for(int i = 0; i < 8; i ++)
        for(int j = 0; j < 8; j ++)
        {
            if(board[i][j] != EMPTY)
                continue;
            else if(judge(_per, i, j))// 先判断一下这个点能不能落子
            {
                int _count = a_step(_per, i, j);
                if(count < _count)// 找到吃子最多的点
                {
                    count = _count;
                    x = i;
                    y = j;
                }
            }
            else continue;
        }
    this->mecjud = false;
    a_step(_per, x, y);// 在能吃到最多的点落子
}

int playpage::final()
{
    int black = 0, white = 0;
    for(int i = 0; i < 8; i ++)
        for(int j = 0; j < 8; j ++)
            if(board[i][j] == BLACK)
                black ++;
            else if(board[i][j] == WHITE)
                white ++;
    return black > white ? BLACK : WHITE;// 谁占的格子多就是谁赢
}
