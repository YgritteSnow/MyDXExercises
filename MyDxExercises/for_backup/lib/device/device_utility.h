#ifndef __FOR_BACKUP_LIB_DEVICE_DEVICE_UTILITY_H__
#define __FOR_BACKUP_LIB_DEVICE_DEVICE_UTILITY_H__
#include <Windows.h>
namespace N_DeviceUtility
{
	HRESULT F_InitD3d( HWND a_hwnd );
	LRESULT CALLBACK F_WinProc( HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam );
	void F_OnRelease();
	void F_OnUpdate();
}
#endif 