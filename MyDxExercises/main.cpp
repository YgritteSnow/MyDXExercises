#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <tchar.h>
#include <vector>

#include "model_2d.h"
#include "model.h"

LPDIRECT3D9 g_d3d = NULL;
LPDIRECT3DDEVICE9 g_d3ddevice = NULL;

const int g_screen_width = 400;
const int g_screen_height = 500;

LRESULT InitD3D( HWND hwnd );
void Render();
void Clear();
LRESULT CALLBACK MyWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

void InitModels();
void RenderModels();

INT WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
{
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		MyWndProc, 
		0, 0, 
		hInstance, 
		NULL, NULL, NULL, NULL, 
		_T("myclass"), 
		NULL
	};
	if( FAILED( RegisterClassEx(&wc) ) )
		return 0;

	HWND hwnd = CreateWindow(
		_T("myclass"), _T("asdfasdfasdf"), WS_OVERLAPPEDWINDOW, 0, 0, 300, 400, NULL, NULL, hInstance, 0 );
	if( !hwnd )
		return 0;

	if( FAILED(InitD3D(hwnd) ) )
		return 0;

	InitModels();

	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, NULL, NULL, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			Render();
		}
	}

	UnregisterClass(_T("myclass"), hInstance);

	return 0;
}

LRESULT CALLBACK MyWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_PAINT:
		Render();
		return 0;

	case WM_DESTROY:
		Clear();
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		{
			switch( wParam )
			{
			case VK_ESCAPE:
				DestroyWindow( hwnd );
				return 0;

			default:
				DestroyWindow( hwnd );
				return DefWindowProc( hwnd, msg, wParam, lParam );
			}
		}

	default:
		return DefWindowProc( hwnd, msg, wParam, lParam );
	}
}

LRESULT InitD3D( HWND hwnd )
{
	if( NULL == (g_d3d = Direct3DCreate9(D3D_SDK_VERSION)) )
		return E_FAIL;

	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	pp.Windowed = true;
	pp.BackBufferFormat = D3DFMT_UNKNOWN;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	if( FAILED(g_d3d->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
		&pp, 
		&g_d3ddevice
		)) )
		return E_FAIL;

	return S_OK;
}

void Render()
{
	g_d3ddevice->Clear(0, NULL, D3DCLEAR_TARGET, 0x00ffffff, 1.0f, 0);
	if( SUCCEEDED( g_d3ddevice->BeginScene() ) )
	{
		RenderModels();
		g_d3ddevice->EndScene();
	}
	g_d3ddevice->Present(NULL, NULL, NULL, NULL);
}

void Clear()
{
	if( g_d3d )
	{
		g_d3d->Release();
		g_d3d = NULL;
	}
	if( g_d3ddevice )
	{
		g_d3ddevice->Release();
		g_d3ddevice = NULL;
	}
}

static std::vector<ModelInterface*> s_vec_models;

void InitModels()
{
	Model2D* m = new Model2D;
	if( m->LoadToRam() && m->LoadToBuffer() )
		s_vec_models.push_back(m);

	ModelInterface* m2 = new Model3D;
	if( m2->LoadToRam() && m2->LoadToBuffer() )
		s_vec_models.push_back(m2);
}
void RenderModels()
{
	for(auto it = s_vec_models.begin(); it != s_vec_models.end(); ++it )
	{
		(*it)->Render();
	}
}