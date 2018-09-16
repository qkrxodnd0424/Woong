#pragma once

enum MouseButton{LEFT, RIGHT, MIDDLE};
typedef struct _MOUSESTATE
{
	int x;
	int y;
	SDL_bool bIsDown[4];
	SDL_bool bIsUp[4];
}MOUSESTATE;

class IInputHandler
{
public:
	IInputHandler()
	{
	}

	virtual ~IInputHandler()
	{
	}

public:
	virtual void KeyboardHandler(void) = 0;
	virtual void MouseHandler(MOUSESTATE mouseState) = 0;
};