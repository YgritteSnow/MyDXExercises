#include <tchar.h>
#include "lib/device/device_utility.h"
#include "lib/config/config.h"
#include "lib/event/event_manager.h"

INT WINAPI WinMain( HINSTANCE a_hinst, HINSTANCE, LPSTR, INT )
{
	WNDCLASSEX t_wc = {
		sizeof( WNDCLASSEX ), 
		CS_CLASSDC, 
		N_DeviceUtility::F_WinProc,
		0, 0, 
		a_hinst, 
		NULL, NULL, NULL, NULL, 
		_T("classname"), 
		NULL
	};
	RegisterClassEx( &t_wc );

	HWND t_hwnd = CreateWindow(
		_T("classname"), 
		_T("caption?..."), 
		WS_OVERLAPPEDWINDOW, 
		800, 400,
		N_Config::F_GetScreenPixelWidth(), 
		N_Config::F_GetScreenPixelHeight(), 
		NULL, NULL, a_hinst, 0
		);

	if( t_hwnd )
	{
		if( SUCCEEDED( N_DeviceUtility::F_InitD3d( t_hwnd ) ) )
		{
			ShowWindow( t_hwnd, SW_SHOWDEFAULT );
			UpdateWindow( t_hwnd );
			//GameManager::GetGameManager().PreRender();

			MSG t_msg;
			ZeroMemory( &t_msg, sizeof(t_msg));

			while( t_msg.message != WM_QUIT )
			if( PeekMessage( &t_msg, NULL, NULL, NULL, PM_REMOVE ) )
			{
				TranslateMessage( &t_msg );
				DispatchMessage( &t_msg );
			}
			else
			{
				C_EventManager::GetEventHandler()->F_OnUpdate();
			}
		}
	}

	UnregisterClass( _T("classname"), t_wc.hInstance );

	return 0;
}