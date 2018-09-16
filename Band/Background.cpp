#include "stdafx.h"

#define STR_MAX		256
char strImageArray[][STR_MAX] = {
	"./Image/Background/MAIN.bmp",
	"./Image/Background/InGame.bmp",
	"./Image/Background/HowTo.bmp",
	"./Image/Background/Credit.bmp",
	NULL };

BACKGROUND* InitBackGround(SDL_Renderer* pRender)
{
	BACKGROUND* Temp;
	Temp = (BACKGROUND*)malloc(sizeof(BACKGROUND));
	Temp->pRender = pRender;
	Temp->select = BACKGROUND::MAIN;
	SDL_Surface* pImage = SDL_LoadBMP(strImageArray[Temp->select]);
	Temp->imgBackground = SDL_CreateTextureFromSurface(pRender, pImage);
	SDL_FreeSurface(pImage);

	return Temp;
}

void Draw(BACKGROUND* obj)
{
	if (obj == NULL) return;

	SDL_RenderCopy(obj->pRender, obj->imgBackground, NULL, NULL);
}

void Select(BACKGROUND* obj, int sel)
{
	if (obj == NULL) return;

	SDL_DestroyTexture(obj->imgBackground);
	SDL_Surface* pImage = SDL_LoadBMP(strImageArray[sel]);
	obj->imgBackground = SDL_CreateTextureFromSurface(obj->pRender, pImage);
	SDL_FreeSurface(pImage);
}

void Release(BACKGROUND* obj)
{
	if (obj == NULL) return;
	obj->pRender = NULL;
	SDL_DestroyTexture(obj->imgBackground);
	free(obj);
}