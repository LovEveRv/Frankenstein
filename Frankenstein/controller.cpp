#include "controller.h"
#include "input.h"
#include "preprocessing.h"
#include "core_processing.h"
#include "output.h"
#ifdef USING_QT
#include "messager.h"
#endif

void my_print_info(const std::string& info)
{
    #ifdef USING_QT
    msg->print_info(info);
    #endif
}

Main_Controller::Main_Controller(QObject *parent, const std::__1::string &m_dirpath, const std::__1::string &m_target, const std::__1::string &m_svpath) :
    QObject(parent),
    srcdir_path(m_dirpath),
    target_path(m_target),
    save_path(m_svpath)
{

}

void Main_Controller::execute()
{
    my_print_info("Loading image_index...");
        Input_Module input;
        Datapack_Imagelist *imgList = input.init(srcdir_path + "/image_index");
        if(imgList == nullptr)
        {
            my_print_info("Fatal: Fail to open image_index.");
            my_print_info("    Terminated.");
            emit finished();
            return;
        }
        else if(Settings::PROCESSING_WIDTH > Settings::ALLOWED_WIDTH || Settings::PROCESSING_HEIGHT > Settings::ALLOWED_HEIGHT)
        {
            my_print_info("Fatal: Resolution exceeds max-allowed resolution.");
            my_print_info("    Terminated.");
            emit finished();
            return;
        }
        my_print_info("Processing images...");
        Pre_Process_Module pre(imgList, srcdir_path, target_path);
        Datapack_Imageinfo *imgInfo = pre.execute();
        my_print_info("Matching images...");
        Core_Process_Module core(imgInfo, Settings::CORE_PROCESSING_DISTPUNISH, Settings::CORE_PROCESSING_THRESHOLD);
        Datapack_Matchinfo *matchInfo = core.execute(Settings::CORE_PROCESSING_ALGSELECT);
        my_print_info("Generating final image...");
        Output_Module output(matchInfo, imgList, srcdir_path, save_path);
        output.execute();
        my_print_info("Done!");
        emit finished();
        return;
}
