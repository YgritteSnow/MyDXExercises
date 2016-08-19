#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")


LRESULT CALLBACK MyWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_PAINT:
		Render();
		return 0;

	case WM_DESTROY:
		Clear();
		DestroyWindow( hwnd );
		return 0;

	default:
		return DefWindowProc( hwnd, msg, wParam, lParam );
	}
}

INT WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
{
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX),
		WS_OVERLAPPEDWINDOW,
		MyWndProc, 
	}
	return 0;
}