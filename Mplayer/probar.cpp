#include "probar.h"
#include "ui_probar.h"

Probar::Probar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Probar)
{
    ui->setupUi(this);
}

Probar::~Probar()
{
    delete ui;
}

void Probar::mousePressEvent(QMouseEvent *event)
{
    emit send_percent(event->x());
}
