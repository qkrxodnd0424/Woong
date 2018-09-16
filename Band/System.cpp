#include "stdafx.h"
BACKGROUND* bg;
BUTTON* btnPlay;
BUTTON* btnCredit;
BUTTON* btnHowTo;
BUTTON* btnExit;
BUTTON* btnStop;
BUTTON* btnBack[2];
BUTTON* Play1[5];    
BALL* ball[5];
SOUND* sound;
CFrameSkip*		m_pGameFrame;

float AniTime;
int fTime;
bool blsMusic;

void Frame(int fps)
{
	m_pGameFrame->SetFramePerSec(fps);
}

void funcLeftDownBtn()
{
	bg->select = BACKGROUND::GAME;
	Select(bg, bg->select);
}
void funcRightDownBtn()
{
	bg->select = BACKGROUND::CREDIT;
	Select(bg, bg->select);
}
void funcHowBtn()
{
	bg->select = BACKGROUND::HOWTO;
	Select(bg, bg->select);
}
void funcExit()
{
	SDL_Quit();
}
void funcBack()
{
	bg->select = BACKGROUND::MAIN;
	Select(bg, bg->select);
	Frame(60);
	Mix_HaltMusic();
	AniTime = 0;
	blsMusic = false;
}

void funcPlay()
{	
	Frame(8);
	sound->select = SOUND::ONE;
	Select(sound, sound->select);
	Play(sound);
	AniTime = 0;
	SDL_Delay(200);
	blsMusic = true;
}
void funcPlay1()
{
	Frame(10);
	sound->select = SOUND::TWO;
	Select(sound, sound->select);
	Play(sound);
	AniTime = 0;
	SDL_Delay(200);
	blsMusic = true;
}
void funcPlay2()
{
	Frame(10);
	sound->select = SOUND::THREE;
	Select(sound, sound->select);
	Play(sound);
	AniTime = 0;
	SDL_Delay(200);
	blsMusic = true;
}
void funcPlay3()
{
	Frame(11);
	sound->select = SOUND::FOUR;
	Select(sound, sound->select);
	Play(sound);
	AniTime = 0;
	SDL_Delay(200);
	blsMusic = true;
}
void funcPlay4()
{
	Frame(10);
	sound->select = SOUND::FIVE;
	Select(sound, sound->select);
	Play(sound);
	AniTime = 0;
	SDL_Delay(200);
	blsMusic = true;
}

void stop()
{
	Frame(60);
	Mix_HaltMusic();
	SDL_Delay(50);
	blsMusic = false;
}
void Ani(bool a, bool b, bool c, bool d, bool e)
{
	Draw(ball[0], a);
	Draw(ball[1], b);
	Draw(ball[2], c);
	Draw(ball[3], d);
	Draw(ball[4], e);
}

CSystem::CSystem(void)
{

}

CSystem::~CSystem(void)
{

}

bool CSystem::Initialize()
{
	CBaseWindow::Initialize();
	CTimeManager::Initialize();

	fTime = 2;
	AniTime = 0;
	blsMusic = false;

	m_pGameFrame = new CFrameSkip;
	m_pGameFrame->SetFramePerSec(60);

	m_pInputManager = new CInputManager;
	m_pInputManager->Initialize();
	m_pInputManager->SetInputHandler(this);

	//여기에 오브젝트 초기화 코드를 넣으세요.
	bg = InitBackGround(m_pRender);
	sound = InitSound();

	btnPlay = InitButton(m_pRender, "./Image/UI/MainPlay.bmp", "./Image/UI/MainPlay1.bmp", 975, 200, funcLeftDownBtn, 1);
	btnCredit = InitButton(m_pRender, "./Image/UI/CreditUi.bmp", "./Image/UI/CreditUi1.bmp", 1035, 310, funcRightDownBtn, 1);
	btnHowTo = InitButton(m_pRender, "./Image/UI/HowToUi.bmp", "./Image/UI/HowToUi1.bmp", 1027, 390, funcHowBtn, 1);
	btnExit = InitButton(m_pRender, "./Image/UI/ExitUi.bmp", "./Image/UI/ExitUi1.bmp", 1055, 470, funcExit, 1);
	btnBack[0] = InitButton(m_pRender, "./Image/UI/CBack.bmp", "./Image/UI/CBack1.bmp", 1130, 620, funcBack, 2);
	btnBack[1] = InitButton(m_pRender, "./Image/UI/CBack.bmp", "./Image/UI/CBack1.bmp", 600, 500, funcBack, 2);
	Play1[0] = InitButton(m_pRender, "./Image/UI/Play.bmp", "./Image/UI/Play1.bmp", 270, 103, funcPlay, 1);
	Play1[1] = InitButton(m_pRender, "./Image/UI/Play.bmp", "./Image/UI/Play1.bmp", 270, 228, funcPlay1, 1);
	Play1[2] = InitButton(m_pRender, "./Image/UI/Play.bmp", "./Image/UI/Play1.bmp", 270, 358, funcPlay2, 1);
	Play1[3] = InitButton(m_pRender, "./Image/UI/Play.bmp", "./Image/UI/Play1.bmp", 270, 483, funcPlay3, 1);
	Play1[4] = InitButton(m_pRender, "./Image/UI/Play.bmp", "./Image/UI/Play1.bmp", 270, 610, funcPlay4, 1);
	
	btnStop = InitButton(m_pRender, "./Image/UI/Stop.bmp", "./Image/UI/Stop1.bmp", 210, 23, stop, 1);

	ball[0] = InitBall(m_pRender, "RedAni", 510, 370);
	ball[1] = InitBall(m_pRender, "GreenAni", 640, 220);
	ball[2] = InitBall(m_pRender, "PAni", 850, 300);
	ball[3] = InitBall(m_pRender, "EAni", 350, 10);
	ball[4] = InitBall(m_pRender, "GAni", 990, 150);

	return true;
}

