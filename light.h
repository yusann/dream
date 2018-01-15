//*****************************************************************************
//   二重定義防止
//*****************************************************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
//   クラスの定義
//*****************************************************************************
// シーンクラス
class CLight
{
public:
	CLight();                                   // デフォルトコンストラクタ
	~CLight();                                  // デストラクタ
	
	void Init(void);                              // 初期化処理
	void Uninit(void);                            // 終了処理
	void Update(void);
	void Set(void);

	D3DXVECTOR3 GetPos() { return m_Light.Position; }
	D3DXVECTOR3 GetDir() { return m_Light.Direction; }
	// ビュー行列取得
	D3DXMATRIX	GetMtxView() { return m_MtxView; }
	// プロジェクション行列取得
	D3DXMATRIX	GetMtxProj() { return m_MtxProj; }
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }

private:
	D3DLIGHT9 m_Light;              // ライト

	D3DXMATRIX  m_MtxView;		// ビュー行列
	D3DXMATRIX  m_MtxProj;		// プロジェクション行列
	LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif