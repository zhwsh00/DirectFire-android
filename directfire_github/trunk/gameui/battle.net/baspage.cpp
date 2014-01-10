#include "baspage.h"

BasPage::BasPage(BasWidget *container)
{
    if(container)
        container->addChild(this);
    this->setFill("parent");
}
BasPage::~BasPage()
{

}
void BasPage::setContainer(BasWidget *container)
{
    if(container)
        container->addChild(this);
}
void BasPage::moveinPage()
{

}
void BasPage::moveoutPage()
{

}
