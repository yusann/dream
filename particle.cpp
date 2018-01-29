//=============================================================================
// パーティクル処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "sceneBillboard.h"
#include "sceneMotionPartsX.h"
#include "particle.h"
#include "texture.h"
#include "equation.h"
#include "camera.h"
#include "mode.h"
#include "player.h"

// 敵死亡時
// 星
#define PARTICLE_ENEMY_DEATH_STAR_NUM			(9)
#define PARTICLE_ENEMY_DEATH_STAR_SIZE			(6.0f)
#define PARTICLE_ENEMY_DEATH_STAR_LIFE			(20)
#define PARTICLE_ENEMY_DEATH_STAR_CHANGETIME	(12)
#define PARTICLE_ENEMY_DEATH_STAR_SPEED			(1.5f)
#define PARTICLE_ENEMY_DEATH_STAR_ROT			(0.2f)
#define PARTICLE_ENEMY_DEATH_STAR_STARTTIME		(10)
// ノーマル
#define PARTICLE_ENEMY_DEATH_NORMAL_SIZE		(10.0f)
#define PARTICLE_ENEMY_DEATH_NORMAL_SIZE_MOVE	(2.0f)
#define PARTICLE_ENEMY_DEATH_NORMAL_LIFE		(10)

// 敵ダッシュ時
// 星
#define PARTICLE_ENEMY_DASH_STAR_NUM		(2)
#define PARTICLE_ENEMY_DASH_STAR_SIZE		(1.0f)
#define PARTICLE_ENEMY_DASH_STAR_LIFE		(20)
#define PARTICLE_ENEMY_DASH_STAR_CHANGETIME	(16)
#define PARTICLE_ENEMY_DASH_STAR_ROT		(0.2f)
// ノーマル
#define PARTICLE_ENEMY_DASH_NORMAL_NUM			(5)
#define PARTICLE_ENEMY_DASH_NORMAL_SIZE			(0.6f)
#define PARTICLE_ENEMY_DASH_NORMAL_SIZE_MOVE	(0.05f)
#define PARTICLE_ENEMY_DASH_NORMAL_LIFE			(10)

// ヒット時
// 星
#define PARTICLE_PLAYER_ATTACK_STAR_NUM			(3)
#define PARTICLE_PLAYER_ATTACK_STAR_SIZE		(1.5f)
#define PARTICLE_PLAYER_ATTACK_STAR_LIFE		(30)
#define PARTICLE_PLAYER_ATTACK_STAR_CHANGETIME	(20)
#define PARTICLE_PLAYER_ATTACK_STAR_ROT			(0.2f)
// ノーマル
#define PARTICLE_PLAYER_ATTACK_NORMAL_NUM			(5)
#define PARTICLE_PLAYER_ATTACK_NORMAL_SIZE			(1.0f)
#define PARTICLE_PLAYER_ATTACK_NORMAL_SIZE_MOVE		(0.05f)
#define PARTICLE_PLAYER_ATTACK_NORMAL_LIFE			(10)

// スイッチOFF時
// ノーマル
#define PARTICLE_SWITCH_OFF_NORMAL_SIZE			(1.0f)
#define PARTICLE_SWITCH_OFF_NORMAL_SIZE_MOVE	(0.01f)
#define PARTICLE_SWITCH_OFF_NORMAL_LIFE			(50)

CParticle::CParticle() :CSceneBillboard(CScene::OBJTYPE_PARTICLE)
{
	m_Rot = 0.0f;
}

CParticle::~CParticle()
{
}

//=======================================================================================
//   セット処理
//=======================================================================================
void CParticle::SetParticl(TYPE type, D3DXVECTOR3 pos)
{
	// タイプごと代入
	switch (type)
	{
		// 敵死亡時
	case TYPE_ENEMY_DEATH:
		EnemyDeath(type,pos);
		break;

		// 敵ダッシュ時
	case TYPE_ENEMY_DASH:
		pos.y -= 5.0f;
		break;

		// プレイヤーヒット時
	case TYPE_PLAYER_HIT:
		break;

		// プレイヤーヒット時
	case TYPE_PLAYER_DISCOVERY:
		break;
		// プレイヤーヒット時
	case TYPE_RUN:
		Run(type, pos);
		break;

	default:
		assert(!"タイプ不正particle::SetParticl(...)");
		break;
	}
}

