#include "widget.h"
#include "chatview.h"
#include "controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;
    controller.show();

    //chatView c;
    //c.show();

    return a.exec();
}
