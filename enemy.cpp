//=============================================================================
// 敵
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "mode.h"
#include "modeGame.h"
#include "scene.h"
#include "sceneModelX.h"
#include "sceneMotionPartsX.h"
#include "sceneBillboard.h"
#include "mode.h"
#include "enemy.h"
#include "player.h"
#include "block.h"
#include "bullet.h"
#include "particle.h"
#include "sceneMesh.h"
#include "meshField.h"
#include "collision.h"
#include "equation.h"
#include "sound.h"
#ifdef _DEBUG
#include "meshSphere.h"
#endif

CEnemy::CEnemy():CSceneMotionPartsX(CScene::OBJTYPE_ENEMY)
{
}

CEnemy::~CEnemy()
{
}

//=======================================================================================
// 作成処理
//=======================================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy *pSceneMD;                            // 変数宣言
	pSceneMD = new CEnemy;                       // 動的確保
	pSceneMD->Init(pos);                            // 初期化
	return pSceneMD;                             // 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CEnemy::Init(D3DXVECTOR3 pos)
{
	m_Mode = MODE_NORMAL;
	m_Pos = pos;
	m_Speed = 0.2f;
	m_life = 3;
	m_CollisionPos = m_Pos;
	m_CollisionScl = 5.0f;
	m_DetectionPos = m_Pos;
	m_DetectionScl = 30.0f;
	m_CheckMode = CEquation::Random(180, 360);
	m_CntFrameNormal = 0;
	m_CntFrameMove = 0;
	m_CntFrameAttack = 0;

	m_pMotionPartsX = CMotionPartsX::GetMotionPartsX(CMotionPartsX::TYPE_ENEMY);
#ifdef _DEBUG
	m_CollisionDebug = CMeshSphere::Create(m_CollisionPos, m_CollisionScl, 10, 10, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.3f));
	m_DetectionDebug = CMeshSphere::Create(m_Pos, m_DetectionScl, 10, 10, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.1f));
