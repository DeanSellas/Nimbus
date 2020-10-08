#include "pch.h"
#include "Mouse.h"

namespace Nimbus
{
	void Mouse::OnButton(EventType type, int x, int y) {
		MouseEvent e(type, x, y);
		switch(type)
		{
			case EventType::LPress: m_leftDown = true;
			case EventType::LRelease: m_leftDown = false;
			case EventType::RPress: m_rightDown = true;
			case EventType::RRelease: m_rightDown = false;
			case EventType::MPress: m_middleDown = true;
			case EventType::MRelease: m_middleDown = false;
		}
		m_mouseBuffer.push(e);
	}

	void Mouse::OnWheel(EventType type, int x, int y) {
		MouseEvent e(type, x, y);
		m_mouseBuffer.push(e);
	}

	void Mouse::OnMouseMove(EventType type, int x, int y) {
		MouseEvent e(type, x, y);
		m_Position[0] = x;
		m_Position[1] = y;
		m_mouseBuffer.push(e);
	}

	MouseEvent Mouse::ReadEvent() {
		if(m_mouseBuffer.empty())
		{
			return MouseEvent();
		}
		else
		{
			return m_mouseBuffer.pop();
		}
	}
}