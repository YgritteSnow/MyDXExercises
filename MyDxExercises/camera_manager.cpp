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

bool CameraManager::OnKeyDown(WPARAM wParam)
{
	switch( wParam )
	{
	case VK_SPACE:
		Reset();
		return true;

	default:
		return false;
	}
}

bool CameraManager::OnKeyMove(float x_screen, float y_screen)
{
	m_camera->RotateXYZ(x_screen, 0, y_screen);
	return true;
}

void CameraManager::Reset()
{
	m_camera->Reset();
}

const D3DXMATRIX& CameraManager::GetProjMatrix()
{
	return m_camera->GetProjMatrix();
}
const D3DXMATRIX CameraManager::GetViewMatrix()
{
	return m_camera->GetViewMatrix();
}