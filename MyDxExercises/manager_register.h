#ifndef __MANAGER_REGISTER_H__
#define __MANAGER_REGISTER_H__

#include <vector>

template <typename objT>
class ManagerRegister
{
protected:
	ManagerRegister(){};
	virtual ~ManagerRegister(){};

public:
	virtual void RegisterObject(objT* handler)
	{
		for(auto it = m_vec_objs.begin(); it != m_vec_objs.end(); ++it )
		{
			if( *it == handler )
			{
				return;
			}
		}
		m_vec_objs.push_back(handler);
	}

	virtual void UnRegisterObject(objT* handler)
	{
		for(auto it = m_vec_objs.begin(); it != m_vec_objs.end(); ++it )
		{
			if( *it == handler )
			{
				m_vec_objs.erase(it);
				return;
			}
		}
	}

protected:
	std::vector<objT*> m_vec_objs;
};

#endif