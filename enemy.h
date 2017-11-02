#ifndef _ENEMY_H_
#define _ENEMY_H_

// 前方宣言
class CShadow;
#ifdef _DEBUG
class CMeshSphere;
#endif

//*****************************************************************************
//   敵クラスの定義
//*****************************************************************************
class CEnemy : public CSceneMotionPartsX
{
public:
	// 状態
	typedef enum
	{
		MODE_NORMAL = 0,
		MODE_MOVE,
		MODE_ATTACK,
		MODE_MAX
	}MODE;

	CEnemy();             // デフォルトコンストラクタ
	~CEnemy();                             // デストラクタ
	
	void Init(D3DXVECTOR3 pos);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理

	static CEnemy *Create(D3DXVECTOR3 pos);                  // 作成
	D3DXVECTOR3 GetCollisionPos(void) { return m_CollisionPos; }
	float GetCollisionScl(void) { return m_CollisionScl; }
	bool Hit(int damage = 1);
#ifdef _DEBUG
	void ImGui(void);
#endif

private:
	void ModeNormal(void);
	void ModeMove(void);
	void ModeAttack(void);

	void CollisionBlock(void);
	bool isPlayer(void);

	MODE m_Mode;
	D3DXVECTOR3 m_Move;
	int m_life;
	int m_CheckMode;
	int m_CntFrameNormal;
	int m_CntFrameMove;
	int m_CntFrameAttack;

	CShadow* m_Shadow;

	D3DXVECTOR3 m_CollisionPos;
	float m_CollisionScl;
	D3DXVECTOR3 m_DetectionPos;
	float m_DetectionScl;

#ifdef _DEBUG
	CMeshSphere* m_CollisionDebug;
	CMeshSphere* m_DetectionDebug;
#endif
};

#endif