#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//*****************************************************************************
//   パーティクルクラス定義
//*****************************************************************************
class CParticle : public CSceneBillboard
{
public:
	// パーティクルタイプ
	typedef enum
	{
		TYPE_ENEMY_DEATH = 0,		// 敵死亡
		TYPE_ENEMY_DASH,			// 敵ダッシュ
		TYPE_PLAYER_HIT,			// ヒット
		TYPE_PLAYER_DISCOVERY,		// ヒット
		TYPE_RUN,					// 走る
		TYPE_SWITCH_OFF,			// スイッチOFF
		TYPE_MAX					// 最大数
	}TYPE;

	// オブジェクトタイプ
	typedef enum
	{
		OBJTYPE_NORMAL,			// 丸
		OBJTYPE_STAR,			// 星
		OBJTYPE_SMOKE,			// 
		OBJTYPE_SURPRISED,		// ビックリマーク
		OBJTYPE_MAX				// 最大数
	}OBJTYPE;

	CParticle();             // デフォルトコンストラクタ
	~CParticle();            // デストラクタ

	// パーティクルのセット
	static void SetParticl(TYPE type, D3DXVECTOR3 pos);

	// 初期化処理
	void Init(TYPE type, 
			OBJTYPE objType,
			D3DXVECTOR3 pos,
			D3DXVECTOR3 size,
			int nLife,
			float fSpeed,
			float fAngle,
			D3DXVECTOR3 sizeMove,
			float fRot,
			int nTime,
			int nChangeTime);
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理

private:
	// 描画タイプ
	typedef enum
	{
		DRAW_TYPE_NORMAL = 0,		// 通常
		DRAW_TYPE_BLENDADD,			// 加算合成
		DRAW_TYPE_MAX				// 最大数
	}DRAW_TYPE;

	// 作成
	static CParticle *Create(TYPE type,
							OBJTYPE objType,
							D3DXVECTOR3 pos,
							D3DXVECTOR3 size, 
							int nLife,
							float fSpeed = 0.0f,
							float fAngle = 0.0f,
							D3DXVECTOR3 sizeMove =D3DXVECTOR3(0.0f,0.0f,0.0f),
							float fRot = 0.0f,
							int nTime = 0,
							int nChangeTime = 0);

	// パーティクルタイプ
	static void EnemyDeath(TYPE type, D3DXVECTOR3 pos);
	static void Run(TYPE type, D3DXVECTOR3 pos);

	TYPE					m_type;
	DRAW_TYPE				m_drawType;					// 描画タイプ
	float					m_fAngle;					// 飛ばす角度
	float					m_fSpeed;					// 速度
	float					m_Rot;
	D3DXVECTOR3				m_sizeMove;					// サイズ変化量
	float					m_TexID;
	float					m_fRotMove;					// 回転量
	int						m_nLife;					// ライフ
	int						m_nVector;					// 方向
	int						m_nTime;					// スタートタイム
	int						m_nChangeTime;				// スタートタイム
};

#endif