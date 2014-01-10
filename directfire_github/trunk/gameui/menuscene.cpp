#include "menuscene.h"
#include "mainmenulayer.h"
#include "gamecore/serverinterface.h"

MenuScene::MenuScene()
{
    ServerInterface::getInstance();
}
MenuScene::~MenuScene()
{

}
bool MenuScene::init()
{
    bool ret = false;

    do {
        CC_BREAK_IF(!CCScene::init());
        this->addChild(MainMenuLayer::create());
        ret = true;
    } while (0);

    return ret;
}
