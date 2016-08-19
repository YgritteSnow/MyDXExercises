#include "camera.h"

const D3DXMATRIX& Camera::GetProjMatrix()
{
	return m_mat_project;
}
const D3DXMATRIX Camera::GetViewMatrix()
{
	return m_mat_camera;
}

void Camera::RotateX(float angle) // ����x���ƶ�
{
	D3DXMATRIX rotMat;
	D3DXMatrixRotationX(&rotMat, angle);
	D3DXMatrixMultiply(&m_mat_camera, &rotMat, &m_mat_camera);

	RefreshViewTransform();
}

void Camera::RotateY(float angle) // ����y���ƶ�
{
	D3DXMATRIX rotMat;
	D3DXMatrixRotationY(&rotMat, angle);
	D3DXMatrixMultiply(&m_mat_camera, &rotMat, &m_mat_camera);

	RefreshViewTransform();
}

void Camera::RotateZ(float angle) // ����z���ƶ�
{
	D3DXMATRIX rotMat;
	D3DXMatrixRotationZ(&rotMat, angle);
	D3DXMatrixMultiply(&m_mat_camera, &rotMat, &m_mat_camera);

	RefreshViewTransform();
}

void Camera::RotateXYZ(float angle_x, float angle_y, float angle_z) // ����xyz�ƶ�
{
	D3DXMATRIX rotMat;
	D3DXMatrixRotationYawPitchRoll(&rotMat, angle_x, angle_y, angle_z);
	D3DXMatrixMultiply(&m_mat_camera, &rotMat, &m_mat_camera);

	RefreshViewTransform();
}

void Camera::MoveX(float dist) // ����x���ƶ�
{
	MoveXYZ(dist, 0, 0);
}

void Camera::MoveY(float dist) // ����y���ƶ�
{
	MoveXYZ(0, dist, 0);
}

void Camera::MoveZ(float dist) // ����z���ƶ�
{
	MoveXYZ(0, 0, dist);
}

void Camera::MoveXYZ(float dist_x, float dist_y, float dist_z) // ����xyz�ƶ�
{
	D3DXMATRIX transMat;
	D3DXMatrixTranslation(&transMat, dist_x, dist_y, dist_z);
	D3DXMatrixMultiply(&m_mat_camera, &transMat, &m_mat_camera);

	RefreshViewTransform();
}

void Camera::MoveToPos(D3DXVECTOR3 pos) // �ƶ����µ�λ��
{
	pos.x -= m_mat_camera._41;
	pos.y -= m_mat_camera._42;
	pos.z -= m_mat_camera._43;
	MoveXYZ(pos.x, pos.y, pos.z);
}

void Camera::Reset() // ����
{
	D3DXMatrixPerspectiveFovLH(&m_mat_project, D3DX_PI/4, 1.0f, 1.0f, 100.f);

	D3DXVECTOR3 eyePos = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 lookatPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 upVec = D3DXVECTOR3(0.f, 1.f, 0.f);
	D3DXMatrixLookAtLH(&m_mat_camera, &eyePos, &lookatPos, &upVec);

	RefreshViewTransform();
	RefreshProjTransform();
}

void Camera::RefreshViewTransform()
{
	g_d3ddevice->SetTransform(D3DTS_VIEW, &m_mat_camera);
}

void Camera::RefreshProjTransform()
{
	g_d3ddevice->SetTransform(D3DTS_PROJECTION, &m_mat_project);
}