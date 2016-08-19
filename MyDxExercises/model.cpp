#include "model.h"
#include <d3dx9mesh.h>
#pragma comment(lib, "d3dx9.lib")

Model3D::Model3D()
	: m_arr_vertex(NULL)
	, m_arr_mtl(NULL)
	, m_arr_pTex(NULL)
	, m_mtlCount(0)
{

}

Model3D::~Model3D()
{
	UnloadFromRam();
}

void Model3D::Render()
{
	g_d3ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	for( DWORD i = 0; i < m_mtlCount; ++i )
	{
		g_d3ddevice->SetMaterial(&m_arr_mtl[i]);
		g_d3ddevice->SetTexture(0, m_arr_pTex[i]);
		m_mesh->DrawSubset(i);
	}
}

bool Model3D::LoadToRam()
{
	UnloadFromBuffer();

	return true;
}

bool Model3D::LoadToBuffer()
{
	LPD3DXBUFFER t_mtlbuffer;
	if( FAILED( D3DXLoadMeshFromX("tiger.x", D3DXMESH_SYSTEMMEM, g_d3ddevice, NULL, &t_mtlbuffer, NULL, &m_mtlCount, &m_mesh )) )
		return false;

	m_arr_mtl = new D3DMATERIAL9[m_mtlCount];
	m_arr_pTex = new LPDIRECT3DTEXTURE9[m_mtlCount];

	D3DXMATERIAL* t_pMaterial = (D3DXMATERIAL*) t_mtlbuffer->GetBufferPointer();
	for( DWORD i = 0; i < m_mtlCount; ++i )
	{
		m_arr_mtl[i] = (t_pMaterial + i)->MatD3D;
		m_arr_mtl[i].Ambient = m_arr_mtl[i].Diffuse;

		if( FAILED(D3DXCreateTextureFromFile(g_d3ddevice, t_pMaterial[i].pTextureFilename, &m_arr_pTex[i])) )
		{
			m_arr_pTex[i] = NULL;
		}
	}
	t_mtlbuffer->Release();

	return true;
}

void Model3D::UnloadFromRam()
{
	UnloadFromBuffer();

	if( m_arr_vertex )
	{
		delete[] m_arr_vertex;
		m_arr_vertex = NULL;
	}
	if( m_arr_mtl )
	{
		delete[] m_arr_mtl;
		m_arr_mtl = NULL;
	}
	if( m_arr_pTex )
	{
		delete[] m_arr_pTex;
		m_arr_pTex = NULL;
	}
	m_mtlCount = 0;
}

void Model3D::UnloadFromBuffer()
{
	if( m_arr_pTex )
	{
		for( DWORD i = 0; i < m_mtlCount; ++i )
		{
			m_arr_pTex[i]->Release();
			m_arr_pTex[i] = NULL;
		}
	}
}