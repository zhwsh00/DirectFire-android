#ifndef _moveoutaction_h_
#define _moveoutaction_h_
using namespace std;
#include "absnodeaction.h"

namespace uilib
{
class TouchNode;

class MoveOutNodeAction : public BasNodeAction
{
public:
    MoveOutNodeAction();
    virtual ~MoveOutNodeAction();
    void doAction(const std::vector<TouchNode*> &nodes);
};

}
#endif
