#ifndef CORE_PROCESSING_H_
#define CORE_PROCESSING_H_

#include "controller.h"

class Core_Process_Module
{
private:
    Datapack_Imageinfo* Input_Data;
    double dist_punish;
    int threshold;

    void Build_Graph(int opt = 0);
public:
    Core_Process_Module(Datapack_Imageinfo* m_datapack, double m_dist_punish, int m_threshold): Input_Data(m_datapack), dist_punish(m_dist_punish), threshold(m_threshold) {}
    ~Core_Process_Module() {delete Input_Data;}
    Datapack_Matchinfo* execute(int alg_selection);
};

#endif /* CORE_PROCESSING_H_ */

/* Developed by HarmoniaLeo & LovEveRv, 2019. All rights reserved. */