#include "controller.h"

Controller::Controller()
{
    widget_ = new Widget();
}

Controller::~Controller(){
    delete widget_;
}
