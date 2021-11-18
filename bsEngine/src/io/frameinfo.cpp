//
// Created by bigsmarty on 11/16/21.
//

#include <main.h>
#include "../base_engine/vk_engine.h"

using namespace std;

FrameData& bsEngine::getCurrentFrame()
{
    return oFrameData[frameNumber % FRAME_OVERLAP];
}