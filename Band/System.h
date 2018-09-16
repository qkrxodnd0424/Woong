#include "stdafx.h"

class CSystem : public CBaseWindow,
			   public CTimeManager,
			   public IInputHandler
{	
private:
	CInputManager*	m_pInputManager;

public:
	CSystem(void);
	~CSystem(void);

private:
	void Pulse();

public:
	bool Initialize();
	void Terminate();
	void Run();

public:
	void KeyboardHandler();
	void MouseHandler(MOUSESTATE mouseState);
};
