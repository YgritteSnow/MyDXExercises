#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <d3dx9math.h>

extern LPDIRECT3DDEVICE9 g_d3ddevice;

class Camera
{
public:
	Camera(){}
	~Camera(){}

	const D3DXMATRIX& GetProjMatrix();
	const D3DXMATRIX GetViewMatrix();

	// 以下的xyz都是指的摄像机空间
	void RotateX(float angle); // 绕着x轴移动
	void RotateY(float angle); // 绕着y轴移动
	void RotateZ(float angle); // 绕着z轴移动
	void RotateXYZ(float angle_x, float angle_y, float angle_z); // 绕着xyz移动

	// 以下的xyz都是指的摄像机空间
	void MoveX(float dist); // 沿着x轴移动
	void MoveY(float dist); // 沿着y轴移动
	void MoveZ(float dist); // 沿着z轴移动
	void MoveXYZ(float dist_x, float dist_y, float dist_z); // 沿着xyz移动
	void MoveXYZ(D3DXVECTOR3 deltaPos); // 沿着xyz移动
	void MoveToPos(D3DXVECTOR3 pos); // 移动到新的位置

	void Reset(); // 重置为默认值

private:
	void RefreshViewTransform();
	void RefreshProjTransform();

private:
	D3DXMATRIX m_mat_project;
	D3DXMATRIX m_mat_camera;
};

#endif 
