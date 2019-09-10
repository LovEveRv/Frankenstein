#include "messager.h"

Messager msg;

void Messager::show_percentage(int percentage)
{
    if(percentage == former_percentage) return;
    emit percentage_changed(percentage);
    former_percentage = percentage;
}
