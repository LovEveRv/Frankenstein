#include "input.h"

Datapack_Imagelist* Input_Module::init(const std::string& filepath)
{
    std::ifstream fin(filepath.c_str());
    if(!fin.is_open()) return nullptr;
    delete imgList;
    imgList = new Datapack_Imagelist;
    int id;
    std::string img_name;
    while(fin >> id)
    {
        if(id == -1)
        {
            int width, height;
            fin >> width >> height;
            Settings::ALLOWED_WIDTH = width;
            Settings::ALLOWED_HEIGHT = height;
            break;
        }
        fin.get();
        std::getline(fin, img_name);
        imgList->Img_Index[id] = img_name;
    }
    fin.close();
    return imgList;
}