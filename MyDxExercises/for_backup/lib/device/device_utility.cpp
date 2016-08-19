#include <d3d9.h>
#pragma comment( lib, "d3d9.lib" )

#include "lib/device/device_utility.h"
#include "lib/event/event_manager.h"

static LPDIRECT3D9 g_d3d = NULL;
static LPDIRECT3DDEVICE9 g_d3ddevice = NULL;

HRESULT N_DeviceUtility::F_InitD3d( HWND a_hwnd )
{
	g_d3d = Direct3DCreate9( D3D_SDK_VERSION );
	if( !g_d3d )
		return E_FAIL;

	D3DPRESENT_PARAMETERS t_dp;
	ZeroMemory( &t_dp, sizeof(t_dp) );
	t_dp.Windowed = true;
	t_dp.BackBufferFormat = D3DFMT_UNKNOWN;
	t_dp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	t_dp.EnableAutoDepthStencil = TRUE;
	t_dp.AutoDepthStencilFormat = D3DFMT_D16;

	if( FAILED( g_d3d->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		a_hwnd, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
		&t_dp, 
		&g_d3ddevice
		) ) )
		return E_FAIL;

	return S_OK;
}


void N_DeviceUtility::F_OnRelease()
{
	if( g_d3d )
	{
		g_d3d->Release();
		g_d3d = NULL;
	}
	if( g_d3ddevice )
	{
		g_d3ddevice->Release();
		g_d3d = NULL;
	}
}

LRESULT CALLBACK N_DeviceUtility::F_WinProc( HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam )
{
	switch( a_msg )
	{
	case WM_PAINT:
		break;

	case WM_LBUTTONDOWN:
		//
		break;

	case WM_LBUTTONUP:
		//GameManager::GetGameManager().HandleLeftMouseButton( false );
		break;

	case WM_MOUSEMOVE:
		//GameManager::GetGameManager().HandleMouseMove( LOWORD( a_lParam ), HIWORD( a_lParam ) );
		break;

	case WM_KEYDOWN:
		C_EventManager::GetEventHandler()->F_OnKeyDown( a_hwnd, a_wParam );
		break;

	case WM_DESTROY:
		F_OnRelease();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc( a_hwnd, a_msg, a_wParam, a_lParam );
}
