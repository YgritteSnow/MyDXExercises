#include "lib/event/event_manager.h"

class C_ModelManager : public I_EventHandler
{
public:
	virtual bool F_OnKeyDown( HWND a_hwnd, WPARAM a_wParam ){}
	virtual void F_OnUpdate(){}
};