void CSystem::Pulse()
{
	CTimeManager::Pulse();
	m_pInputManager->Pulse();

	float fTimeStep = CTimeManager::GetTimeStep();
	AniTime += fTimeStep;

	if (m_pGameFrame->Update(fTimeStep))
	{
		SDL_SetRenderDrawColor(m_pRender, MIN8, MIN8, MAX8, MAX8);
		SDL_RenderClear(m_pRender);
		//==========================================
		//여기에 오브젝트 프로세스 코드를 넣으세요.
		//배경 오브젝트
		Draw(bg);
		if (bg->select == BACKGROUND::MAIN)
		{			
			Draw(m_pRender, btnPlay);
			Draw(m_pRender, btnCredit);
			Draw(m_pRender, btnHowTo);
			Draw(m_pRender, btnExit);
		}
		if (bg->select == BACKGROUND::GAME)
		{		
			Draw(m_pRender, btnBack[0]);
			for (int i = 0; i < 5; i++)
				Draw(m_pRender, Play1[i]);
			Draw(m_pRender, btnStop);
			if (!blsMusic)
				Ani(false, false, false, false, false);
		}
		if (blsMusic && sound->select == SOUND::ONE)
		{
			if (AniTime > 0 && AniTime < 17)
				Ani(true, true, true, false, false);
			else if (AniTime >= 17 && AniTime < 26)
				Ani(false, true, false, true, true);
			else if (AniTime >= 26 && AniTime < 34)
				Ani(true, true, true, true, true);
			else if (AniTime >= 34 && AniTime < 42)
				Ani(true, false, false, true, true);
			else if (AniTime >= 42 && AniTime < 51)
				Ani(false, false, true, true, true);
			else if (AniTime >= 51 && AniTime < 67)
				Ani(true, true, true, false, false);
			else if (AniTime >= 67 && AniTime < 84)
				Ani(true, true, true, true, true);
			else if (AniTime >= 84 && AniTime < 93)
				Ani(false, true, false, false, false);
			else
				Ani(true, true, true, true, true);
		}

		if (blsMusic && sound->select == SOUND::TWO)
		{
			if (AniTime > 0 && AniTime < 17)
				Ani(true, true, true, true, true);
			else if (AniTime >= 17 && AniTime < 32.5)
				Ani(true, true, true, false, false);
			else if (AniTime >= 32.5 && AniTime < 48)
				Ani(false, true, false, false, false);
			else
				Ani(true, true, true, true, true);
		}

		if (blsMusic && sound->select == SOUND::THREE)
		{
			if (AniTime > 0 && AniTime < 15)
				Ani(false, false, false, false, true);
			else if (AniTime >= 15 && AniTime < 24)
				Ani(true, false, false, true, true);
			else if (AniTime >= 24 && AniTime < 30.4)
				Ani(false, false, true, true, true);
			else if (AniTime >= 30.4 && AniTime < 45)
				Ani(false, true, false, true, true);
			else if (AniTime >= 45 && AniTime < 59)
				Ani(true, true, true, false, false);
			else
				Ani(true, true, true, true, true);
		}

		if (blsMusic && sound->select == SOUND::FOUR)
		{
			if (AniTime > 0 && AniTime < 8)
				Ani(false, false, false, false, false);
			else if (AniTime >= 8 && AniTime < 21.5)
				Ani(false, false, false, true, false);
			else if (AniTime >= 21.5 && AniTime < 26.7)
				Ani(true, false, false, true, true);
			else if (AniTime >= 26.7 && AniTime < 29)
				Ani(true, true, true, false, false);
			else if (AniTime >= 29 && AniTime < 34)
				Ani(true, false, false, true, true);
			else if (AniTime >= 34 && AniTime < 36)
				Ani(true, true, true, false, false);
			else if (AniTime >= 36 && AniTime < 50)
				Ani(false, true, false, false, false);
			else if (AniTime >= 50 && AniTime < 64)
				Ani(false, false, true, false, false);
			else if (AniTime >= 64 && AniTime < 75)
				Ani(true, false, true, true, false);
			else if (AniTime >= 75 && AniTime < 94)
				Ani(true, true, true, false, false);
			else
				Ani(true, true, true, true, true);
		}

		if (blsMusic && sound->select == SOUND::FIVE)
		{
			if (AniTime > 0 && AniTime < 13)
				Ani(false, false, false, false, true);
			else if (AniTime >= 13 && AniTime < 16.5)
				Ani(false, true, false, false, false);
			else if (AniTime >= 16.5 && AniTime < 19.5)
				Ani(true, true, true, true, true);
			else if (AniTime >= 19.5 && AniTime < 30.5)
				Ani(false, true, false, false, false);
			else if (AniTime >= 30.5 && AniTime < 33.5)
				Ani(true, true, true, false, false);
			else if (AniTime >= 33.5 && AniTime < 45)
				Ani(true, false, true, false, true);
			else if (AniTime >= 45 && AniTime < 54.5)
				Ani(true, true, true, false, false);
			else if (AniTime >= 54.5 && AniTime < 61)
				Ani(true, true, true, true, true);
			else if (AniTime >= 61 && AniTime < 66)
				Ani(true, false, false, false, false);
			else if (AniTime >= 66 && AniTime < 67.5)
				Ani(true, true, true, false, false);
			else if (AniTime >= 67.5 && AniTime < 79)
				Ani(true, true, true, true, true);
			else if (AniTime >= 79 && AniTime < 80.5)
				Ani(true, true, true, false, false);
			else
				Ani(true, true, true, true, true);
		}

		if (bg->select == BACKGROUND::CREDIT || bg->select == BACKGROUND::HOWTO)
			Draw(m_pRender, btnBack[1]);
		//==========================================
		SDL_RenderPresent(m_pRender);
	}
}

