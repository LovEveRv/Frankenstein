#include "controller.h"

Messager msg;

void Messager::print_percentage(int percentage)
{
    if(former_percentage == -1)
    {
        (*os) << "  0%";
        os->flush();
        former_percentage = 0;
    }
    else
    {
        if(percentage == former_percentage) return;
        (*os) << "\b\b\b\b" << std::setw(3) << percentage << '%';
        os->flush();
        former_percentage = percentage;
    }
}