#endif

	// 親の初期化
	CSceneMotionPartsX::Init();

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_ENEMY);
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CEnemy::Uninit()
{
#ifdef _DEBUG
	m_CollisionDebug->Uninit();
	m_DetectionDebug->Uninit();
#endif
	CSceneMotionPartsX::Uninit();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CEnemy::Update()
{
	m_Move.y -= 0.2f;
	if (isPlayer())
	{
		m_Mode = MODE_ATTACK;
	}
	else if (m_Mode == MODE_ATTACK)
	{
		m_Mode = MODE_NORMAL;
	}

	switch (m_Mode)
	{
	case MODE_NORMAL:     ModeNormal();     break;
	case MODE_MOVE:       ModeMove();       break;
	case MODE_ATTACK:     ModeAttack();     break;
	default:
		assert("敵モードエラー！");
		break;
	}

	// 移動処理
	m_Pos += m_Move;
	m_Move.x = 0.0f;
	m_Move.z = 0.0f;
	CMeshField *pMeshField = CModeGame::GetMeshField();
	if (pMeshField == NULL) { return; }
	float PosY = pMeshField->GetHeight(m_Pos);
	if (m_Pos.y < PosY)
	{
		m_Move.y = 0.0f;
		m_Pos.y = PosY;
	}

	// 移動できる範囲
	if (m_Pos.x > 550.0f) m_Pos.x = 550.0f;
	if (m_Pos.x < -600.0f) m_Pos.x = -600.0f;
	if (m_Pos.z > 550.0f) m_Pos.z = 550.0f;
	if (m_Pos.z < -600.0f) m_Pos.z = -600.0f;

	CSceneMotionPartsX::SetMotion(m_Mode);
	CSceneMotionPartsX::Update();

	if (m_life <= 0)
	{
		CParticle::SetParticl(CParticle::TYPE_ENEMY_DEATH, m_Pos);
		CManager::GetSound()->Play(CSound::SE_DAMAGE000);
		Uninit();
		return;
	}
	m_CollisionPos = D3DXVECTOR3(m_Pos.x, m_Pos.y + 5.0f, m_Pos.z);
	m_DetectionPos = D3DXVECTOR3(m_Pos.x + (float)cos(-m_Rot.y + D3DXToRadian(-90))*12.0f, m_Pos.y, m_Pos.z + (float)sin(-m_Rot.y + D3DXToRadian(-90))*12.0f);

#ifdef _DEBUG
	m_CollisionDebug->Update(m_CollisionPos, m_CollisionScl);
	m_DetectionDebug->Update(m_DetectionPos, m_DetectionScl);
#endif
	CollisionBlock();
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CEnemy::Draw()
{
	CSceneMotionPartsX::Draw();
}
//=======================================================================================
//   待機モード処理
//=======================================================================================
void CEnemy::ModeNormal()
{
	m_CntFrameNormal++;
	if (m_CntFrameNormal >= m_CheckMode)
	{
		m_Mode = MODE_MOVE;
		m_Rot.y = CEquation::Random(-314, 314)* 0.01f;
		m_CntFrameNormal = 0;
		m_CheckMode = CEquation::Random(240, 400);
	}
}

//=======================================================================================
//   移動モード処理
//=======================================================================================
void CEnemy::ModeMove()
{
	m_CntFrameMove++;
	if (m_CntFrameMove >= m_CheckMode)
	{
		m_Mode = MODE_NORMAL;
		m_CntFrameMove = 0;
		m_CheckMode = CEquation::Random(120, 250);
	}

	m_Move.x = (float)cos(-m_Rot.y + D3DXToRadian(-90))*m_Speed;
	m_Move.z = (float)sin(-m_Rot.y + D3DXToRadian(-90))*m_Speed;
}

//=======================================================================================
//   攻撃モード処理
//=======================================================================================
void CEnemy::ModeAttack()
{
	m_Move.x = (float)cos(-m_Rot.y + D3DXToRadian(-90))*(m_Speed * 2.0f);
	m_Move.z = (float)sin(-m_Rot.y + D3DXToRadian(-90))*(m_Speed * 2.0f);

	// プレイヤーの取得
	CPlayer* pPlayer = CModeGame::GetPlayer();
	if (pPlayer == NULL) { return; }

	COLLISION_SPHERE Collision = pPlayer->GetCollision();

	// プレイヤーとのベクトル
	D3DXVECTOR3 Vector;
	Vector.x = Collision.Pos.x - m_Pos.x;
	Vector.z = Collision.Pos.z - m_Pos.z;
	Vector.y = 0.0f;

	// プレイヤーとの角度
	//m_Rot.y = atan2(Vector.x, Vector.z) + 3.14f;
	float RotY = atan2(Vector.x, Vector.z) + 3.14f;
	if (m_Rot.y - RotY >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
	if (m_Rot.y - RotY < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }

	m_Rot.y += (RotY - m_Rot.y) * 0.1f;
}

//=======================================================================================
//   ダメージ処理
//=======================================================================================
bool CEnemy::Hit(int damage)
{
	m_life -= damage;
	if (m_life <= 0)
	{
		return true;
	}
	return false;
}

//=======================================================================================
//   ブロックとの当たり判定
//=======================================================================================
void CEnemy::CollisionBlock(void)
{
	// シーンの取得
	CScene *pScene;
	pScene = CScene::GetScene(CScene::OBJTYPE_BLOCK);

	// NULLチェック
	while (pScene != NULL)
	{
		// ブロックの宣言
		CBlock *pBlock;
		pBlock = (CBlock*)pScene;
		D3DXVECTOR3 BlockPos = pBlock->GetPos();
		D3DXVECTOR3 BlockScl = pBlock->GetScl();

		// 各辺との差分変数
		float fLenX = 0.0f, fLenZ = 0.0f;

		// 当たり判定フラグ
		bool bCollision = false;

		// 各辺との当たり判定チェック/////////////////////
		// X辺
		bCollision = CCollision::AABB(m_Pos.x,
			BlockPos.x - (BlockScl.x * 0.5f) - m_Scl.x,
			BlockPos.x + (BlockScl.x * 0.5f) + m_Scl.x);
		// 当たってない場合抜く
		if (!bCollision) {
			pScene = pScene->SetNextScene();
			continue;
		};

		// Z辺
		bCollision = CCollision::AABB(m_Pos.z,
			BlockPos.z - (BlockScl.z * 0.5f) - m_Scl.x,
			BlockPos.z + (BlockScl.z * 0.5f) + m_Scl.x);
		// 当たってない場合抜く
		if (!bCollision) {
			pScene = pScene->SetNextScene();
			continue;
		};


		// 各辺との差分計算
		// X辺
		fLenX = CCollision::AABBToPoint(m_Pos.x,
			BlockPos.x - (BlockScl.x * 0.5f) - m_Scl.x,
			BlockPos.x + (BlockScl.x * 0.5f) + m_Scl.x,
			fLenX);

		// Z辺
		fLenZ = CCollision::AABBToPoint(m_Pos.z,
			BlockPos.z - (BlockScl.z * 0.5f) - m_Scl.x,
			BlockPos.z + (BlockScl.z * 0.5f) + m_Scl.x,
			fLenZ);

		// Z辺はX辺よりめり込んだ場合
		if (fabs(fLenZ) > fabs(fLenX)) {

			// X軸を補正する
			m_Pos.x += fLenX;
		}

		// X辺はZ辺よりめり込んだ場合
		if (fabs(fLenX) > fabs(fLenZ)) {

			// Z軸を補正する
			m_Pos.z += fLenZ;
		}

		pScene = pScene->SetNextScene();
	}
}

//=======================================================================================
//   プレイヤー検知処理
//=======================================================================================
bool CEnemy::isPlayer(void)
{
	// プレイヤーの取得
	CPlayer* pPlayer = CModeGame::GetPlayer();
	if (pPlayer == NULL) { return false; }

	COLLISION_SPHERE Collision = pPlayer->GetCollision();

	if (CCollision::Sphere(Collision.Pos, Collision.Scl, m_DetectionPos, m_DetectionScl))
	{
		return true;
	}
	return false;
}

#ifdef _DEBUG
//=======================================================================================
//   デバッグ表示
//=======================================================================================
void CEnemy::ImGui()
{
	std::string ModeName[MODE_MAX];
	ModeName[0] = "NORMAL";
	ModeName[1] = "MOVE";
	ModeName[2] = "ATTACK";
	ImGui::Text("Mode %s", ModeName[m_Mode].c_str());
	ImGui::InputFloat("MoveSpeed", &m_Speed, 0.01f);
	ImGui::InputInt("Life", &m_life);
}
#endif