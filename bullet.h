#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
//   弾クラス定義
//*****************************************************************************
class CBullet : public CSceneBillboard
{
public:
	CBullet();             // デフォルトコンストラクタ
	~CBullet();                             // デストラクタ

	typedef enum
	{
		TYPE_PLAYER = 0,
		TYPE_ENEMY,
		TYPE_MAX
	}TYPE;

	static CBullet *Create( TYPE Type, D3DXVECTOR3 Pos, float Rot);                  // 作成
	void Init(TYPE Type, D3DXVECTOR3 Pos, float Rot);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理

private:
	TYPE m_Type;
	D3DXVECTOR3 m_Move;
	int m_Life;
};

#endif