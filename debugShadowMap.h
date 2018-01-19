#ifndef _DEBUG_SHADOW_MAP_H_
#define _DEBUG_SHADOW_MAP_H_

//*****************************************************************************
//   2Dオブジェクトクラス定義
//*****************************************************************************
class CDebugShadowMap
{
public:
	CDebugShadowMap();             // デフォルトコンストラクタ
	~CDebugShadowMap() {}                             // デストラクタ

	static CDebugShadowMap *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl);                  // 作成
	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 scl);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(LPDIRECT3DTEXTURE9 pTexture);      // 更新処理
	void Draw(void);        // 描画処理

	static void DrawAll(void);
	static void UninitAll(void);

private:
	void MakeVex(void);     // 頂点の設定

	LPDIRECT3DVERTEXBUFFER9 m_pVB;  // 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Scl;
	static std::vector<CDebugShadowMap*> m_Debug;
};

#endif