#include "mouse_handle_manager.h"
#include <tchar.h>


MouseHandleManager::MouseHandleManager()
	: m_last_mousepos_x(0)
	, m_last_mousepos_y(0)
	, m_is_inited(false)
	, m_is_left_mouse_down(false)
{

}

MouseHandleManager::~MouseHandleManager()
{

}

MouseHandleManager* MouseHandleManager::GetMouseHandleManager()
{
	static MouseHandleManager t_mouseHandleManager;
	return &t_mouseHandleManager;
}

/************************************************************************/
/* 从主循环接收消息                                                                     */
/************************************************************************/

void MouseHandleManager::OnKeyDown(WPARAM wParam)
{
	switch( wParam )
	{
	case VK_ESCAPE:
		OnEscapeKeyDown(true);
		break;
	case VK_SPACE:
		OnSpaceKeyDown(true);
		break;
	case VK_LEFT:
	case 'A':
		OnArrowKeyDown(true, D3DXVECTOR3(-g_key_sensitivity, 0, 0));
		break;
	case VK_RIGHT:
	case 'D':
		OnArrowKeyDown(true, D3DXVECTOR3(g_key_sensitivity, 0, 0));
		break;
	case VK_UP:
	case 'W':
		OnArrowKeyDown(true, D3DXVECTOR3(0, g_key_sensitivity, 0));
		break;
	case VK_DOWN:
	case 'S':
		OnArrowKeyDown(true, D3DXVECTOR3(0, -g_key_sensitivity, 0));
		break;
	}
}

void MouseHandleManager::OnWheelMove(int deltaMove)
{
	deltaMove /= 20;
	OnArrowKeyDown(true,D3DXVECTOR3(0.f, 0.f, -deltaMove * g_key_sensitivity));
}

void MouseHandleManager::OnMouseMove(int x, int y)
{
	if( m_is_left_mouse_down )
	{
		OnMouseMove_LButton(x, y);
	}
}

void MouseHandleManager::OnLeftMousePress(bool isDown, int x, int y)
{
	m_is_left_mouse_down = isDown;
	SyncMousePos(x, y);
}

void MouseHandleManager::OnRightMousePress(bool isDown, int x, int y)
{
	SyncMousePos(x, y);
}

/************************************************************************/
/* 分发消息                                                                     */
/************************************************************************/

void MouseHandleManager::OnArrowKeyDown(bool isDown, D3DXVECTOR3 direct)
{
	for( auto it = m_vec_objs.begin(); it != m_vec_objs.end(); ++it )
	{
		(*it)->OnArrowKeyDown(true, direct);
	}
}

void MouseHandleManager::OnEscapeKeyDown(bool isDown)
{
	for( auto it = m_vec_objs.begin(); it != m_vec_objs.end(); ++it )
	{
		(*it)->OnEscapeKeyDown(true);
	}
}

void MouseHandleManager::OnSpaceKeyDown(bool isDown)
{
	for( auto it = m_vec_objs.begin(); it != m_vec_objs.end(); ++it )
	{
		(*it)->OnSpaceKeyDown(true);
	}
}

void MouseHandleManager::OnMouseMove_LButton(int x, int y)
{
	if( m_is_inited )
	{
		float t_floatx = float(x-m_last_mousepos_x) / g_screen_width * 2.0f * D3DX_PI;
		float t_floaty = float(y-m_last_mousepos_y) / g_screen_height * 2.0f * D3DX_PI;

		for( auto it = m_vec_objs.begin(); it != m_vec_objs.end(); ++it )
		{
			(*it)->OnMouseMove(t_floatx, t_floaty);
		}
	}
	else
	{
		m_is_inited = true;
		m_is_left_mouse_down = GetAsyncKeyState(VK_LBUTTON);
	}

	SyncMousePos(x, y);
}

void MouseHandleManager::SyncMousePos(int x, int y)
{
	m_last_mousepos_x = x;
	m_last_mousepos_y = y;
}