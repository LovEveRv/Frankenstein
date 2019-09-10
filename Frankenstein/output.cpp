#include "output.h"
#include <cmath>
#ifdef USING_QT
#include <QPainter>
#include "messager.h"
#endif

Output_Module::Output_Module(Datapack_Matchinfo *m_matchInfo, Datapack_Imagelist *m_imgList, const std::string &m_dirpath, const std::string& m_svpath) :
    matchInfo(m_matchInfo),
    imgList(m_imgList),
    srcdir_path(m_dirpath),
    save_path(m_svpath)
{

}

void Output_Module::execute()
{
    int widnum = matchInfo->Match_Info.size();
    int heinum = matchInfo->Match_Info[0].size();
    int width = widnum * Settings::PROCESSING_WIDTH;
    int height = heinum * Settings::PROCESSING_HEIGHT;
    QImage output(width, height, QImage::Format_RGB888);
    output.fill(Qt::white);
    QImage input;
    QPainter p(&output);
    msg->reset_percentage();
    for(int i=0; i<widnum; i++)
        for(int j=0; j<heinum; j++)
        {
            int index = matchInfo->Match_Info[i][j];
            if(index == -1) continue;
            input.load(QString::fromStdString(srcdir_path + '/' + imgList->Img_Index[index]));
            int ori_x, ori_y;
            switch(Settings::ALIGN)
            {
            case Settings::ALIGN_LEFT_TOP:
                ori_x = 0;
                ori_y = 0;
                break;
            case Settings::ALIGN_CENTER:
                ori_x = (input.width()-Settings::PROCESSING_WIDTH) / 2;
                ori_y = (input.height()-Settings::PROCESSING_HEIGHT) / 2;
                break;
            case Settings::ALIGN_RIGHT_BOTTOM:
                ori_x = input.width()-Settings::PROCESSING_WIDTH;
                ori_y = input.height()-Settings::PROCESSING_HEIGHT;
                break;
            }
            QImage img = input.copy(ori_x, ori_y, Settings::PROCESSING_WIDTH, Settings::PROCESSING_HEIGHT);
            p.drawImage(QRect(i*Settings::PROCESSING_WIDTH, j*Settings::PROCESSING_HEIGHT, Settings::PROCESSING_WIDTH, Settings::PROCESSING_HEIGHT), img);
            msg->show_percentage((i*heinum+j)*100/(widnum*heinum-1));
        }

    switch(Settings::OUTPUT_QUALITY)
    {
    case Settings::QUALITY_MAXIMUM:
        break;
    case Settings::QUALITY_MINIMUM:
        width = Settings::TARGET_WIDTH;
        break;
    case Settings::QUALITY_SUITABLE:
        width = 4096;
        break;
    }
    height = std::floor(double(width)/Settings::TARGET_WIDTH*Settings::TARGET_HEIGHT + 0.5);
    output.scaled(width, height).save(QString::fromStdString(save_path));
}
