#include "model.h"
#include "effect.h"
#include "camera_manager.h"

Model::Model()
	: m_model(NULL)
	, m_effect(NULL)
{}

Model::~Model()
{
	if(m_model)
	{
		delete m_model;
		m_model = NULL;
	}
}

void Model::Render() const
{
	//g_d3ddevice->SetTransform(D3DTS_WORLD, &m_worldTrans);

	if( m_effect->IsValid() )
	{
		g_d3ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		g_d3ddevice->SetRenderState( D3DRS_ZENABLE, TRUE );

		RenderByEffect();
	}
	else
	{
		g_d3ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		g_d3ddevice->SetRenderState( D3DRS_ZENABLE, TRUE );
		g_d3ddevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

		m_model->Render();
	}
}

void Model::RenderByEffect() const
{
	if( !m_effect->IsValid() )
		return;

	HRESULT res;
	HR_RETURN( m_effect->SetMatrix("WorldTransform", &m_worldTrans) );
	HR_RETURN( m_effect->SetMatrix("ViewTransform", &(CameraManager::GetCameraManager()->GetViewMatrix())) );
	HR_RETURN( m_effect->SetMatrix("ProjTransform", &(CameraManager::GetCameraManager()->GetProjMatrix())) );
	HR_RETURN( m_effect->SetMatrix("ViewProjTransform", &(CameraManager::GetCameraManager()->GetViewProjMatrix())) );
	HR_RETURN( m_effect->SetMatrix("WorldViewProjTransform", &(CameraManager::GetCameraManager()->GetWorldViewProjMatrix(&m_worldTrans))) );

	HR_RETURN( m_effect->SetTechnique("Default") );
	UINT passCount = 0;
	HR_RETURN( m_effect->Begin(&passCount, 0) );
	HR_RETURN( g_d3ddevice->SetVertexDeclaration(m_effect->GetVertexDecl()) );
	for( auto it_pass = 0; it_pass != passCount; ++it_pass )
	{
		HR_RETURN( m_effect->BeginPass(it_pass) );

		for( auto it_subset = m_model->BeginIterator(); !it_subset.IsEnd(); it_subset.Next() )
		{
			HR_RETURN( m_effect->SetTexture("DiffuseTexture", it_subset.GetTexture()) );
			m_model->RenderSubset(it_subset.GetIdx());
		}

		HR_RETURN( m_effect->EndPass() );
	}
	HR_RETURN( m_effect->End() );
}

bool Model::LoadToRam()
{
	m_model = new Model3D;
	Reset();
	bool res = m_model->LoadToRam();
	if(!res)
		return false;

	m_effect = new Effect;
	m_effect->LoadToRam(); // m_effect 加载失败也不影响返回false

	return res;
}

void Model::UnloadFromRam()
{
	m_model->UnloadFromRam();
	m_effect->UnloadFromRam();
}

bool Model::LoadToBuffer()
{
	bool res = m_model->LoadToBuffer();
	if( m_effect && m_effect->LoadToBuffer() )
	{
		D3DVERTEXELEMENT9 pElements[MAX_FVF_DECL_SIZE];
		UINT eleCount;
		m_effect->GetVertexDecl()->GetDeclaration(pElements, &eleCount);
		res = res && m_model->SetVertexDecl(pElements, eleCount);
	}

	return res;
}

void Model::UnloadFromBuffer()
{
	m_model->UnloadFromBuffer();
	m_effect->UnloadFromBuffer();
}

void Model::Reset()
{
	D3DXMatrixIdentity(&m_worldTrans);
}