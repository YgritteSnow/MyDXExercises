#ifndef __MODEL_H__
#define __MODEL_H__

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")

#include "model_interface.h"

extern LPDIRECT3DDEVICE9 g_d3ddevice;
extern const int g_screen_width;
extern const int g_screen_height;

class Model3D : public ModelInterface
{
public:
	Model3D();
	~Model3D();

public:
	virtual void Render();

	virtual bool LoadToRam();
	virtual void UnloadFromRam();

	virtual bool LoadToBuffer();
	virtual void UnloadFromBuffer();

private:
	struct VertexStruct
	{
		float x, y, z, rhw;
		DWORD color;
	};
	static const DWORD VertexFVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

	VertexStruct* m_arr_vertex;
	DWORD m_mtlCount;
	LPD3DXMESH m_mesh;
	D3DMATERIAL9* m_arr_mtl;
	LPDIRECT3DTEXTURE9* m_arr_pTex;
};

#endif