//=======================================================================================
//   生成処理
//=======================================================================================
CParticle *CParticle::Create(TYPE type, OBJTYPE objType, D3DXVECTOR3 pos, D3DXVECTOR3 size,int nLife, float fSpeed, float fAngle, D3DXVECTOR3 sizeMove, float fRot, int nTime, int nChangeTime)
{
	CParticle *pParticle;                            // 変数宣言
	pParticle = new CParticle;                       // 動的確保
	pParticle->Init(type,objType, pos, size,nLife, fSpeed, fAngle,sizeMove,fRot,nTime, nChangeTime);                            // 初期化
	return pParticle;                             // 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CParticle::Init(TYPE type, OBJTYPE objType, D3DXVECTOR3 pos, D3DXVECTOR3 size,int nLife, float fSpeed, float fAngle, D3DXVECTOR3 sizeMove, float fRot, int nTime, int nChangeTime)
{
	// 共通変数代入
	m_type = type;							// タイプ
	m_Pos = pos;							// 座標
	m_fSpeed = fSpeed;						// 速さ
	m_fAngle = fAngle;						// 角度
	m_sizeMove = sizeMove;					// サイズ変更量
	m_fRotMove = fRot;						// 回転量
	m_nLife = nLife;						// 存続期間
	m_Scl = size;							// サイズ
	m_nTime = nTime;						// スタートタイム
	m_nChangeTime = nChangeTime;			// 更新パターン変更タイム
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 色
	m_TexID = 0.0f;
	
	// 親の初期化
	CSceneBillboard::Init(); 

	// タイプごと代入
	switch (objType)
	{
	// オブジェクト（ノーマル　●）
	case OBJTYPE_NORMAL:
		m_drawType = DRAW_TYPE_BLENDADD;	// 描画モード
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_PARTICLE00);		// テクスチャ

		break;

	// オブジェクト（星）
	case OBJTYPE_STAR:
		m_drawType = DRAW_TYPE_NORMAL;		// 描画モード
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_PARTICLE01);		// テクスチャ

		m_Pos.y += 2.0f;
		m_TexWidth = 4;
		m_TexHeight = 4;
		CSceneBillboard::SetTexID((int)m_TexID);

		break;

		// オブジェクト（ビックリマーク）
	case OBJTYPE_SURPRISED:
		m_drawType = DRAW_TYPE_NORMAL;		// 描画モード
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_PARTICLE02);		// テクスチャ
		m_Color.a = 0.0f;
		break;

	case OBJTYPE_SMOKE:
		m_Pos.x += CEquation::Random(-20, 20)*0.1f;
		m_Pos.z += CEquation::Random(-20, 20)*0.1f;
		m_Pos.y += 2.0f;
		m_Rot = CEquation::Random(-314, 314)*0.01f;
		m_drawType = DRAW_TYPE_NORMAL;		// 描画モード
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_SMOKE);		// テクスチャ
		break;

	default:
		assert(!"タイプ不正particle::Init(...)");
		break;
	}

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_PARTICLE);
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CParticle::Uninit()
{
	CSceneBillboard::Uninit();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CParticle::Update()
{
	m_nTime--;
	if (m_nTime <= 0)
	{
		// タイムクリア
		m_nTime = 0;

		// 寿命を減らす
		m_nLife--;

		if (m_nLife > m_nChangeTime)
		{
			// サイズ更新
			m_Scl -= m_sizeMove;
			// 移動処理
			m_Pos.x += cos(m_fAngle) * m_fSpeed;
			m_Pos.z += sin(m_fAngle) * m_fSpeed;
			CSceneBillboard::Update();
			CEquation::SetVertexScaleXY(m_pVB_POS, m_Angle, m_Length, m_Rot);
		}
		else
		{
			switch (m_type)
			{
				// 敵死亡時
			case TYPE_ENEMY_DEATH:
			{
				CEquation::SetVertexScaleXY(m_pVB_POS, m_Angle, m_Length, m_Rot);
				m_Rot += m_fRotMove;
				break;
			}

				// 敵ダッシュ時
			case TYPE_ENEMY_DASH:
				break;

				// プレイヤーヒット時
			case TYPE_PLAYER_HIT:
				break;

				// プレイヤー発見時
			case TYPE_PLAYER_DISCOVERY:
				break;

				// スイッチOFF時
			case TYPE_SWITCH_OFF:
				break;
			case TYPE_RUN:
				// サイズ更新
				m_Scl += m_sizeMove;
				CSceneBillboard::Update();
				CEquation::SetVertexScaleXY(m_pVB_POS, m_Angle, m_Length, m_Rot);
				break;
			}
		}
	}
	// ライフがなくなった
	if (m_nLife <= 0)
	{
		// 破棄
		Uninit();
		return;
	}
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CParticle::Draw()
{
	CSceneBillboard::Draw(CSceneBillboard::NORMAL);
}

//=======================================================================================
//   敵死亡時パーティクル生成
//=======================================================================================
void CParticle::EnemyDeath(TYPE type, D3DXVECTOR3 pos)
{
	// 星の生成
	for (int i = 0; i < PARTICLE_ENEMY_DEATH_STAR_NUM; i++)
	{
		Create(type, 
			OBJTYPE_STAR,
			pos,
			D3DXVECTOR3(PARTICLE_ENEMY_DEATH_STAR_SIZE, PARTICLE_ENEMY_DEATH_STAR_SIZE,0.0f),
			PARTICLE_ENEMY_DEATH_STAR_LIFE,
			PARTICLE_ENEMY_DEATH_STAR_SPEED,
			(D3DX_PI * 2 / PARTICLE_ENEMY_DEATH_STAR_NUM)*i,
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			PARTICLE_ENEMY_DEATH_STAR_ROT,
			PARTICLE_ENEMY_DEATH_STAR_STARTTIME,
			PARTICLE_ENEMY_DEATH_STAR_CHANGETIME);
	}
}
//=======================================================================================
//   走る時パーティクル生成
//=======================================================================================
void CParticle::Run(TYPE type, D3DXVECTOR3 pos)
{
	// 煙の生成
	Create(type,
		OBJTYPE_SMOKE,
		pos,
		D3DXVECTOR3(3.0f, 3.0f, 0.0f),
		30,
		0.0f,
		0.0f,
		D3DXVECTOR3(-0.2f, -0.2f, 0.0f),
		0.05f,
		0,
		20);
}
