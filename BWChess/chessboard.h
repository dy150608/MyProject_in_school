#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

namespace Ui {
class Chessboard;
}

class Chessboard : public QWidget
{
    Q_OBJECT

public:
    explicit Chessboard(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void page_updating(void*);
    ~Chessboard();

    int (*board)[8];
signals:
    void send_locale(int, int);

private:
    Ui::Chessboard *ui;
};

#endif // CHESSBOARD_H
