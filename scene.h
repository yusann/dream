#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
//   シーンクラスの定義
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BACKGROUND,

		OBJTYPE_FIELD,
		OBJTYPE_BLOCK,
		OBJTYPE_SWITCH,
		OBJTYPE_ENEMY,
		OBJTYPE_PLAYER,
		OBJTYPE_BULLET,
		OBJTYPE_SHADOW,
		OBJTYPE_PARTICLE,

		OBJTYPE_UI,
		OBJTYPE_DEBUG_MESH,
		OBJTYPE_FADE,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 3);                        // デフォルトコンストラクタ
	virtual ~CScene();                       // デストラクタ
	
	virtual void Init(void)   =0;      // 初期化処理
	virtual void Uninit(void) =0;      // 終了処理
	virtual void Update(void) =0;      // 更新処理
	virtual void Draw(void)   =0;      // 描画処理
	virtual void DrawDepth(void) = 0;  // 描画処理
	virtual void DrawStencilShadow(void) = 0;  // 描画処理
	virtual void DrawGBuffer(void) = 0;  // 描画処理

	static void UpdateAll(void);                // すべての更新
	static void DrawAll(void);                  // すべての描画
	static void DrawDepthAll(void);                  // すべての描画
	static void DrawStencilShadowAll(void);                  // すべての描画
	static void DrawGBufferAll(void);                  // すべての描画
	static void ReleaseAll(int CntMax = OBJTYPE_MAX);               // すべてのリリース

	static CScene *GetScene(int Priority) { return m_Top[Priority]; }			// シーンの取得処理
	void SetObjType(OBJTYPE ObjType) { m_ObjType = ObjType; }					// シーンタイプの代入処理
	OBJTYPE GetObjType(void) { return m_ObjType; }								// シーンタイプの取得処理

	CScene *SetNextScene(void) { return m_Next; }
	D3DXVECTOR3 GetPos(void) { return m_Pos; }
	D3DXVECTOR3 GetScl(void) { return m_Scl; }

protected:
	void Release(void);                         // リリース処理（子クラスを消してから親クラスを消すため用）
	D3DXVECTOR3             m_Pos;       // 座標
	D3DXVECTOR3             m_Scl;      // サイズ
	D3DXCOLOR               m_Color;    // 色
	LPDIRECT3DTEXTURE9      m_pTexture;  // テクスチャ

private:
	static CScene *m_Top[OBJTYPE_MAX];      // シーンの宣言
	static int m_NumScene;                  // シーンの総数
	CScene *m_Prev;
	CScene *m_Next;
	int m_Priority;
	OBJTYPE m_ObjType;

};

#endif