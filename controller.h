#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <queue>
#include <utility>
#include <algorithm>
#include "point.h"

class Datapack_Imagelist //Datapack, from INPUT module to PREPROCESSING module
{

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

class Main_Controller //Controlling the whole procedure
{
public:
    void init();
    void execute();
};

class Messager //Showing messages to create an interface
{
private:
    std::ostream* os;
    int former_percentage;
public:
    Messager(): os(&std::cout), former_percentage(-1) {}
    void print_info(const std::string& str) {(*os) << str;}
    void reset_percentage() {former_percentage = -1;}
    void print_percentage(int percentage);
};
extern Messager msg;

class Settings //Recording client settings
{

};

#endif /* CONTROLLER_H_ */

/* Developed by LovEveRv, 2019. All rights reserved. */