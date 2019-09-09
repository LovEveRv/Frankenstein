#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <queue>
#include <utility>
#include <algorithm>
#include "point.h"

class Datapack_Imagelist //Datapack, from INPUT module to PREPROCESSING module
{
public:
    std::map<int, std::string> Img_Index;
    Datapack_Imagelist() = default;
};

class Datapack_Imageinfo //Datapack, from PREPROCESSING module to CORE_PROCESSING module
{
public:
    std::vector<Element> Resource_Image_Info;
    std::vector<std::vector<Element>> Target_Image_Info;
    Datapack_Imageinfo() = default;
};

class Datapack_Matchinfo //Datapack, from CORE_PROCESSING module to OUTPUT module
{
public:
    std::vector<std::vector<int>> Match_Info;
    Datapack_Matchinfo() = default;
};

class Settings //Recording client settings
{
public:
    static int ALLOWED_WIDTH;
    static int ALLOWED_HEIGHT;
    static int PROCESSING_WIDTH;
    static int PROCESSING_HEIGHT;

    enum AlignType {ALIGN_LEFT_TOP, ALIGN_CENTER, ALIGN_RIGHT_BOTTOM};
    static AlignType ALIGN;

    static int VAGUE_ARG;
    enum Quality {MAXIMUM, SUITABLE, MINIMUM};
    static Quality OUTPUT_QUALITY;
};

class Messager //Showing messages to create an interface
{
private:
    int former_percentage;
public:
    void reset_percentage() {former_percentage = -1;}
    void show_percentage(int percentage); //print to screen
};
extern Messager msg;

#endif /* CONTROLLER_H_ */

/* Developed by LovEveRv, 2019. All rights reserved. */