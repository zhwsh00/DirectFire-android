#ifndef _uistatus_h_
#define _uistatus_h_
#include <string>
#include <vector>
using namespace std;

class UiStatusMgr
{
    static UiStatusMgr *m_instance;
    UiStatusMgr();
    ~UiStatusMgr();
public:
    static UiStatusMgr *getInstance();
    void pushUiStatus(int status);
    int frontUiStatus();
    void popUiStatus();
protected:
    std::vector<int> m_statusVector;
};

#endif
