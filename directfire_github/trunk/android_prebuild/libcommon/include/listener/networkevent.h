#ifndef _networkevent_h_
#define _networkevent_h_
#include "absevent.h"
class NetworkEvent : public BasEvent
{
public:
	NetworkEvent();
	NetworkEvent(int childtype);
	~NetworkEvent();
	int childType() { return (int)m_childType;}
	void setChildType(int type) {m_childType = type;}
protected:
	int m_childType;
};
#endif
