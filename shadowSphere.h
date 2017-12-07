#ifndef _SHADOW_SPHERE_H_
#define _SHADOW_SPHERE_H_

//*****************************************************************************
//   影クラス定義
//*****************************************************************************
class CShadowSphere
{
public:
	CShadowSphere();					// デフォルトコンストラクタ
	CShadowSphere(int numBlockX, int numBlockY,  float radius, D3DXVECTOR3 scl, D3DXCOLOR color, D3DXVECTOR3 pos);		// コンストラクタ
	~CShadowSphere();					// デストラクタ

	// 生成処理
	static CShadowSphere *Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl);
	static CShadowSphere *Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXVECTOR3 pos);
	static CShadowSphere *Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXCOLOR color);

	void Init(void);												// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(const D3DXVECTOR3 pos);								// 更新処理
	void Update(const D3DXVECTOR3 pos, const D3DXVECTOR3 scl);		// スケール更新処理
	void Draw(void);												// 描画処理

private:
	void MakeVex(void);				// 影頂点の設定
	void MakeSphereVex(void);		// スフィア頂点の設定
	void MakeSphereBuff(void);		// スフィアバッファの設定
	void DrawSphere(void);			// スフィア描画処理

	// 影
	LPDIRECT3DVERTEXBUFFER9	m_VtxBuff;		// 頂点バッファ
	D3DXCOLOR				m_Color;		// 色

	// スフィア
	LPDIRECT3DVERTEXBUFFER9	m_SphereVtxBuff;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9	m_SphereIdxBuff;	// インデックスバッファ
	D3DXVECTOR3		m_SpherePos;	// 座標
	D3DXVECTOR3		m_SphereScl;	// スケール
	float	m_SphereRadius;			// 半径
	int		m_SphereNumX;			// 分割数X
	int		m_SphereNumY;			// 分割数Y
	int		m_PolygonNum;			// ポリゴン数
	int		m_VexNum;				// 頂点数
	int		m_IndexNum;				// インデクス数

	LPDIRECT3DVERTEXBUFFER9	m_pVB_POS;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_NORMAL;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_COLOR;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_TEX;
};

#endif