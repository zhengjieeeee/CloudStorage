#include "widget.h"
#include "chatview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    //chatView c;
    //c.show();

    return a.exec();
}
