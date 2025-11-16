#include "friendbox.h"
#include "ui_friendbox.h"

friendBox::friendBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendBox)
{
    ui->setupUi(this);
}

friendBox::~friendBox()
{
    delete ui;
}
