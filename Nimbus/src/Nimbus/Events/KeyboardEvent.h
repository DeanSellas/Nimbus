#pragma once
#include "Event.h"

namespace Nimbus
{
	class KeyBoardEvent : public Event
	{
	public:
		KeyBoardEvent() { SetEventType(); }
		KeyBoardEvent(const EventType type, const unsigned char key) : key(key) { SetEventType(type); }
		bool isPressed() const { return GetEventType() == EventType::KeyPressed; }
		bool isReleased() const { return GetEventType() == EventType::KeyReleased; }
		unsigned char GetKeyCode() const { return key; }

	private:
		unsigned char key;
	};
}