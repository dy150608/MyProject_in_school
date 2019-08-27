#ifndef PLAYPAGE_H
#define PLAYPAGE_H

#include <QWidget>
#include <QTimer>
#include <QPaintEvent>
#include <QString>
#include "chessboard.h"
#include "result.h"

#define PVE 1
#define PVP 2
#define BLACK 3
#define WHITE 4
#define EMPTY 0

namespace Ui {
class playpage;
}

void _copy(int[][8], int[][8]);

class playpage : public QWidget
{
    Q_OBJECT

public:
    friend class Result;
    explicit playpage(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    ~playpage();

    // 3->black, 0->null, 4->white
    int board[8][8];
    int turn[2] = {BLACK, WHITE};
    int mode;
    int role;
    bool start = false;
    bool mecjud = false;
    int x, y;
    int seconds = 30;

    void refresh();
    void reset_board(int[8][8]);
    // to judge is chess board full?
    bool end();
    // to judge is this step leagel?
    bool judge(int _per, int _x, int _y);
    // this step you eat how many?
    int a_step(int _per, int _x, int _y);
    // it's turn of mechine
    void mechine(int _per);
    // you win?
    int final();

public slots:
    void location(int, int);

signals:
    void page_update(void*);
    void result(QString);
    void Regame();
private:
    Ui::playpage *ui;
    QTimer *time = new QTimer;
    Chessboard *chess = new Chessboard;
    Result *res = new Result;
};

#endif // PLAYPAGE_H
