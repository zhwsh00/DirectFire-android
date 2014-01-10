#ifndef _absthrad_h_
#define _absthrad_h_
#include <vector>
using namespace std;
#include <pthread.h>

#include "listener/abslistener.h"
#include "listener/absevent.h"
// abstract for thread

template<typename TYPE,void (TYPE::*RunThread)()>
void *thread_t(void *param)
{
	TYPE *m_obj = (TYPE*)param;
	(m_obj->*RunThread)();
	return 0;
}
class BasThread
{
public:
	BasThread();
	virtual ~BasThread();
	virtual void start();
	virtual void finish();
	virtual void run() = 0;
	bool registerListener(int id,int type,int level,BasListener *listener);
	void unregisterListener(BasListener *listener);
    void broadEvent(BasEvent::EventType type,BasEvent::EventDetailLevel level,BasEvent *event,void *sender=0);
protected:
	std::vector<ListenerDefine *> m_listener;
protected:
	pthread_t m_pid;
};

#endif
