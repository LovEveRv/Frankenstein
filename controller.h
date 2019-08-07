#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <queue>

class Datapack_Imagelist //Datapack, from INPUT module to PREPROCESSING module
{

};

class Datapack_Imageinfo //Datapack, from PREPROCESSING module to CORE_PROCESSING module
{
public:
    std::vector<std::vector<int> > Resource_Image_Info;
    std::vector<std::vector<std::vector<int> > > Target_Image_Info;
    Datapack_Imageinfo() = default;
};

class Datapack_Matchinfo //Datapack, from CORE_PROCESSING module to OUTPUT module
{
public:
    std::vector<std::vector<int> > Match_Info;
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

};

class Settings //Recording client settings
{

};

#endif /* CONTROLLER_H_ */

/* Developed by HarmoniaLeo & LovEveRv, 2019. All rights reserved. */