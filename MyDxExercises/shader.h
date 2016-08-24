#ifndef __SHADER_H__
#define __SHADER_H__

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#include <tchar.h>

#include "model_interface.h"

extern LPDIRECT3DDEVICE9 g_d3ddevice;

class Shader : public ModelInterface
{
public:
	Shader(){}
	~Shader(){}

public:
	bool IsValid(){return m_isValid;};

	virtual void Render();

	virtual bool LoadToRam();
	virtual void UnloadFromRam();

	virtual bool LoadToBuffer();
	virtual void UnloadFromBuffer();

private:
	bool m_isValid;
	ID3DXEffect* m_effect;
};

#endif