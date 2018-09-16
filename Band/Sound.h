#pragma once

typedef struct tagSound
{
	enum { ONE, TWO, THREE, FOUR, FIVE, END };
	Mix_Music* bgm;
	int select;

}SOUND;

SOUND* InitSound();
void Play(SOUND* obj);
void Select(SOUND* obj, int sel);
void Release(SOUND* obj);