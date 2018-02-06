#ifndef _PLAYER_LIFE_H_
#define _PLAYER_LIFE_H_

//*****************************************************************************
//   2Dオブジェクトクラス定義
//*****************************************************************************
class CPlayerLife : public CScene2D
{
public:
	CPlayerLife();             // デフォルトコンストラクタ
	~CPlayerLife();                             // デストラクタ

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_IN,
		TYPE_OUT,
		TYPE_MAX
	}TYPE;

	static CPlayerLife *Create(	const LPDIRECT3DTEXTURE9 pTexture,
								const D3DXVECTOR2 Pos,
								const D3DXVECTOR2 Scl,
								const int Num);                  // 作成
	void Init(	const LPDIRECT3DTEXTURE9 pTexture,
				const D3DXVECTOR2 Pos,
				const D3DXVECTOR2 Scl,
				const int Num);
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理
	void ChangeNum(int NextNum);

private:
	CScene2D *m_pLifeIcon;
	TYPE m_Type;
	int m_Num;
	D3DXVECTOR3 m_PosOld;
};

#endif