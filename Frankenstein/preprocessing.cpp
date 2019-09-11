#include "preprocessing.h"
#include <fstream>
#include <cmath>
#ifdef USING_QT
#include <QImage>
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
    msg->print_info("    Processing resource images.");
    msg->reset_percentage();
    bool reprocess = true;
    std::ifstream fin((srcdir_path + "/resource_info").c_str());
    if(fin.is_open())
    {
        int processing_width, processing_height;
        fin >> processing_width >> processing_height;
        if(processing_width == Settings::PROCESSING_WIDTH && processing_height == Settings::PROCESSING_HEIGHT)
        {
            std::string align;
            fin >> align;
            Settings::AlignType aligntype = Settings::ALIGN;
            if((align=="left_top"&&aligntype==Settings::ALIGN_LEFT_TOP) || (align=="center"&&aligntype==Settings::ALIGN_CENTER) || (align=="right_bottom"&&aligntype==Settings::ALIGN_RIGHT_BOTTOM))
            {
                Element ele(4);
                while(fin >> ele[0] >> ele[1] >> ele[2] >> ele[3])
                    imgInfo->Resource_Image_Info.push_back(ele);
                reprocess = false;
                msg->show_percentage(100);
            }
        }

    }
    if(reprocess)
    {
        for(int i=0; i<max_Index; i++)
        {
            msg->show_percentage(i * 100 / (max_Index-1));
            img.load(QString::fromStdString(srcdir_path + '/' + imgList->Img_Index[i]));
            if(img.isNull())
            {
                Element ele(3);
                ele[0] = Settings::SAFE_ERROR_NUMBER;
                ele[1] = Settings::SAFE_ERROR_NUMBER;
                ele[2] = Settings::SAFE_ERROR_NUMBER;
                imgInfo->Resource_Image_Info.push_back(ele);
                continue; //This will never be selected
            }
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
            Element ele(4);
            R /= total;
            G /= total;
            B /= total;
            ele[0] = R;
            ele[1] = G;
            ele[2] = B;
            int loss = 0;
            for(int i=0; i<width; i++)
                for(int j=0; j<height; j++)
                {
                    rgb = img.pixelColor(i, j);
                    loss += (std::abs(rgb.red()-R) + std::abs(rgb.green()-G) + std::abs(rgb.blue()-B)) / 3;
                }
            loss /= total;
            loss /= Settings::LOSS_DIVISION;
            ele[3] = loss;
            imgInfo->Resource_Image_Info.push_back(ele);
        }
        std::ofstream fout((srcdir_path + "/resource_info").c_str());
        fout << Settings::PROCESSING_WIDTH << ' ' << Settings::PROCESSING_HEIGHT << '\n';
        switch(Settings::ALIGN)
        {
        case Settings::ALIGN_LEFT_TOP:
            fout << "left_top\n";
            break;
        case Settings::ALIGN_CENTER:
            fout << "center\n";
            break;
        case Settings::ALIGN_RIGHT_BOTTOM:
            fout << "right_bottom\n";
            break;
        }
        for(size_t i=0; i<imgInfo->Resource_Image_Info.size(); i++)
        {
            for(int j=0; j<4; j++)
                fout << imgInfo->Resource_Image_Info[i][j] << ' ';
            fout << '\n';
        }
        fout.close();
    }
    fin.close();

    //Processing Target_Image_Info
    msg->print_info("    Processing target image.");
    msg->reset_percentage();
    img.load(QString::fromStdString(target_path));
    int width = img.width();
    int height = img.height();
    Settings::TARGET_WIDTH = width;
    Settings::TARGET_HEIGHT = height;
    int widnum = Settings::BLOCKS_PER_ROW;
    int s_width = width / widnum;
    int s_height = std::floor(double(s_width)/Settings::PROCESSING_WIDTH*Settings::PROCESSING_HEIGHT + 0.5);
    int heinum = height / s_height;
    int total = s_width * s_height;
    for(int i=0; i<widnum; i++)
    {
        std::vector<Element> tmp;
        for(int j=0; j<heinum;j++)
        {
            msg->show_percentage((i*heinum+j)/(widnum*heinum-1));
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
            Element ele(4);
            ele[0] = R / total;
            ele[1] = G / total;
            ele[2] = B / total;
            ele[3] = 0;
            tmp.push_back(ele);
        }
        imgInfo->Target_Image_Info.push_back(tmp);
    }

    return imgInfo;
}
