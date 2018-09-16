#include "stdafx.h"

#define IMR_DIR "./Image/Ani/"

BALL* InitBall(SDL_Renderer* pRender, const char* name, int x, int y)
{
	BALL* Temp;
	SDL_Surface* Image;
	Temp = (BALL*)malloc(sizeof(BALL));
	Temp->pRender = pRender;
	Temp->numAni = 0;
	for (int i = 0; i < 4; i++)
	{
		char str[128] = IMR_DIR;
		strcat(str, name);
		char temp[256];
		sprintf(temp, "%d.bmp", i + 1);
		strcat(str, temp);
		Image = SDL_LoadBMP(str);
		Uint32 colorkey = SDL_MapRGB(Image->format, 219, 3, 181); //»ö±ò Å° °ª 
		SDL_SetColorKey(Image, SDL_TRUE, colorkey); //»ö±ò Å° °ª ¼³Á¤
		Temp->rtClip.x = x;
		Temp->rtClip.y = y;
		Temp->rtClip.w = Image->w * 1.2;
		Temp->rtClip.h = Image->h * 1.5;
		Temp->pTexture[i] = SDL_CreateTextureFromSurface(pRender, Image);
		Temp->numAni++;
		SDL_FreeSurface(Image);
	}
	return Temp;
}

void Draw(BALL* obj, bool a)
{
	if (obj == NULL) return;

	static int AniCount = 0;

	if (a)
	{
		if (AniCount >= obj->numAni - 1)
			AniCount = 0;
		else
		{
			AniCount++;
		}
		SDL_RenderCopy(obj->pRender, obj->pTexture[AniCount], NULL, &obj->rtClip);
	}
	else
		SDL_RenderCopy(obj->pRender, obj->pTexture[0], NULL, &obj->rtClip);
}

void Release(BALL* obj)
{
	if (obj == NULL) return;
	obj->pRender = NULL;
	for (int i = 0; i < obj->numAni; i++)
	{
		SDL_DestroyTexture(obj->pTexture[i]);
	}
	free(obj);
}