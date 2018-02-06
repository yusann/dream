#ifndef _PLAYER_STAMINA_H_
#define _PLAYER_STAMINA_H_

//*****************************************************************************
//   2Dオブジェクトクラス定義
//*****************************************************************************
class CPlayerStamina : public CScene2D
{
public:
	CPlayerStamina();             // デフォルトコンストラクタ
	~CPlayerStamina();                             // デストラクタ

	static CPlayerStamina *Create(	const LPDIRECT3DTEXTURE9 pTexture,
								const D3DXVECTOR2 Pos,
								const D3DXVECTOR2 Scl);                  // 作成
	void Init(	const LPDIRECT3DTEXTURE9 pTexture,
				const D3DXVECTOR2 Pos,
				const D3DXVECTOR2 Scl);
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理
	void SetValue(float Value) { m_Value = Value; }

private:
	CScene2D *m_pBG;
	float m_Value;
	bool  m_isDraw;
};

#endif