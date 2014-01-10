#ifndef _moveinaction_h_
#define _moveinaction_h_
#include "cocos2d.h"
using namespace cocos2d;

#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include "absnodeaction.h"

namespace uilib
{
class TouchNode;

class MoveInNodeAction : public BasNodeAction
{
public:
    MoveInNodeAction();
    virtual ~MoveInNodeAction();
    void doAction(const std::vector<TouchNode*> &nodes);
};

}
#endif
