#ifndef _PLYAER_UI_MANAGER_H_
#define _PLYAER_UI_MANAGER_H_

class CScene2D;

//*****************************************************************************
//   ÉNÉâÉXÇÃíËã`
//*****************************************************************************
class CPlayerUIManager
{
public:
	CPlayerUIManager() : m_pLife(NULL),
						 m_pStamina(NULL) {};
	~CPlayerUIManager() {};
	static CPlayerUIManager *Create(int LifeMax);                  // çÏê¨
	void Init(int LifeMax);
	void Uninit(void);

	void SetLife(int Life);
	void SetStamina(float Stamina);
	void SpinAdd(void);
	void SpinSub(void);
private:
	CScene2D* m_pLife;
	CScene2D* m_pStamina;
};

#endif