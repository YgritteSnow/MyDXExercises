#include "camera_manager.h"

CameraManager::CameraManager()
	: m_camera(NULL)
{
	m_camera = new Camera;
}

CameraManager::~CameraManager()
{
	if( m_camera )
	{
		delete m_camera;
		m_camera = NULL;
	}
}

CameraManager* CameraManager::GetCameraManager()
{
	static CameraManager s_cameraManager;
	return &s_cameraManager;
}

void CameraManager::InitCamera()
{
	Reset();
}

bool CameraManager::OnSpaceKeyDown(bool isDown)
{
	if( isDown )
	{
		Reset();
		return true;
	}
	return false;
}

bool CameraManager::OnMouseMove(float x_screen, float y_screen)
{
	m_camera->RotateXYZ(x_screen, y_screen, 0);
	return true;
}

bool CameraManager::OnArrowKeyDown(bool isDown, D3DXVECTOR3 direct)
{
	if(!isDown)
		return false;

	m_camera->MoveXYZ(direct.x, direct.y, direct.z);
	return false;
}

void CameraManager::Reset()
{
	m_camera->Reset();
}

const D3DXMATRIX CameraManager::GetProjMatrix() const
{
	return m_camera->GetProjMatrix();
}
const D3DXMATRIX CameraManager::GetViewMatrix() const
{
	D3DXMATRIX res;
	D3DXMatrixInverse(&res, NULL, &m_camera->GetViewMatrix());
	return m_camera->GetViewMatrix();
}
const D3DXMATRIX CameraManager::GetViewProjMatrix() const
{
	D3DXMATRIX res;
	D3DXMatrixMultiply( &res, &GetViewMatrix(), &GetProjMatrix() );
	res = GetViewMatrix() * GetProjMatrix();
	return res;
}
const D3DXMATRIX CameraManager::GetWorldViewProjMatrix(const D3DXMATRIX* worldTransform) const
{
	D3DXMATRIX res;
	D3DXMatrixMultiply( &res, &GetViewMatrix(), &GetProjMatrix() );
	D3DXMatrixMultiply( &res, worldTransform, &res );
	res = *worldTransform * GetViewMatrix() * GetProjMatrix();
	return res;
}