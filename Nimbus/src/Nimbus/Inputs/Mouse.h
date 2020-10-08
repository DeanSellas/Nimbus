#pragma once
#include "Input.h"
#include "Nimbus/Events/MouseEvent.h"
namespace Nimbus
{
	class Mouse
	{
	public:
		void OnButton(EventType type, int x, int y);

		void OnWheel(EventType type, int x, int y);

		void OnMouseMove(EventType type, int x, int y);

		bool IsLeftDown() { return m_leftDown; }
		bool IsRightDown() { return m_leftDown; }
		bool IsMiddleDown() { return m_middleDown; }

		int GetPosX() { return m_Position[0]; }
		int GetPosY() { return m_Position[1]; }
		MousePoint GetPos() { return { m_Position[0], m_Position[1] }; }

		MouseEvent ReadEvent();
		bool MouseBufferEmpty() { return m_mouseBuffer.empty(); }
	private:
		Input<MouseEvent> m_mouseBuffer;
		bool m_leftDown = false,
			m_rightDown = false,
			m_middleDown = false;
		int m_Position[2];
	};
}