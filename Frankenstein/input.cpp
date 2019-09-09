#include "input.h"

Datapack_Imagelist* Input_Module::init(const std::string& filepath)
{
    delete imgList;
    imgList = new Datapack_Imagelist;
    std::ifstream fin(filepath.c_str());
    
}