void CSystem::Terminate()
{
	//여기에 오브젝트 종료/해제 코드를 넣으세요.
	Release(bg);
	for (int i = 0; i < 5; i++)
		Release(ball[i]);
	Release(btnPlay);
	Release(btnCredit);
	Release(btnHowTo);
	Release(btnExit);
	Release(btnBack[0]);
	Release(btnBack[1]);
	for (int i = 0; i < 5; i++)
	{
		Release(Play1[i]);
	}
	Release(btnStop);
	m_pInputManager->Terminate();

	CBaseWindow::Terminate();
	CTimeManager::Terminate();
}

void CSystem::Run()
{
	while (m_bIsGameRun)
	{
		Pulse(); //Update()
	}
}

#define g_pKeyCodeScan(vk) (m_pInputManager->GetOldKeyState(vk)&&m_pInputManager->GetCurKeyState(vk))

void CSystem::KeyboardHandler() //키보드 입력
{
	if (g_pKeyCodeScan(SDLK_ESCAPE))
		this->m_bIsGameRun = SDL_FALSE;
}

void CSystem::MouseHandler(MOUSESTATE mouseState)
{
	if (mouseState.bIsDown[MouseButton::LEFT])
	{
		MouseDown(btnPlay, mouseState.x, mouseState.y);
		MouseDown(btnCredit, mouseState.x, mouseState.y);
		MouseDown(btnHowTo, mouseState.x, mouseState.y);
		MouseDown(btnExit, mouseState.x, mouseState.y);
		MouseDown(btnBack[0], mouseState.x, mouseState.y);
		MouseDown(btnBack[1], mouseState.x, mouseState.y);
		for (int i = 0; i < 5; i++)
			MouseDown(Play1[i], mouseState.x, mouseState.y);
		MouseDown(btnStop, mouseState.x, mouseState.y);
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			ResetOnUp(Play1[i]);
		}
		ResetOnUp(btnStop);
		ResetOnUp(btnBack[0]);
		ResetOnUp(btnBack[1]);
		ResetOnUp(btnPlay);
		ResetOnUp(btnCredit);
		ResetOnUp(btnHowTo);
		ResetOnUp(btnExit);
	}

	for (int i = 0; i < 5; i++)
	{
		IsOver(Play1[i], mouseState.x, mouseState.y);	
	}
	IsOver(btnStop, mouseState.x, mouseState.y);
	IsOver(btnBack[0], mouseState.x, mouseState.y);
	IsOver(btnBack[1], mouseState.x, mouseState.y);
	IsOver(btnPlay, mouseState.x, mouseState.y);
	IsOver(btnCredit, mouseState.x, mouseState.y);
	IsOver(btnHowTo, mouseState.x, mouseState.y);
	IsOver(btnExit, mouseState.x, mouseState.y);
}




