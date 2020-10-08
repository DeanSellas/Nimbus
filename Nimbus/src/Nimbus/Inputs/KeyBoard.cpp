#include "pch.h"
#include "KeyBoard.h"


namespace Nimbus
{
	KeyBoard::KeyBoard() {
		for(bool item : keyStates)
		{
			item = false;
		}
	}

	KeyBoardEvent KeyBoard::ReadKey() {
		if(keyBuf.empty())
		{
			return KeyBoardEvent();
		}
		else
		{
			// removes item from queue and returns it
			return keyBuf.pop();
		}
	}

	unsigned char KeyBoard::ReadChar() {
		if(charBuf.empty())
		{
			return 0u;
		}
		else
		{
			return charBuf.pop();
		}
	}

	void KeyBoard::OnKeyPressed(const unsigned char key) {
		keyStates[key] = true;
		keyBuf.push(KeyBoardEvent(EventType::KeyPressed, key));
	}

	void KeyBoard::OnKeyReleased(const unsigned char key) {
		keyStates[key] = false;
		keyBuf.push(KeyBoardEvent(EventType::KeyReleased, key));
	}

	void KeyBoard::OnChar(const unsigned char key) {
		charBuf.push(key);
	}
}
