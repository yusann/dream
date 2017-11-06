#ifndef _MODEGAME_H_
#define _MODEGAME_H_

//   前方宣言
class CPlayer;
class CMeshField;
class CSkyBox;

//*****************************************************************************
//   ゲームモードクラス定義
//*****************************************************************************
class CModeGame : public CMode
{
private:
	static CPlayer *m_pPlayer;
	CSkyBox *m_pSkyBox;
	static CMeshField *m_pMeshField;
	void LoadFile(char* FileName);

public:
	void Init(void);
	void Uninit(void);
	void Update(void);

	static CMeshField *GetMeshField() { return m_pMeshField; }
	static CPlayer *GetPlayer() { return m_pPlayer; }
};

#endif