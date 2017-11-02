#ifndef _MODE_H_
#define _MODE_H_

//   前方宣言
class CPlayer;
class CMeshField;
class CSkyBox;

//*****************************************************************************
//   モードクラス定義
//*****************************************************************************
class CMode
{
public:
	virtual void Init(void) = 0;      // 初期化処理
	virtual void Uninit(void) = 0;      // 終了処理
	virtual void Update(void) = 0;      // 更新処理
	virtual void Draw(void) = 0;      // 描画処理
};

// タイトル
class CModeTitle : public CMode
{
private:

public:
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

// ゲーム
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
	void Draw(void);

	static CMeshField *GetMeshField() { return m_pMeshField; }
	static CPlayer *GetPlayer() { return m_pPlayer; }
};

// リザルト
class CModeResult : public CMode
{
private:
	static bool m_Clear;
public:
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetClear(bool Clear);
};

#endif