#ifndef __FOR_BACKUP_LIB_EVENT_EVENT_MANAGER_H__
#define __FOR_BACKUP_LIB_EVENT_EVENT_MANAGER_H__
#include <Windows.h>
class I_EventHandler
{
public:
	virtual bool F_OnKeyDown( HWND a_hwnd, WPARAM a_wParam ) = 0;
	virtual void F_OnUpdate() = 0;
};

class C_EventManager : public I_EventHandler
{
public:
	static I_EventHandler* GetEventHandler();
	bool F_OnKeyDown( HWND a_hwnd, WPARAM a_wParam );
	void F_OnUpdate();
};
#endif 