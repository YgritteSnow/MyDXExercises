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

	virtual bool OnMouseMove(float x_screen, float y_screen);
	virtual bool OnSpaceKeyDown(bool isDown);
	virtual bool OnArrowKeyDown(bool isDown, D3DXVECTOR3 direct);

public:
	const D3DXMATRIX GetProjMatrix() const;
	const D3DXMATRIX GetViewMatrix() const;
	const D3DXMATRIX GetViewProjMatrix() const;
	const D3DXMATRIX GetWorldViewProjMatrix(const D3DXMATRIX* worldTransform) const;

private:
	Camera* m_camera;
};
#endif 