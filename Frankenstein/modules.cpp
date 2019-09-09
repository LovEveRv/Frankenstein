#include "modules.h"

Messager msg;
int Settings::ALLOWED_WIDTH;
int Settings::ALLOWED_HEIGHT;
int Settings::PROCESSING_WIDTH;
int Settings::PROCESSING_HEIGHT;
Settings::AlignType ALIGN;
int Settings::VAGUE_ARG;
Settings::Quality OUTPUT_QUALITY;

void Messager::show_percentage(int percentage)
{
    if(percentage == former_percentage) return;
    // remain working
    former_percentage = percentage;
}