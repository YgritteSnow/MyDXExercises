#include "mouse_handle_manager.h"
#include <tchar.h>

MouseHandeManager::MouseHandeManager()
	: m_last_mousepos_x(0)
	, m_last_mousepos_y(0)
	, m_is_inited(false)
{

}

MouseHandeManager::~MouseHandeManager()
{

}

MouseHandeManager* MouseHandeManager::GetMouseHandleManager()
{
	static MouseHandeManager t_mouseHandleManager;
	return &t_mouseHandleManager;
}

void MouseHandeManager::RegisterMouseHandlerObject(MouseHandlerObject* handler)
{
	for(auto it = m_vec_handlerObject.begin(); it != m_vec_handlerObject.end(); ++it )
	{
		if( *it == handler )
		{
			return;
		}
	}
	m_vec_handlerObject.push_back(handler);
}

void MouseHandeManager::UnRegisterMouseHandlerObject(MouseHandlerObject* handler)
{
	for(auto it = m_vec_handlerObject.begin(); it != m_vec_handlerObject.end(); ++it )
	{
		if( *it == handler )
		{
			m_vec_handlerObject.erase(it);
			return;
		}
	}
}

void MouseHandeManager::OnKeyDown(WPARAM wParam)
{
	for( auto it = m_vec_handlerObject.begin(); it != m_vec_handlerObject.end(); ++it )
	{
		(*it)->OnKeyDown(wParam);
	}
}

void MouseHandeManager::OnMouseMove(int x, int y)
{
	if( m_is_inited )
	{
		float t_floatx = float(x-m_last_mousepos_x) / g_screen_width * 2.0f * D3DX_PI;
		float t_floaty = float(y-m_last_mousepos_y) / g_screen_height * 2.0f * D3DX_PI;

		for( auto it = m_vec_handlerObject.begin(); it != m_vec_handlerObject.end(); ++it )
		{
			(*it)->OnKeyMove(t_floatx, t_floaty);
		}
	}
	else
	{
		m_is_inited = true;
	}

	m_last_mousepos_x = x;
	m_last_mousepos_y = y;
}