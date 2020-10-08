#pragma once
#include "Nimbus/Events/KeyBoardEvent.h"

#include "Input.h"

namespace Nimbus
{
	class KeyBoard
	{
	public:
		KeyBoard();
		bool KeyIsPressed(const unsigned char keycode) { return keyStates[keycode]; }

		KeyBoardEvent ReadKey();
		unsigned char ReadChar();

		void OnKeyPressed(const unsigned char key);
		void OnKeyReleased(const unsigned char key);
		void OnChar(const unsigned char key);

		void ChangeKeyAutoState() { autoRepeatKey = !autoRepeatKey; }
		void ChangeCharAutoState() { autoRepeatChar = !autoRepeatChar; }

		bool KeyAutoRepeat() { return autoRepeatKey; }
		bool CharAutoRepeat() { return autoRepeatChar; }

		bool KeyBufferEmpty() { return keyBuf.empty(); }
		bool CharBufferEmpty() { return charBuf.empty(); }

	private:
		bool autoRepeatKey = false;
		bool autoRepeatChar = false;
		bool keyStates[256];
		Input<KeyBoardEvent> keyBuf;
		Input<unsigned char> charBuf;
	};
}
