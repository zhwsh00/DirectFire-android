#ifndef _absevent_h_
#define _absevent_h_

class BasEvent
{
public:
	enum EventType{
		EventType_task = 1 << 0,
		EventType_process = 1 << 1,
		EventType_thread = 1 << 2,
		EventType_network = 1 << 3
	};
	enum EventDetailLevel{
		EventDetailLevel_all = 1 << 0,
		EventDetailLevel_level1 = 1 << 1,
		EventDetailLevel_level2 = 1 << 2
	};
public:
	BasEvent(EventType type);
	virtual ~BasEvent();
	EventType type() { return m_eventType;}
	virtual int childType() = 0;
protected:
	EventType m_eventType;
};

class BasListener;
typedef struct ListenerDefine{
	ListenerDefine() { m_id = m_eventType = m_level = 0;m_listener=0;}
	int m_id;
	int m_eventType;
	int m_level;
	BasListener *m_listener;
}ListenerDefine;
#endif
