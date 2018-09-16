#pragma once

typedef struct S_BUTTON
{
	enum eButtonState { BUTTONDOWN, BUTTONUP };

	SDL_Texture* imgUp;
	SDL_Texture* imgDown;
	SDL_Texture* imgCurrent;

	SDL_Rect		rtClip;

	int nX, nY;
	bool bIsVisible;

	void(*func)(void);

}BUTTON;

BUTTON* InitButton(SDL_Renderer* screen, const char* szUp, const char* szDown, int x, int y, void(*f)(void), int z);
void Release(BUTTON* pBtn);
void Draw(SDL_Renderer* drawSurface, BUTTON* pBtn);

BUTTON::eButtonState GetState(BUTTON* pBtn);
void ClickDown(BUTTON* pBtn);
void ClickUp(BUTTON* pBtn);

bool IsOver(BUTTON* pBtn, int px, int py);
void Toggle(BUTTON* pBtn);
void ResetOnUp(BUTTON* pBtn);
void SetCoord(BUTTON* btn, int x, int y);
void SetVisible(BUTTON* btn, bool visible);
bool IsVisible(BUTTON* btn);

void MouseDown(BUTTON* pBtn, int px, int py);
void MouseUp(BUTTON* pBtn, int px, int py);
