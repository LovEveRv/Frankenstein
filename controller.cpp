#include "controller.h"

Messager msg;
void Messager::print_percentage(int percentage)
{
    if(percentage == former_percentage) return;
    if(former_percentage != -1) std::cout << "\b\b\b\b"; 
    std::cout << std::setw(3) << percentage << '%';
    std::cout.flush();
    former_percentage = percentage;
}