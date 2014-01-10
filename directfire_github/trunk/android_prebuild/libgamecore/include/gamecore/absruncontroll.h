#ifndef _absruncontroll_h_
#define _absruncontroll_h_
class BasRunControll
{
public:
    BasRunControll();
    virtual ~BasRunControll();
    void enableTimeControll(bool enable) { m_enableTimeControll = enable;}
    void setTimeDelayMSec(int msec) { m_timeDelayMsec = msec;}
    virtual bool canRun();
protected:
    bool m_enableTimeControll;
    long m_prevSec;
    long m_prevUSec;
    int m_timeDelayMsec;
};

#endif
