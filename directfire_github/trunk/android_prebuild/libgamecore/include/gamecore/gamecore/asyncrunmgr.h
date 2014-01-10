#ifndef _asyncrunmgr_h_
#define _asyncrunmgr_h_

class AsyncRunMgr
{
public:
    enum AsyncRunStatus{
        Async_NoneRun,
        Async_NormalRun,
        Async_CatchRun,
        Async_WaitingRun
    };
    typedef struct AsyncRunTimeRecorder
    {
        long m_startTimeSec;
        long m_startTimeUSec;
        long m_catchStartTimeSec;
        long m_catchStartTimeUsec;
        long m_waitStartTimeSec;
        long m_waitStartTimeUSec;
        void recordStartTime();
        void logStartTime();
        void recordCatchTime();
        void logCatchTime();
        void recordWaitTime();
        void logWaitTime();
    }AsyncRunTimeRecorder;

    AsyncRunMgr();
    virtual ~AsyncRunMgr();
    void setRunInfo(float time,int frame);
    void resumeRunInfo();
    void setRunUsed(float time,int frame);
    virtual void clientFrameStep();
    void setPredictedDelay(float time);
    bool canRun() { return m_usedFrame < m_runFrame; }
    float runTime() { return m_runTime;}
    int runFrame() { return m_runFrame;}
    float usedTime() { return m_usedTime;}
    int usedFrame() { return m_usedFrame;}
    int totalRunFrame() { return m_totalRunFrame;}
    virtual void adjustNetworkDelayAfterCatch();
    virtual void adjustNetworkDelayAfterWaiting();
    virtual void runFinished();
    virtual void asyncSignalGot();
    virtual void runFastCatchToSync(int userIndex = -1);
    virtual void runFinishedWaitForSync(int userIndex = -1);
    virtual void waitFinishedRunForSync(int userIndex = -1);
    bool inNormalRun() { return m_asyncRunStatus == AsyncRunMgr::Async_NormalRun;}
    bool inCatchRun() { return m_asyncRunStatus == AsyncRunMgr::Async_CatchRun;}
    bool inWaitingRun() { return m_asyncRunStatus == AsyncRunMgr::Async_WaitingRun;}
    float predictedDelay() { return m_predictedDelay;}
protected:
    void setRunStatus(AsyncRunMgr::AsyncRunStatus status);
protected:
    float m_origRunTime;
    float m_origRunFrame;
    float m_origStepTime;
    float m_runTime;
    int m_runFrame;
    float m_usedTime;
    int m_usedFrame;
    float m_predictedDelay;
    float m_stepTime;
protected:
    AsyncRunStatus m_asyncRunStatus;
    AsyncRunTimeRecorder m_runTimeRecorder;
protected:
    int m_totalRunFrame;
};

#endif
