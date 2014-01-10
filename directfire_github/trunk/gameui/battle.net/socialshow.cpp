#include "socialshow.h"
#include "propshow.h"

SocialPropShow::SocialPropShow()
{

}
SocialPropShow::~SocialPropShow()
{

}
void SocialPropShow::setProps(int id,int num)
{
    std::map<int,PropShow*>::iterator iter;
    iter = m_propShows.find(id);
    if(iter != m_propShows.end()){
        iter->second->setProp(id,num);
    }
}
void SocialPropShow::finish()
{
    HorizontalLayout *hlay;
    PropShow *propshow;

    hlay = new HorizontalLayout;
    hlay->setAlignChildsSize(true);
    hlay->setSpacing(10);
    propshow = new PropShow();
    propshow->setProp(PropDef::Props_Coin,0);
    hlay->addWidget(propshow);
    m_propShows.insert(std::make_pair(PropDef::Props_Coin,propshow));

    propshow = new PropShow();
    propshow->setProp(PropDef::Props_Gold,0);
    hlay->addWidget(propshow);
    m_propShows.insert(std::make_pair(PropDef::Props_Gold,propshow));

    setLayout(hlay);
}
