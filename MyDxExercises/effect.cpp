#include "effect.h"
#include "camera_manager.h"

Effect::Effect()
	: m_isValid(false)
	, m_effect(NULL)
	, m_arr_vertexDelcaration(NULL)
{

}

Effect::~Effect()
{
	UnloadFromBuffer();
	UnloadFromRam();
}

void Effect::Render() const
{
}

bool Effect::LoadToRam()
{
	UnloadFromRam();
	UnloadFromBuffer();

	return true;
}

void Effect::UnloadFromRam()
{
	m_isValid = false;
	return;
}

bool Effect::LoadToBuffer()
{
	UnloadFromBuffer();

	LPD3DXBUFFER errBuf = NULL;
	auto hr = D3DXCreateEffectFromFile(g_d3ddevice, _T("jj_test.fx"), NULL, NULL, 
		D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT | D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT, 
		0, &m_effect, &errBuf);
	
	if( FAILED(hr) )
	{
		if(errBuf)LogOutput((char *)errBuf->GetBufferPointer());
		return m_isValid = false;
	}

	D3DVERTEXELEMENT9 temp_ve[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 }, 
		{ 0, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 32, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	if( FAILED(g_d3ddevice->CreateVertexDeclaration(temp_ve, &m_arr_vertexDelcaration)) )
		return m_isValid = false;

	return m_isValid = true;
}

void Effect::UnloadFromBuffer()
{
	m_isValid = false;
	if( m_effect )
	{
		m_effect->Release();
		m_effect = NULL;
	}
	if( m_arr_vertexDelcaration )
	{
		m_arr_vertexDelcaration->Release();
		m_arr_vertexDelcaration = NULL;
	}
}

const LPDIRECT3DVERTEXDECLARATION9 Effect::GetVertexDecl()
{
	return m_arr_vertexDelcaration;
}

HRESULT Effect::SetMatrix(D3DXHANDLE handle, const D3DXMATRIX* mat )
{
	return m_effect->SetMatrix(handle, mat);
}

HRESULT Effect::SetTechnique(D3DXHANDLE handle)
{
	return m_effect->SetTechnique(handle);
}

HRESULT Effect::SetTexture(D3DXHANDLE handle, LPDIRECT3DBASETEXTURE9 pTex)
{
	return m_effect->SetTexture(handle, pTex);
}

HRESULT Effect::Begin(UINT* pass, DWORD flags)
{
	return m_effect->Begin(pass, flags);
}

HRESULT Effect::End()
{
	return m_effect->End();
}

HRESULT Effect::BeginPass(UINT pass)
{
	return m_effect->BeginPass(pass);
}

HRESULT Effect::EndPass()
{
	return m_effect->EndPass();
}