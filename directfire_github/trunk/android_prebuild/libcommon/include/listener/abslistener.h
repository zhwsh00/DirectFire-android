#ifndef _abslistener_h_
#define _abslistener_h_
#include "absevent.h"
class BasListener
{
public:
	BasListener();
	virtual ~BasListener();
    virtual void notify(int id,BasEvent::EventType event_type,BasEvent *event,void *sender=0) = 0;
};
#endif
