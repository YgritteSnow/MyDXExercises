#ifndef __MODEL_MANAGER_H__
#define __MODEL_MANAGER_H__

#include "model_2d.h"
#include "model_3d.h"
#include "model.h"
#include "model_interface.h"

class ModelManager
{
private:
	ModelManager(){}
	~ModelManager(){}

public:
	static ModelManager* GetModelManager()
	{
		static ModelManager s_modelManager;
		return &s_modelManager;
	}

	void InitModels()
	{
		Model2D* m = new Model2D;
		if( m->LoadToRam() && m->LoadToBuffer() )
			s_vec_models.push_back(m);

		ModelInterface* m2 = new Model;
		if( m2->LoadToRam() && m2->LoadToBuffer() )
			s_vec_models.push_back(m2);
	}

	void RenderModels()
	{
		for(auto it = s_vec_models.begin(); it != s_vec_models.end(); ++it )
		{
			(*it)->Render();
		}
	}

private:
	std::vector<ModelInterface*> s_vec_models;
};
#endif