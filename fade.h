#ifndef _FADE_H_
#define _FADE_H_

//   前方宣言
class CMode;

//*****************************************************************************
//   フェードクラス定義
//*****************************************************************************
class CFade : public CScene2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX,
	}FADE;

	CFade();             // デフォルトコンストラクタ
	~CFade();                             // デストラクタ
	
	void Init(D3DXCOLOR color);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理

	static void SetFade(CMode *modeNext, D3DXCOLOR color = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f), FADE fade = FADE_OUT);  // 追加でカラー指定、テクスチャ指定、フェードスピート
	static FADE GetFade(void);                      // フェード状態取得

	static CFade *Create(D3DXCOLOR color);                  // 作成
private:
	static FADE m_fade;
	static CMode *m_pModeNext;
};

#endif