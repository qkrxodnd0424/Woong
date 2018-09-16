#include "stdafx.h"

#define STR_MAX 256
char strSound[][STR_MAX] = {
	"./Image/Sound/DDD.wav",
	"./Image/Sound/Red.wav",
	"./Image/Sound/TT.wav",
	"./Image/Sound/Likey.wav",
	"./Image/Sound/OOH.wav",
	NULL
};

SOUND* InitSound()
{
	SOUND* Temp;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Temp = (SOUND*)malloc(sizeof(SOUND));
	Temp->select = SOUND::END;
	Temp->bgm = Mix_LoadMUS(strSound[Temp->select]);

	return Temp;
}

void Play(SOUND* obj)
{
	if (obj == NULL) return;

	printf("ang");
	Mix_PlayMusic(obj->bgm, -1);
}

void Select(SOUND* obj, int sel)
{
	if (obj == NULL) return;

	Mix_FreeMusic(obj->bgm);
	obj->bgm = Mix_LoadMUS(strSound[sel]);
}

void Release(SOUND* obj)
{
	if (obj == NULL) return;
	
	Mix_FreeMusic(obj->bgm);
}