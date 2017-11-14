#ifndef _SHADOW_H_
#define _SHADOW_H_

//*****************************************************************************
//   影クラス定義
//*****************************************************************************
class CShadow
{
public:
	CShadow();					// デフォルトコンストラクタ
	CShadow(int numBlockX,
			int numBlockY, 
			float radius,
			D3DXVECTOR3 scl,
			D3DXVECTOR3 pos);
	~CShadow();					// デストラクタ

	static CShadow *Create(int numBlockX,
							int numBlockY,
							float radius,
							D3DXVECTOR3 scl,
							D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f));                  // 作成

	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(const D3DXVECTOR3 pos);      // 更新処理
	void Update(const D3DXVECTOR3 pos, const D3DXVECTOR3 scl);      // 更新処理
	void Draw(void);        // 描画処理

private:
	void MakeVex(void);     // 頂点の設定
	void MakeSphereVex(void);     // 頂点の設定
	void MakeSphereBuff(void);    // バッファの設定
	void DrawSphere(void);

	D3DXCOLOR   m_Color;    // 色
	D3DXVECTOR3 m_SpherePos;
	D3DXVECTOR3 m_SphereScl;
	float m_SphereRadius;
	int m_SphereNumX;
	int m_SphereNumY;
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;         // 頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_SphereVtxBuff;    // 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9  m_SphereIdxBuff;     // インデックスバッファ
	int   m_PolygonNum;
	int   m_VexNum;
	int   m_IndexNum;
};

#endif