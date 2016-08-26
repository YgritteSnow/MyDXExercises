#ifndef __MODEL_3D_H__
#define __MODEL_3D_H__

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
	virtual void Render() const;

	virtual bool LoadToRam();
	virtual void UnloadFromRam();

	virtual bool LoadToBuffer();
	virtual void UnloadFromBuffer();

	bool SetVertexDecl( D3DVERTEXELEMENT9* pElements, UINT eleCount );

public:
	struct ModelSubsetConstIterator;
	friend ModelSubsetConstIterator;
	struct ModelSubsetConstIterator
	{
		ModelSubsetConstIterator(Model3D* originData):_idx(0), _originData(originData){}
		DWORD _idx;
		Model3D* _originData;
		void Next(){++_idx;};
		bool IsEnd(){return _idx >= this->_originData->m_mtlCount;};
		DWORD GetIdx(){return _idx;}
		LPDIRECT3DTEXTURE9 GetTexture(){
			return this->_originData->m_arr_pTex[_idx];};
	};

	ModelSubsetConstIterator BeginIterator(){return ModelSubsetConstIterator(this);}
	void RenderSubset(DWORD subset) const;

private:
	bool LoadToBuffer_mesh();

	void Render_byShader();
	void Render_byMesh();

private:
	DWORD m_mtlCount;
	LPD3DXMESH m_mesh;
	D3DMATERIAL9* m_arr_mtl;
	LPDIRECT3DTEXTURE9* m_arr_pTex;
};

#endif 