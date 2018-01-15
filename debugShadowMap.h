#ifndef _DEBUG_SHADOW_MAP_H_
#define _DEBUG_SHADOW_MAP_H_

//*****************************************************************************
//   2Dオブジェクトクラス定義
//*****************************************************************************
class CDebugShadowMap : public CScene2D
{
public:
	CDebugShadowMap();             // デフォルトコンストラクタ
	~CDebugShadowMap();                             // デストラクタ

	static CDebugShadowMap *Create();                  // 作成
	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理
};

#endif