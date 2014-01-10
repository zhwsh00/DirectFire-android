#ifndef _chatphrasedialog_h_
#define _chatphrasedialog_h_
#include "cocos2d.h"
using namespace cocos2d;
#include "../base/widget.h"

#include <string>
#include <vector>
using namespace std;

namespace uilib
{
class ChatPhraseDialog : public BorderWidget
{
public:
    ChatPhraseDialog(TouchNode *parent,const CCPoint &pos);
    virtual ~ChatPhraseDialog();
    void show();
    void hide();
    void getUserClickedPhrase(std::string &face);
    void setPhraseClickCB(CCNode *node,SEL_CallFuncND func);
protected:
    void touchPressEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchMoveEvent(CCTouch *pTouch, CCEvent *pEvent);
    void touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent);
protected:
    void init(int dummy=0);
    void onPhraseClicked(CCNode *node,void *data);
protected:
    CCNode *m_clickListener;
    SEL_CallFuncND m_clickFunc;
protected:
    CCPoint m_pos;
    CCSize m_size;
    int m_clickedIndex;
    std::vector<std::string> m_hasPhrases;
};
}
#endif
