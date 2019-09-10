#include "preprocessing.h"
#include <cmath>
#include <QImage>
#ifdef USING_QT
#include "messager.h"
#endif

Pre_Process_Module::Pre_Process_Module(Datapack_Imagelist *m_datapack, const std::string &m_dirpath, const std::string &m_targetpath) :
    imgList(m_datapack),
    imgInfo(nullptr),
    srcdir_path(m_dirpath),
    target_path(m_targetpath)
{

}

Datapack_Imageinfo *Pre_Process_Module::execute()
{
    delete imgInfo;
    imgInfo = new Datapack_Imageinfo;
    int max_Index = imgList->Img_Index.size();
    QImage img;

    //Processing Resource_Image_Info
    msg.print_info("    Processing resource images.");
    msg.reset_percentage();
    for(int i=0; i<max_Index; i++)
    {
        img.load(QString::fromStdString(srcdir_path + imgList->Img_Index[i]));
        int width = img.width();
        int height = img.height();
        int ori_x, ori_y;
        switch(Settings::ALIGN)
        {
        case Settings::ALIGN_LEFT_TOP:
            ori_x = 0;
            ori_y = 0;
            break;
        case Settings::ALIGN_CENTER:
            ori_x = (width-Settings::PROCESSING_WIDTH) / 2;
            ori_y = (height-Settings::PROCESSING_HEIGHT) / 2;
            break;
        case Settings::ALIGN_RIGHT_BOTTOM:
            ori_x = width-Settings::PROCESSING_WIDTH;
            ori_y = height-Settings::PROCESSING_HEIGHT;
            break;
        }
        QColor rgb;
        int R = 0, G = 0, B = 0;
        for(int i=0; i<Settings::PROCESSING_WIDTH; i++)
            for(int j=0; j<Settings::PROCESSING_HEIGHT; j++)
            {
                rgb = img.pixelColor(i+ori_x, j+ori_y);
                R += rgb.red();
                G += rgb.green();
                B += rgb.blue();
            }
        int total = Settings::PROCESSING_WIDTH * Settings::PROCESSING_HEIGHT;
        Element ele(3);
        ele[0] = R / total;
        ele[1] = G / total;
        ele[2] = B / total;
        imgInfo->Resource_Image_Info.push_back(ele);
        msg.show_percentage(i / (max_Index-1));
    }

    //Processing Target_Image_Info
    msg.print_info("    Processing target image.");
    msg.reset_percentage();
    img.load(QString::fromStdString(target_path));
    int width = img.width();
    int height = img.height();
    int widnum = std::floor(double((1-width)/100)*Settings::VAGUE_ARG+width + 0.5);
    int s_width = width / widnum;
    int s_height = std::floor(double(s_width/Settings::PROCESSING_WIDTH*Settings::PROCESSING_HEIGHT) + 0.5);
    int heinum = height / s_height;
    int total = s_width * s_height;
    for(int i=0; i<widnum; i++)
    {
        std::vector<Element> tmp;
        for(int j=0; j<heinum;j++)
        {
            QColor rgb;
            int R = 0, G = 0, B = 0;
            for(int x=0; x<s_width; x++)
                for(int y=0; y<s_height; y++)
                {
                    rgb = img.pixelColor(i*s_width+x, j*s_height+y);
                    R += rgb.red();
                    G += rgb.green();
                    B += rgb.blue();
                }
            Element ele(3);
            ele[0] = R / total;
            ele[1] = G / total;
            ele[2] = B / total;
            tmp.push_back(ele);
            msg.show_percentage((i*widnum+j)/(widnum*heinum-1));
        }
        imgInfo->Target_Image_Info.push_back(tmp);
    }

    return imgInfo;
}
