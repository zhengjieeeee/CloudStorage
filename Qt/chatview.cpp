#include "chatview.h"
#include "ui_chatview.h"

chatView::chatView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatView)
{
    ui->setupUi(this);
}

chatView::~chatView()
{
    delete ui;
}
