#pragma once

namespace Nimbus
{
	// ENUM TO STORE EVENT TYPES.
	// KEYBOARD EVENTS ARE 1
	// MOUSE EVENTS ARE 2
	// 0 IS AN INVALID EVENT
	enum class EventType
	{
		KeyPressed, KeyReleased, KeyTyped,
		LPress, LRelease, RPress, RRelease, MPress, MRelease, WheelUp, WheelDown, Move, RAW_MOVE,
		Invalid
	};

	class Event
	{
	public:
		EventType GetEventType() const { return type; }
		void SetEventType(EventType t = EventType::Invalid) { type = t; }
		bool isValid() const { return GetEventType() != EventType::Invalid; }
	private:
		EventType type;
	};
}
