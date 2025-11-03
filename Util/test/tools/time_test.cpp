#include <iostream>
#include "../../tools/Time.h"

int main(){
    std::string time = Time::getTime();
    std::cout << time << std::endl;
    return 0;
}