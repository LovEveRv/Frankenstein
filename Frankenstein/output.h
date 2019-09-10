#ifndef OUTPUT_H_
#define OUTPUT_H_
#include "modules.h"
#include <QImage>

class Output_Module
{
private:
    Datapack_Matchinfo* matchInfo;
    Datapack_Imagelist* imgList;
public:
    Output_Module(Datapack_Matchinfo* m_matchInfo, Datapack_Imagelist* m_imgList) : matchInfo(m_matchInfo), imgList(m_imgList) {}
    QImage execute();
};

#endif
