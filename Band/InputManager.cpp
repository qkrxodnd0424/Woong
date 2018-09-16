#include "StdAfx.h"
#include "InputManager.h"


CInputManager::CInputManager(void)
{
	m_pCurInputHandler = NULL;
}


CInputManager::~CInputManager(void)
{
}

bool CInputManager::Initialize()
{
	memset( m_OldKeyState, 0, sizeof(m_OldKeyState) );
	memset( m_CurKeyState, 0, sizeof(m_CurKeyState) );

	memset( &m_MouseState, 0, sizeof(m_MouseState) );
	
	return true;
}

void CInputManager::Terminate()
{

}

void CInputManager::Keyboard()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		if (currentKeyStates[nCnt])
		{
			m_CurKeyState[nCnt] = SDL_TRUE;
		}
		else
		{
			m_CurKeyState[nCnt] = SDL_FALSE;
		}
	}
	m_pCurInputHandler->KeyboardHandler();

	memcpy(m_OldKeyState, m_CurKeyState, 256);
}

void CInputManager::Mouse()
{
	SDL_Event evnt;
	SDL_PollEvent(&evnt);

	if (evnt.type == SDL_MOUSEBUTTONDOWN)
	{
		switch (evnt.button.button)
		{
		case SDL_BUTTON_LEFT:	
			m_MouseState.bIsDown[MouseButton::LEFT] = SDL_TRUE;		
			m_MouseState.bIsUp[MouseButton::LEFT] = SDL_FALSE;
			break;
		case SDL_BUTTON_RIGHT:	
			m_MouseState.bIsDown[MouseButton::RIGHT] = SDL_TRUE;	
			m_MouseState.bIsUp[MouseButton::RIGHT] = SDL_FALSE;
			break;
		case SDL_BUTTON_MIDDLE:	
			m_MouseState.bIsDown[MouseButton::MIDDLE] = SDL_TRUE;	
			m_MouseState.bIsUp[MouseButton::MIDDLE] = SDL_FALSE;
			break;
		}
	}
	if (evnt.type == SDL_MOUSEBUTTONUP)
	{
		m_MouseState.bIsDown[MouseButton::LEFT] = SDL_FALSE;
		m_MouseState.bIsDown[MouseButton::RIGHT] = SDL_FALSE;
		m_MouseState.bIsDown[MouseButton::MIDDLE] = SDL_FALSE;

		m_MouseState.bIsUp[MouseButton::LEFT]   = SDL_TRUE;
		m_MouseState.bIsUp[MouseButton::RIGHT]  = SDL_TRUE;
		m_MouseState.bIsUp[MouseButton::MIDDLE] = SDL_TRUE;
	}
	int x, y;
	SDL_GetMouseState(&x, &y);
	m_MouseState.x = x;
	m_MouseState.y = y;

	m_pCurInputHandler->MouseHandler(m_MouseState);
}

void CInputManager::Pulse()
{
	if (m_pCurInputHandler)
	{
		Keyboard();
		Mouse();
	}
}
