#include "game/updater/updater.h"

C_Updater::C_Updater()
	: m_u_time(0)
{

}

C_Updater::~C_Updater()
{

}

I_Updater* C_Updater::F_GetUpdater()
{
	static C_Updater t_Updater;
	return &t_Updater;
}

void C_Updater::F_OnUpdate()
{
}