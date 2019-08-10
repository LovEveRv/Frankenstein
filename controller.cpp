#include "controller.h"

Messager msg;

void Messager::print_percentage(int percentage)
{
    if(percentage == former_percentage) return;
    if(former_percentage != -1) (*os) << "\b\b\b\b"; 
    (*os) << std::setw(3) << percentage << '%';
    os->flush();
    former_percentage = percentage;
}