#ifndef __FOR_BACKUP_GAME_UPDATER_UPDATER_H__
#define __FOR_BACKUP_GAME_UPDATER_UPDATER_H__
class I_Updater
{
public:
	virtual void F_OnUpdate() = 0;
};

class C_Updater : public I_Updater
{
public:
	I_Updater* F_GetUpdater();
	void F_OnUpdate();

private:
	C_Updater();
	virtual ~C_Updater();

private:
	unsigned m_u_time;
};
#endif 