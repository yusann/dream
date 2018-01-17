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

	D3DXVECTOR3 GetPos() { return m_PosEye; }
	D3DXVECTOR3 GetDir() { return m_Direction; }
	// ビュー行列取得
	D3DXMATRIX	GetMtxView() { return m_MtxView; }
	// プロジェクション行列取得
	D3DXMATRIX	GetMtxProj() { return m_MtxProj; }
	float		GetFar() { return m_Far; }
	float		GetDepthEpsilon() { return m_DepthEpsilon; }
	float		GetDepthEpsilonScl() { return m_DepthEpsilonScl; }
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }

private:
	D3DXVECTOR3 m_PosEye;		// 座標
	D3DXVECTOR3 m_PosAt;		// 注視点
	D3DXVECTOR3 m_VecUp;		// 上方向
	D3DXVECTOR3 m_Direction;		// 座標

	D3DXMATRIX  m_MtxView;		// ビュー行列
	D3DXMATRIX  m_MtxProj;		// プロジェクション行列
	float       m_Far;
	float		m_DepthEpsilon;
	float		m_DepthEpsilonScl;
	LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif