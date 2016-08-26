#ifndef __MODEL_INTERFACE_H__
#define __MODEL_INTERFACE_H__

class ModelInterface
{
public:
	virtual void Render() const = 0;

	virtual bool LoadToRam() = 0;
	virtual void UnloadFromRam() = 0;

	virtual bool LoadToBuffer() = 0;
	virtual void UnloadFromBuffer() = 0;
};
#endif 