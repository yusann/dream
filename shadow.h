#ifndef _SHADOW_H_
#define _SHADOW_H_

//*****************************************************************************
//   影クラス定義
//*****************************************************************************
class CShadow : public CScene2D
{
public:
	CShadow();					// デフォルトコンストラクタ
	~CShadow();					// デストラクタ

	static CShadow* Clear();

	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);
	void Draw(void);        // 描画処理
private:
	static CShadow* m_pShadow;

};

#endif