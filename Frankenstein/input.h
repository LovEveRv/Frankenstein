#include <fstream>
#include "modules.h"

class Input_Module
{
private:
    Datapack_Imagelist* imgList;
public:
    Input_Module(): imgList(nullptr) {}
    ~Input_Module() {delete imgList;}
    Datapack_Imagelist* init(const std::string& filepath);
};