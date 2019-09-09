#include "modules.h"

Messager msg;
void Messager::show_percentage(int percentage)
{
    if(percentage == former_percentage) return;
    // remain working
    former_percentage = percentage;
}