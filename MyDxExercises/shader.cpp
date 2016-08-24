#include "shader.h"

Shader::Shader()
	: m_isValid(false)
	, m_effect(NULL)
{

}

Shader::~Shader()
{
	UnloadFromBuffer();
	UnloadFromRam();
}

void Shader::Render()
{

}

bool Shader::LoadToRam()
{
	UnloadFromRam();
	UnloadFromBuffer();

	return m_isValid = m_isValid && true;
}

void Shader::UnloadFromRam()
{
	m_isValid = false;
	return;
}

bool Shader::LoadToBuffer()
{
	UnloadFromBuffer();

	auto hr = D3DXCreateEffectFromFile(g_d3ddevice, _T("jj_test.fx"), NULL, NULL, 0, 0, &m_effect, NULL);
	if( FAILED(hr) )
		return m_isValid = m_isValid && false;

	return m_isValid = m_isValid && true;
}

void Shader::UnloadFromBuffer()
{
	m_isValid = false;
	if( m_effect )
	{
		m_effect->Release();
		m_effect = NULL;
	}
}