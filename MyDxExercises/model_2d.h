/************************************************************************/
/* 使用 rhw 参数，来做2d的模型。或许可以用作界面~                                                                     */
/************************************************************************/
#ifndef __MODEL_2D__
#define __MODEL_2D__

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

extern LPDIRECT3DDEVICE9 g_d3ddevice;
extern const int g_screen_width;
extern const int g_screen_height;

struct Model2DVertex
{
	float x, y, z, rhw;
	DWORD color;
};

class Model2D
{
public:
	Model2D();
	~Model2D();

public:
	void Render();

	bool LoadToRam();
	void UnloadFromRam();

	bool LoadToBuffer();
	void UnloadFromBuffer();

private:
	static const DWORD Model2DVertexFVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

	Model2DVertex* m_arr_vertex;
	LPDIRECT3DVERTEXBUFFER9 m_vbuffer;
	LPDIRECT3DINDEXBUFFER9 m_ibuffer;
};

#endif