#ifndef _threadevent_h_
#define _threadevent_h_
#include "absevent.h"

class ThreadEvent : public BasEvent
{
public:
	enum ThreadEventType{
		ThreadEvent_null,
		ThreadEvent_start,
        ThreadEvent_startcompleted,
		ThreadEvent_startfailed,
        ThreadEvent_end,
        ThreadEvent_exceptionend
	};
	ThreadEvent();
	ThreadEvent(ThreadEventType childtype);
	~ThreadEvent();
	int childType();
	void setChildType(ThreadEventType type) { m_childType = type;}
protected:
	ThreadEventType m_childType;
};
#endif
