#include "model.h"

Model::Model()
	: m_model(NULL)
{}

Model::~Model()
{
	if(m_model)
	{
		delete m_model;
		m_model = NULL;
	}
}

void Model::Render()
{
	g_d3ddevice->SetTransform(D3DTS_WORLD, &m_worldTrans);
	m_model->Render();
}

bool Model::LoadToRam()
{
	m_model = new Model3D;
	Reset();
	return m_model->LoadToRam();
}

void Model::UnloadFromRam()
{
	m_model->UnloadFromRam();
}

bool Model::LoadToBuffer()
{
	return m_model->LoadToBuffer();
}

void Model::UnloadFromBuffer()
{
	m_model->UnloadFromBuffer();
}

void Model::Reset()
{
	D3DXMatrixIdentity(&m_worldTrans);
}