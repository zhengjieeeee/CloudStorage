#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "widget.h"

enum class CurrentTab{
    CMD,
    Transmission,
    Message,
    AI,
    Setting
};

class Controller
{
public:
    Controller();
    ~Controller();

    void show() { widget_ -> show(); }
    static CurrentTab getCurrentTab() { return currentTab_; }

private:
    Widget* widget_;

    static CurrentTab currentTab_;
};

#endif // CONTROLLER_H
