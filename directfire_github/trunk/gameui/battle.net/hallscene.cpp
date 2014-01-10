#include "hallscene.h"
#include "halllayer.h"

HallScene::HallScene()
{

}
HallScene::~HallScene()
{

}
bool HallScene::init()
{
    bool ret = false;
    do {
        CC_BREAK_IF(!CCScene::init());
        this->addChild(HallLayer::create(),0);
        ret = true;
    } while (0);
    return ret;
}
