#include "lib/event/event_manager.h"

bool C_EventManager::F_OnKeyDown( HWND a_hwnd, WPARAM a_wParam )
{
	switch( a_wParam )
	{
	case VK_ESCAPE:
		DestroyWindow( a_hwnd );
		return true;
		break;
	}
	return false;
}

void C_EventManager::F_OnUpdate()
{

}

I_EventHandler* C_EventManager::GetEventHandler()
{
	static C_EventManager t_EventManager;
	return &t_EventManager;
}