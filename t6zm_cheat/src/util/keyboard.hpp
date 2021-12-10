#pragma once

namespace t6zm
{
	// keys for ANSI Keyboard layout - basic QWERTY
	enum class eKey
	{
		NONE,
		LEFT_MOUSE,
		RIGHT_MOUSE,
		MIDDLE_MOUSE = 0x4,
		BACKSPACE = 0x8,
		TAB,
		CLEAR = 0xC,
		ENTER,
		SHIFT = 0x10,
		CONTROL,
		ALT,
		PAUSE,
		CAPS_LOCK,
		ESCAPE = 0x1B,
		SPACEBAR = 0x20,
		PAGE_UP,
		PAGE_DOWN,
		END,
		HOME,
		LEFT_ARROW,
		UP_ARROW,
		RIGHT_ARROW,
		DOWN_ARROW,
		SELECT,
		PRINT,
		EXECUTE,
		PRINT_SCREEN,
		INSERT,
		DEL,
		HELP,
		A=0x41, B, C, D,
		E, F, G, H, I, J,
		K, L, M, N, O, P,
		Q, R, S, T, U, V,
		W, X, Y, Z,
		LEFT_WINDOWS = 0x5B,
		RIGHT_WINDOWS,
		NUMPAD0 = 0x60,
		NUMPAD1,
		NUMPAD2,
		NUMPAD3,
		NUMPAD4,
		NUMPAD5,
		NUMPAD6,
		NUMPAD7,
		NUMPAD8,
		NUMPAD9,
		MULTIPLY,
		ADD,
		SEPARATOR,
		SUBTRACT,
		DECIMAL,
		DIVIDE,
		F1, F2, F3,
		F4, F5, F6,
		F7, F8, F9,
		F10,F11,F12,
		NUMLOCK = 0x90,
		SCROLL_LOCK,
		LEFT_SHIFT = 0xA0,
		RIGHT_SHIFT,
		LEFT_CONTROL,
		RIGHT_CONTROL
	};

	struct keyboard
	{
		static bool key_pressed(eKey key)
		{
			return GetAsyncKeyState((int)key) & 0x8000;
		}
	};
}