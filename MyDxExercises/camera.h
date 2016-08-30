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

	// ���µ�xyz����ָ��������ռ�
	void RotateX(float angle); // ����x���ƶ�
	void RotateY(float angle); // ����y���ƶ�
	void RotateZ(float angle); // ����z���ƶ�
	void RotateXYZ(float angle_x, float angle_y, float angle_z); // ����xyz�ƶ�

	// ���µ�xyz����ָ��������ռ�
	void MoveX(float dist); // ����x���ƶ�
	void MoveY(float dist); // ����y���ƶ�
	void MoveZ(float dist); // ����z���ƶ�
	void MoveXYZ(float dist_x, float dist_y, float dist_z); // ����xyz�ƶ�
	void MoveXYZ(D3DXVECTOR3 deltaPos); // ����xyz�ƶ�
	void MoveToPos(D3DXVECTOR3 pos); // �ƶ����µ�λ��

	void Reset(); // ����ΪĬ��ֵ

private:
	void RefreshViewTransform();
	void RefreshProjTransform();

private:
	D3DXMATRIX m_mat_project;
	D3DXMATRIX m_mat_camera;
};

#endif 
