//=============================================================================
// 弾
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "scene.h"
#include "sceneModelX.h"
#include "sceneBillboard.h"
#include "sceneMotionPartsX.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "texture.h"
#include "collision.h"

#define BULLET_LEN  (1.0f)

CBullet::CBullet():CSceneBillboard(CScene::OBJTYPE_BULLET)
{
}

CBullet::~CBullet()
{
}

//==================================================================================================================================================
// 作成処理
//==================================================================================================================================================
CBullet *CBullet::Create(TYPE Type, D3DXVECTOR3 Pos, float Rot)
{
	CBullet *pSceneBI;                            // 変数宣言
	pSceneBI = new CBullet;                       // 動的確保
	pSceneBI->Init(Type, Pos,Rot);                            // 初期化
	return pSceneBI;                             // 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CBullet::Init(TYPE Type, D3DXVECTOR3 Pos, float Rot)
{
	// メンバ変数の初期化
	m_Type = Type;
	m_Pos = Pos;
	m_Scl = D3DXVECTOR3(BULLET_LEN, BULLET_LEN, 0.0f);
	m_Life = 60;
	m_Move = D3DXVECTOR3((float)cos(Rot)* 0.5f, 0.0f, (float)sin(Rot)*0.5f);

	// 親の初期化
	CSceneBillboard::Init();

	// テクスチャセット
	m_pTexture = CTexture::GetTexture((int)CTexture::TEXTYPE_BULLET);

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_BULLET);
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CBullet::Uninit()
{
	CSceneBillboard::Uninit();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CBullet::Update()
{
	m_Life--;
	m_Pos += m_Move;
	if (m_Life <= 0)
	{
		Uninit();
		return;
	}
	// 当たり判定
	switch (m_Type)
	{
	case TYPE_PLAYER:
	{
		// シーンの取得
		CScene *pScene;
		pScene = CScene::GetScene(CScene::OBJTYPE_ENEMY);

		// NULLチェック
		while (pScene != NULL)
		{
			// ブロックの宣言
			CEnemy *pEnemy;
			pEnemy = (CEnemy*)pScene;
			D3DXVECTOR3 EnemyPos = pEnemy->GetCollisionPos();
			float EnemyScl = pEnemy->GetCollisionScl();

			if (CCollision::Sphere(m_Pos, BULLET_LEN, EnemyPos, EnemyScl))
			{
				pEnemy->Hit();
				Uninit();
				return;
			}

			pScene = pScene->SetNextScene();
		}
		break;
	}
	case TYPE_ENEMY:
	{
		// シーンの取得
		CScene *pScene;
		pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER);

		// NULLチェック
		while (pScene != NULL)
		{
			// ブロックの宣言
			CPlayer *pPlayer;
			pPlayer = (CPlayer*)pScene;
			CCollision::SPHERE Collision = pPlayer->GetCollision();

			if (CCollision::Sphere(m_Pos, BULLET_LEN, Collision.Pos, Collision.Scl))
			{
				Uninit();
				return;
			}

			pScene = pScene->SetNextScene();
		}
	}
	default:
		break;
	}
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CBullet::Draw()
{
	CSceneBillboard::Draw( CSceneBillboard::ADD );
}