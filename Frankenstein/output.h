#ifndef OUTPUT_H_
#define OUTPUT_H_
#include "modules.h"
#include <QImage>

class Output_Module
{
private:
    Datapack_Matchinfo* matchInfo;
    Datapack_Imagelist* imgList;
    std::string srcdir_path;
    std::string save_path;
public:
    Output_Module(Datapack_Matchinfo* m_matchInfo, Datapack_Imagelist* m_imgList, const std::string& m_dirpath, const std::string& save_path);
    void execute();
};

#endif
