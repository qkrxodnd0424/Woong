#pragma once
typedef struct tagBall
{
	SDL_Renderer* pRender;
	SDL_Texture* pTexture[4];

	SDL_Rect rtClip;

	int numAni;
	int x, y;
}BALL;

BALL* InitBall(SDL_Renderer* pRender, const char* name, int x, int y); // ����
void Draw(BALL* obj, bool a); // �׸�
void Release(BALL* obj); // ����/����