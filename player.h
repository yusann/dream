#ifndef _PLAYER_H_
#define _PLAYER_H_

// 前方宣言
#ifdef _DEBUG
class CMeshSphere;
#endif

//*****************************************************************************
//   プレイヤークラス定義
//*****************************************************************************
class CPlayer : public CSceneMotionPartsX
{
public:

	// 状態
	typedef enum
	{
		MODE_NORMAL = 0,
		MODE_MOVE,
		MODE_ATTACK,
		MODE_JUMP,
		MODE_JUMPATTACK,
		MODE_MAX
	}MODE;

	// ステータス情報
	typedef struct
	{
		int LifeMax;
		int MagicMax;
		int Life;
		int Magic;
	}STATUS;

	CPlayer();             // デフォルトコンストラクタ
	~CPlayer();                             // デストラクタ

	static CPlayer *Create(D3DXVECTOR3 pos);                  // 作成
	void Init(D3DXVECTOR3 pos);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理

	STATUS GetStatus(void);
	void Hit(int Damage) { m_Life -= Damage; }
	const COLLISION_SPHERE GetCollision(void) { return m_Collision; }

#ifdef _DEBUG
	void ImGui(void);
#endif

private:
	void InputKey(void);
	void ModeNormal(void);
	void ModeMove(void);
	void ModeAttack(void);
	void ModeJump(void);
	void ModeJumpAttack(void);

	void CollisionEnemy(void);
	void CollisionBlock(void);
	void HitEnemy(int Damage = 1);

	MODE m_Mode;
	D3DXVECTOR3 m_Move;
	D3DXVECTOR3 m_PosOld;
	bool m_isBlock;
	int m_Level;
	int m_LifeMax;
	int m_MagicMax;
	int m_Life;
	int m_Magic;
	float m_FloorPosY;
	COLLISION_SPHERE m_Collision;
};

#endif