#ifndef RESULT_H
#define RESULT_H

#include <QWidget>
#include <QString>

namespace Ui {
class Result;
}

class Result : public QWidget
{
    Q_OBJECT

public:
    explicit Result(QWidget *parent = 0);
    ~Result();

public slots:
    void showre(QString);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

signals:
    void regame();
    void endgame();

private:
    Ui::Result *ui;
};

#endif // RESULT_H
