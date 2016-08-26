#include "model_3d.h"
#include <d3dx9mesh.h>
#pragma comment(lib, "d3dx9.lib")
#include <tchar.h>

Model3D::Model3D()
	: m_arr_mtl(NULL)
	, m_arr_pTex(NULL)
	, m_mtlCount(0)
{

}

Model3D::~Model3D()
{
	UnloadFromBuffer();
	UnloadFromRam();
}

void Model3D::Render() const
{
	for( DWORD i = 0; i < m_mtlCount; ++i )
	{
		g_d3ddevice->SetMaterial(&m_arr_mtl[i]);
		g_d3ddevice->SetTexture(0, m_arr_pTex[i]);
		m_mesh->DrawSubset(i);
	}
}

void Model3D::RenderSubset(DWORD subset) const 
{
	m_mesh->DrawSubset(subset);
}

bool Model3D::LoadToRam()
{
	UnloadFromBuffer();
	UnloadFromRam();

	return true;
}

bool Model3D::LoadToBuffer()
{
	LPD3DXBUFFER t_mtlbuffer;
	if( FAILED( D3DXLoadMeshFromX(_T("tiger.x"), D3DXMESH_SYSTEMMEM, g_d3ddevice, NULL, &t_mtlbuffer, NULL, &m_mtlCount, &m_mesh )) )
		return false;

	m_arr_mtl = new D3DMATERIAL9[m_mtlCount];
	m_arr_pTex = new LPDIRECT3DTEXTURE9[m_mtlCount];

	D3DXMATERIAL* t_pMaterial = (D3DXMATERIAL*) t_mtlbuffer->GetBufferPointer();
	for( DWORD i = 0; i < m_mtlCount; ++i )
	{
		m_arr_mtl[i] = (t_pMaterial + i)->MatD3D;
		m_arr_mtl[i].Ambient = m_arr_mtl[i].Diffuse;

		if( FAILED(D3DXCreateTextureFromFileA(g_d3ddevice, t_pMaterial[i].pTextureFilename, &m_arr_pTex[i])) )
		{
			m_arr_pTex[i] = NULL;
		}
	}
	t_mtlbuffer->Release();

	return true;
}

bool Model3D::SetVertexDecl( D3DVERTEXELEMENT9* pElements, UINT eleCount )
{
	LPD3DXMESH pTempMesh = NULL;
	m_mesh->CloneMesh(m_mesh->GetOptions(), pElements, g_d3ddevice, &pTempMesh);
	if( !pTempMesh )
	{
		UnloadFromBuffer();
		return false;
	}

	D3DVERTEXELEMENT9 pOldDeclElements[MAX_FVF_DECL_SIZE];

	m_mesh->GetDeclaration(pOldDeclElements);
	bool bHadNormal = false;
	for( UINT idx = 0; idx < D3DXGetDeclLength(pOldDeclElements); ++idx )
	{
		if( pOldDeclElements[idx].Usage == D3DDECLUSAGE_NORMAL )
		{
			bHadNormal = true;
		}
	}

	m_mesh->Release();
	m_mesh = pTempMesh;

	bool bHaveNormal = false;
	for( UINT idx = 0; idx < eleCount; ++idx )
	{
		if( pElements[idx].Usage == D3DDECLUSAGE_NORMAL )
		{
			bHaveNormal = true;
		}
	}

	if( !bHadNormal && bHaveNormal )
	{
		D3DXComputeNormals( m_mesh, NULL );
	}

	return true;
}

void Model3D::UnloadFromRam()
{
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