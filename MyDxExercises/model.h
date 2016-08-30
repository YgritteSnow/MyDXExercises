#ifndef __MODEL_H__
#define __MODEL_H__

#include "model_3d.h"
#include "log.h"
#include "TimerManager.h"

class Effect;

class Model : public ModelInterface, public TimerObject
{
public:
	Model();
	~Model();

	// model 相关
	virtual void Render() const;

	virtual bool LoadToRam();
	virtual void UnloadFromRam();
	virtual bool LoadToBuffer();
	virtual void UnloadFromBuffer();

	// transform 相关
	void Reset();

	// 更新
	virtual void Update(float deltaTime){};

private:
	void RenderByEffect() const;

private:
	Model3D* m_model;
	D3DXMATRIX m_worldTrans;
	Effect* m_effect;
};
#endif 