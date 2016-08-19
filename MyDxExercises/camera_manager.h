#ifndef __CAMERA_MANAGER_H__
#define __CAMERA_MANAGER_H__

#include <d3dx9math.h>
#include "camera.h"
#include "mouse_handle_manager.h"

class CameraManager : public MouseHandlerObject
{
private:
	CameraManager();
	~CameraManager();

public:
	static CameraManager* GetCameraManager();
	MouseHandlerObject* QueryMouseHandler(){
		return this;}

	void InitCamera();
	void Reset();

	virtual bool OnKeyDown(WPARAM wParam);
	virtual bool OnKeyMove(float x_screen, float y_screen);

protected:
	const D3DXMATRIX& GetProjMatrix();
	const D3DXMATRIX GetViewMatrix();

private:
	Camera* m_camera;
};
#endif