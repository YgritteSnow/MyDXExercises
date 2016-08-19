#ifndef __MODEL_H__
#define __MODEL_H__

#include "model_3d.h"

class Model : public ModelInterface
{
public:
	Model();
	~Model();

	// model ���
	virtual void Render();
	virtual bool LoadToRam();
	virtual void UnloadFromRam();
	virtual bool LoadToBuffer();
	virtual void UnloadFromBuffer();

	// transform ���
	void Reset();

private:
	Model3D* m_model;
	D3DXMATRIX m_worldTrans;
};
#endif