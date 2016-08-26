#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#include <tchar.h>

#include "log.h"
#include "model_interface.h"

extern LPDIRECT3DDEVICE9 g_d3ddevice;

class Effect : public ModelInterface
{
public:
	Effect();
	~Effect();

public:
	bool IsValid() const{return m_isValid;};

	virtual void Render() const;

	virtual bool LoadToRam();
	virtual void UnloadFromRam();

	virtual bool LoadToBuffer();
	virtual void UnloadFromBuffer();

	// 重载 ID3DXEffect 的函数
	HRESULT SetMatrix(D3DXHANDLE handle, const D3DXMATRIX* mat );
	HRESULT SetTechnique(D3DXHANDLE handle);
	HRESULT SetTexture(D3DXHANDLE handle, LPDIRECT3DBASETEXTURE9 pTex);
	HRESULT Begin(UINT* pass, DWORD flags);
	HRESULT End();
	HRESULT BeginPass(UINT pass);
	HRESULT EndPass();

public://功能相关
	const LPDIRECT3DVERTEXDECLARATION9 GetVertexDecl();

private:
	bool m_isValid;
	ID3DXEffect* m_effect;
	D3DXMATRIX m_worldTransform;

	LPDIRECT3DVERTEXDECLARATION9 m_arr_vertexDelcaration;
};

#endif 