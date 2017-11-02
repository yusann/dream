//*****************************************************************************
//   二重定義防止
//*****************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
//   クラスの定義
//*****************************************************************************
// シーンクラス
class CPlayer : public CSceneModelX
{
public:
	CPlayer();             // デフォルトコンストラクタ
	~CPlayer();                             // デストラクタ
	
	// ステータス情報
	typedef struct
	{
		int LifeMax;
		int MagicMax;
		int Life;
		int Magic;
	}STATUS;

	static CPlayer *Create(VECTOR3 pos);                  // 作成
	void Init(VECTOR3 pos);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理

	void Hit(int Damage);
	STATUS GetStatus(void);

private:
	VECTOR3 m_Move;
	int m_Level;
	int m_LifeMax;
	int m_MagicMax;
	int m_Life;
	int m_Magic;
};

#endif