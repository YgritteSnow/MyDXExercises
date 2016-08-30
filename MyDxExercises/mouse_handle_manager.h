#ifndef __MOUSE_HANDLE_MANAGER_H__
#define __MOUSE_HANDLE_MANAGER_H__

#include <vector>
#include <d3d9.h>
#include <d3dx9math.h>

#include "manager_register.h"

extern const int g_screen_width;
extern const int g_screen_height;
extern const float g_key_sensitivity;

class MouseHandlerObject
{
public:
	virtual bool OnMouseMove(float x_screen, float y_screen){return true;};

	virtual bool OnEscapeKeyDown(bool isDown){return false;};
	virtual bool OnSpaceKeyDown(bool isDown){return false;};
	virtual bool OnArrowKeyDown(bool isDown, D3DXVECTOR3 direct){return false;};
};

class MouseHandleManager : public ManagerRegister<MouseHandlerObject>
{
private:
	MouseHandleManager();
	~MouseHandleManager();

public:
	static MouseHandleManager* GetMouseHandleManager();

public:
	void OnKeyDown(WPARAM wParam);
	void OnWheelMove(int deltaMove);

	void OnLeftMousePress(bool isDown, int x, int y);
	void OnRightMousePress(bool isDown, int x, int y);

	void OnMouseMove(int x, int y);


private:
	void OnArrowKeyDown(bool isDown, D3DXVECTOR3 direct);
	void OnEscapeKeyDown(bool isDown);
	void OnSpaceKeyDown(bool isDown);

	void OnMouseMove_LButton(int x, int y);
	void SyncMousePos(int x, int y);

private:
	int m_last_mousepos_x, m_last_mousepos_y;
	bool m_is_left_mouse_down;

	bool m_is_inited;
};
#endif 