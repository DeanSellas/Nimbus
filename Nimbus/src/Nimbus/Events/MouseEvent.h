#pragma once
#include "Event.h"
#include <vector>
namespace Nimbus
{
	struct MousePoint
	{
		int x, y;
	};

	class MouseEvent : public Event
	{
	public:
		MouseEvent() { SetEventType(); }
		MouseEvent(const EventType type, const int x, const int y) : m_Position{ x,y } { SetEventType(type); }
		MousePoint GetPos() { return { m_Position[0], m_Position[1] }; }
		int GetPosX() const { return m_Position[0]; }
		int GetPosY() const { return m_Position[1]; }

	private:
		int m_Position[2];
	};
}