#ifndef __MOUSE_HANDLER_H__
#define __MOUSE_HANDLER_H__

#include <vector>
#include <d3d9.h>
#include <d3dx9math.h>

extern const int g_screen_width;
extern const int g_screen_height;

class MouseHandlerObject
{
public:
	virtual bool OnKeyDown(WPARAM wParam) = 0;
	virtual bool OnKeyMove(float x_screen, float y_screen) = 0;
};

class MouseHandeManager
{
private:
	MouseHandeManager();
	~MouseHandeManager();

public:
	static MouseHandeManager* GetMouseHandleManager();

public:
	void RegisterMouseHandlerObject(MouseHandlerObject* handler);
	void UnRegisterMouseHandlerObject(MouseHandlerObject* handler);

	void OnKeyDown(WPARAM wParam);
	void OnMouseMove(int x, int y);

private:
	std::vector<MouseHandlerObject*> m_vec_handlerObject;
	int m_last_mousepos_x, m_last_mousepos_y;

	bool m_is_inited;
};
#endif