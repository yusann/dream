#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//*****************************************************************************
//   2Dオブジェクトクラス定義
//*****************************************************************************
class CObject2D : public CScene2D
{
public:
	CObject2D();             // デフォルトコンストラクタ
	~CObject2D();                             // デストラクタ

	typedef enum
	{
		TYPE_BG_TITLE = 0,
		TYPE_BG_TITLE_SIBA,
		TYPE_BG_TUTORIAL,
		TYPE_BG_RESULTLOSE,
		TYPE_BG_RESULTWIN,
		TYPE_UI_PUSH,
		TYPE_UI_NUM,
		TYPE_MAX
	}TYPE;

	static CObject2D *Create(TYPE Type);                  // 作成
	void Init(TYPE Type);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理

private:
	TYPE m_Type;
	D3DXVECTOR3 m_SclOld;
};

#endif