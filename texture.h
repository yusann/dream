#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
//   テクスチャリソースクラスの定義
//*****************************************************************************
class CTexture
{
public:

	typedef enum
	{
		TEXTYPE_WHITE = 0,
		TEXTYPE_FIELD,
		TEXTYPE_PLAYER,
		TEXTYPE_BULLET,

		TEXTYPE_SKY000,
		TEXTYPE_TITLEBG,
		TEXTYPE_TITLELOGO,
		TEXTYPE_TUTORIALBG,
		TEXTYPE_RESULTWINBG,
		TEXTYPE_RESULTLOSTBG,
		TEXTYPE_PUSHSTART,

		TEXTYPE_PARTICLE00,
		TEXTYPE_PARTICLE01,
		TEXTYPE_PARTICLE02,

		TEXTYPE_UI_LIFE,
		TEXTYPE_UI_MAGIC,
		TEXTYPE_UI_GAGEBG,
		TEXTYPE_UI_NUM,

		TEXTYPE_MAX
	}TEXTYPE;
	CTexture();                                   // デフォルトコンストラクタ
	~CTexture();                                  // デストラクタ
	
	static void Init(void);                              // 初期化処理
	static void Uninit(void);                            // 終了処理

	static LPDIRECT3DTEXTURE9 GetTexture(int nNo);		// テクスチャの取得

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEXTYPE_MAX];		// テクスチャ
	static char m_TexName[TEXTYPE_MAX][128];				// テクスチャパス
};

#endif