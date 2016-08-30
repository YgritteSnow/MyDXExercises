#ifndef __TIMER_MANAGER_H__
#define __TIMER_MANAGER_H__

#include <vector>
#include <time.h>
#pragma comment(lib, "winmm.lib")

#include "manager_register.h"

class TimerObject
{
	virtual void Update(float deltaTime) = 0;
};

class TimerManager : public ManagerRegister<TimerObject>
{
private:
	TimerManager(){};
	virtual ~TimerManager(){};

public:
	static TimerManager* GetTimerManager(){
		static TimerManager t_timerManager;
		return &t_timerManager;
	}

	const float GetCurTime() const{
		return static_cast<float>( timeGetTime() * 0.001f );
	}

	void Update();

private:
	std::vector<TimerObject*> m_vec_timerObjs;
};
#endif