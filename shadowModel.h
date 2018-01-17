#ifndef _SHADOW_MODEL_H_
#define _SHADOW_MODEL_H_

//*****************************************************************************
//   影クラス定義
//*****************************************************************************
class CShadowModel : public CScene2D
{
public:
	CShadowModel();					// デフォルトコンストラクタ
	~CShadowModel();					// デストラクタ

	static CShadowModel *Create();                  // 作成

	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);
	void Draw(void);        // 描画処理
};

#endif