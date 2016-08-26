#ifndef __MODEL_2D_H__
#define __MODEL_2D_H__
/************************************************************************/
/* 使用 rhw 参数，来做2d的模型。或许可以用作界面~                                                                     */
/************************************************************************/

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include "model_interface.h"

extern LPDIRECT3DDEVICE9 g_d3ddevice;
extern const int g_screen_width;
extern const int g_screen_height;

class Model2D : public ModelInterface
{
public:
	Model2D();
	~Model2D();

public:
	virtual void Render() const;

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
	LPDIRECT3DVERTEXBUFFER9 m_vbuffer;
	LPDIRECT3DINDEXBUFFER9 m_ibuffer;
};

#endif 