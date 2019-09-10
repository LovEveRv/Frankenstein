#ifndef PREPROCESSING_H_
#define PREPROCESSING_H_
#include "modules.h"

class Pre_Process_Module
{
private:
    Datapack_Imagelist* imgList;
    Datapack_Imageinfo* imgInfo;
    std::string srcdir_path;
    std::string target_path;
public:
    Pre_Process_Module(Datapack_Imagelist* m_datapack, const std::string& m_dirpath, const std::string& m_targetpath);
    ~Pre_Process_Module() {delete imgInfo;}
    Datapack_Imageinfo* execute();
};

#endif
