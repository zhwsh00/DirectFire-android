#include "uistatus.h"
#include "uistatusenum.h"

UiStatusMgr *UiStatusMgr::m_instance = 0;
UiStatusMgr::UiStatusMgr()
{

}
UiStatusMgr::~UiStatusMgr()
{

}
UiStatusMgr *UiStatusMgr::getInstance()
{
    if(m_instance == 0)
        m_instance = new UiStatusMgr;
    return m_instance;
}
void UiStatusMgr::pushUiStatus(int status)
{
    m_statusVector.push_back(status);
}
int UiStatusMgr::frontUiStatus()
{
    if(m_statusVector.size() > 0){
        return m_statusVector[m_statusVector.size() - 1];
    }else{
        return UiStatusEnum::UiSt_null;
    }
}
void UiStatusMgr::popUiStatus()
{
    m_statusVector.pop_back();
}
