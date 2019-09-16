#ifndef PROBAR_H
#define PROBAR_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class Probar;
}

class Probar : public QWidget
{
    Q_OBJECT
    
public:
    explicit Probar(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);
    ~Probar();
    Ui::Probar *ui;

public slots:

signals:
    void send_percent(int);
};

#endif // PROBAR_H
