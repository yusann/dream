//=============================================================================
// プレイヤー
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "mode.h"
#include "modeGame.h"
#include "scene.h"
#include "scene2D.h"
#include "sceneModelX.h"
#include "sceneMotionPartsX.h"
#include "sceneBillboard.h"
#include "sceneMesh.h"

#include "player.h"
#include "enemy.h"
#include "block.h"
#include "bullet.h"
#include "particle.h"
#include "meshField.h"

#include "object2D.h"
#include "camera.h"
#include "light.h"

#include "inputKey.h"
#ifdef _DEBUG
#include "meshSphere.h"
#endif

#include "playerState.h"
#include "playerStateNormal.h"

#define MOVE (0.5f)
#define PLAYER_LIFE					(1000)
#define PLAYER_MAGIC				(72)
#define PLAYER_JUMP					(1.6f)        // ジャンプ力

CPlayer::CPlayer():CSceneMotionPartsX(CScene::OBJTYPE_PLAYER)
{
}

CPlayer::~CPlayer()
{
}

//==================================================================================================================================================
// 作成処理
//==================================================================================================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pSceneMD;			// 変数宣言
	pSceneMD = new CPlayer;		// 動的確保
	pSceneMD->Init(pos);		// 初期化
	return pSceneMD;			// 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CPlayer::Init(D3DXVECTOR3 pos)
{
	// 変数の初期化
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Pos = pos;
	m_Rot.y = 3.14f;
	m_Speed = 0.5f;
	m_Jump = PLAYER_JUMP;
	m_Level = 1;
	m_LifeMax = PLAYER_LIFE;
	m_MagicMax = PLAYER_MAGIC;
	m_Life = m_LifeMax;
	m_Magic = m_MagicMax;
	m_FloorPosY = 0.0f;
	m_Collision.Pos = m_Pos;
	m_Collision.Scl = 2.0f;

	m_pMotionPartsX = CMotionPartsX::GetMotionPartsX(CMotionPartsX::TYPE_PLAYER);

#ifdef _DEBUG
	m_Collision.Sphere = CMeshSphere::Create(m_Collision.Pos, m_Collision.Scl, 10, 10, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.3f));
#endif
	
	// 親の初期化（頂点生成）
	CSceneMotionPartsX::Init();

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_PLAYER);

	// UIの生成
	CObject2D::Create(CObject2D::TYPE_UI_LIFEBG);

	// 状態の生成
	m_pState = new CPlayerStateNormal;
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CPlayer::Uninit()
{
	CSceneMotionPartsX::Uninit();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayer::Update()
{
	/*
	// 座標記憶
	m_PosOld = m_Pos;

	// 重力
	m_Move.y -= PLAYER_GRAVITY;

	// 移動処理
	m_Pos += m_Move;
	m_Move.x = 0.0f;
	m_Move.z = 0.0f;
	m_Collision.Pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + 2.0f, m_Pos.z);
#ifdef _DEBUG
	m_Collision.Sphere->Update(m_Collision.Pos, m_Collision.Scl);
#endif

	// ブロックの当たり判定
	m_onBlock = false;
	CollisionBlock();

	// 地面判定
	if (!m_onBlock)
	{
		CMeshField *pMeshField = CModeGame::GetMeshField();
		if (pMeshField == NULL) { return; }
		m_FloorPosY = pMeshField->GetHeight(m_Pos);
	}
#ifdef _DEBUG
	ImGui::Text("m_FloorPosY %.2f", m_FloorPosY);
#endif // _DEBUG

	// 着地時処理
	if (m_Pos.y < m_FloorPosY && m_Move.y < 0.0f)
	{
		m_Move.y = 0.0f;
		m_Pos.y = m_FloorPosY;
	}

	// 移動できる範囲
	if (m_Pos.x > 550.0f) m_Pos.x = 550.0f;
	if (m_Pos.x < -600.0f) m_Pos.x = -600.0f;
	if (m_Pos.z > 550.0f) m_Pos.z = 550.0f;
	if (m_Pos.z < -600.0f) m_Pos.z = -600.0f;

	// モーションの代入　更新
	CSceneMotionPartsX::SetMotion(0);
	CSceneMotionPartsX::Update();

	// 敵との当たり判定
	CollisionEnemy();

	// 死亡
	if (m_Life <= 0) {
		Uninit();
		return;
	}
	*/
	m_pState->Update(this);

	CSceneMotionPartsX::Update();

	// ブロックの当たり判定
	m_Collision.Pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + 2.0f, m_Pos.z);
#ifdef _DEBUG
	m_Collision.Sphere->Update(m_Collision.Pos, m_Collision.Scl);
#endif
	m_onBlock = false;
	CollisionBlock();

	// 敵との当たり判定
	CollisionEnemy();

	// 死亡
	if (m_Life <= 0) {
		Uninit();
		return;
	}
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CPlayer::Draw()
{
	CSceneMotionPartsX::Draw();
}

/*
//=======================================================================================
//   キー判定処理
//=======================================================================================
void CPlayer::InputKey(void)
{
	// カメラ情報取得
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == NULL) { return; }
	D3DXVECTOR3 CameraPos = pCamera->GetPosEye();

	// カメラとのベクトル
	D3DXVECTOR3 Vector;
	Vector.x = CameraPos.x - m_Pos.x;
	Vector.z = CameraPos.z - m_Pos.z;
	Vector.y = 0.0f;

	// カメラとの角度
	float Angle = -atan2(Vector.z, Vector.x) + D3DX_PI*0.5f;

	// 前進キー判定
	bool Input_MoveDown = false;
	m_Speed = 0.5f;

	if (CInputKey::InputPlayerDash())
	{
		m_Speed = 1.5f;
	}
	if (CInputKey::InputPlayerMove())
	{
		if (m_Mode != MODE_JUMP) m_Mode = MODE_MOVE;
		D3DXVECTOR2 Move = CInputKey::GetAnalogLValue();
		m_Rot.y = atan2(Move.x, Move.y);
		m_Rot.y += Angle;
		m_Move.x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		m_Move.z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
	}

	// 前進
	if (CInputKey::InputPlayerMoveU())
	{
		if (m_Mode != MODE_JUMP) m_Mode = MODE_MOVE;
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }
		m_Rot.y += (Angle - m_Rot.y)*0.1f;
		m_Move.x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		m_Move.z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
	}

	// 後退
	if (CInputKey::InputPlayerMoveD())
	{
		if (m_Mode != MODE_JUMP) m_Mode = MODE_MOVE;
		Angle += D3DX_PI;

		// 近いルードで回す
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }

		// 角度計算
		m_Rot.y += (Angle - m_Rot.y)*0.1f;

		// 前進キーフラグ
		Input_MoveDown = true;
		m_Move.x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		m_Move.z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
	}

	// 左移動
	if (CInputKey::InputPlayerMoveL())
	{
		if (m_Mode != MODE_JUMP) m_Mode = MODE_MOVE;
		if (Input_MoveDown)
		{
			Angle += D3DX_PI*0.5f;
		}
		else
		{
			Angle -= D3DX_PI*0.5f;
		}
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }
		m_Rot.y += (Angle - m_Rot.y)*0.1f;
		m_Move.x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		m_Move.z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
	}

	// 右移動
	if (CInputKey::InputPlayerMoveR())
	{
		if (m_Mode != MODE_JUMP) m_Mode = MODE_MOVE;

		// 前進キーを押しているとき
		if (Input_MoveDown)
		{
			Angle -= D3DX_PI*0.5f;
		}
		else
		{
			Angle += D3DX_PI*0.5f;
		}
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }
		m_Rot.y += (Angle - m_Rot.y)*0.1f;
		m_Move.x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		m_Move.z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
	}

	// 攻撃
	if (CInputKey::InputPlayerAttack())
	{
		m_Mode = MODE_ATTACK;
	}

	// ジャンプ
	if (m_Mode != MODE_JUMP)
	{
		if (CInputKey::InputPlayerJump())
		{
			m_Mode = MODE_JUMP;
			m_Move.y = m_Jump;
		}
	}
	else
	{
		if (CInputKey::InputPlayerJump())
		{
			m_Mode = MODE_JUMPATTACK;
		}
	}
}
*/

//=======================================================================================
//   攻撃モード処理
//=======================================================================================
void CPlayer::ModeAttack()
{
	int Key = GetKey();
	if (Key < 1 )
	{
		m_Move.x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		m_Move.z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
	}
	HitEnemy();

	if (m_LastKye)
	{
		// ニュートラルモード変更
		//m_Mode = MODE_NORMAL;
	}
}

//=======================================================================================
//   ジャンプアタックモード処理
//=======================================================================================
void CPlayer::ModeJumpAttack()
{
	int Key = GetKey();
	int Frame = GetFrame();
	if (Key == 0 && Frame == 1)
	{
		m_Move.y = 1.0f;
	}
	if (Key <= 1) return;
	if (Key == 2)
	{
		m_Move.y = 0.0f;
	}
	else
	{
		m_Move.y -= 0.3f;
	}
	HitEnemy();

	// 着地時処理
	if (m_Pos.y <= m_FloorPosY)
	{
		m_Move.y = 1.0f;
		//m_Mode = MODE_NORMAL;
	}
}

//=======================================================================================
//   敵との当たり判定
//=======================================================================================
void CPlayer::CollisionEnemy(void)
{
	// シーンの取得
	CScene *pScene;
	pScene = CScene::GetScene(CScene::OBJTYPE_ENEMY);

	// NULLチェック
	while (pScene != NULL)
	{
		// 敵の宣言
		CEnemy *pEnemy;
		pEnemy = (CEnemy*)pScene;
		D3DXVECTOR3 EnemyPos = pEnemy->GetCollisionPos();
		float EnemyScl = pEnemy->GetCollisionScl();
		
		if ( CCollision::Sphere( m_Collision.Pos, m_Collision.Scl, EnemyPos, EnemyScl ) )
		{
			Hit(10);
			return;
		}
		pScene = pScene->SetNextScene();
	}
}

//=======================================================================================
//   ブロックとの当たり判定
//=======================================================================================
void CPlayer::CollisionBlock(void)
{
	// シーンの取得
	CScene *pScene;
	pScene = CScene::GetScene(CScene::OBJTYPE_BLOCK);

	// ブロック高さ選別用
	float blockPosY = 0.0f;

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
		bCollision = CCollision::AABB(m_Collision.Pos.x,
			BlockPos.x - (BlockScl.x * 0.5f) - m_Collision.Scl,
			BlockPos.x + (BlockScl.x * 0.5f) + m_Collision.Scl);
		// 当たってない場合
		if (!bCollision)
		{	// 次へ
			pScene = pScene->SetNextScene(); 
			continue;
		};

		// Z辺
		bCollision = CCollision::AABB(m_Collision.Pos.z,
			BlockPos.z - (BlockScl.z * 0.5f) - m_Collision.Scl,
			BlockPos.z + (BlockScl.z * 0.5f) + m_Collision.Scl);
		// 当たってない場合
		if (!bCollision)
		{	// 次へ
			pScene = pScene->SetNextScene();
			continue;
		};

		// ブロックの高さ計算
		float fBlockHeight = BlockPos.y + BlockScl.y;

		float Check = (m_Pos.y - fBlockHeight)*(m_PosOld.y - fBlockHeight);
		
		// ブロックの上にいるよ
		if (m_Collision.Pos.y > fBlockHeight) { 
			m_onBlock = true;

			if (blockPosY < fBlockHeight)
			{	// 一番高いブロック選別
				blockPosY = fBlockHeight;
			}
		}

		// Y辺
		bCollision = CCollision::AABB(m_Collision.Pos.y,
			BlockPos.y - m_Collision.Scl,
			BlockPos.y + BlockScl.y + m_Collision.Scl);
		// 当たってない場合
		if (!bCollision)
		{	// 次へ
			pScene = pScene->SetNextScene();
			continue;
		};

		// 落下の時
		if (m_Move.y < 0.0f && (m_Collision.Pos.y > fBlockHeight || Check <0.0f))
		{
			// ブロック高さの代入
			m_onBlock = true;
			blockPosY = fBlockHeight;

			// 次へ
			pScene = pScene->SetNextScene();
			continue;
		}

		// 各辺との差分計算
		// X辺
		fLenX = CCollision::AABBToPoint(m_Collision.Pos.x,
			BlockPos.x - (BlockScl.x * 0.5f) - m_Collision.Scl,
			BlockPos.x + (BlockScl.x * 0.5f) + m_Collision.Scl,
			fLenX);

		// Z辺
		fLenZ = CCollision::AABBToPoint(m_Collision.Pos.z,
			BlockPos.z - (BlockScl.z * 0.5f) - m_Collision.Scl,
			BlockPos.z + (BlockScl.z * 0.5f) + m_Collision.Scl,
			fLenZ);

		// Z辺はX辺よりめり込んだ場合
		if (fabs(fLenZ) > fabs(fLenX))
		{	// X軸を補正する
			m_Pos.x += fLenX;
		}
		else
		{	// Z軸を補正する
			m_Pos.z += fLenZ;
		}

		// 次へ
		pScene = pScene->SetNextScene();
	}
	// ブロック高さの代入
	m_FloorPosY = blockPosY;
}

//=======================================================================================
//   敵へのダメージ処理
//=======================================================================================
void CPlayer::HitEnemy(int Damage)
{
	// 当たり範囲セット
	std::vector<CCollision::SPHERE*> Collision = GetCollisionSphere();
	for (auto it = Collision.begin(); it != Collision.end(); it++)
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

			if (CCollision::Sphere((*it)->Pos, (*it)->Scl, EnemyPos, EnemyScl))
			{
				pEnemy->Hit(Damage);
				return;
			}
			pScene = pScene->SetNextScene();
		}
	}
}

//=======================================================================================
//   移動判定処理
//=======================================================================================
bool CPlayer::InputKeyMove(D3DXVECTOR3 *pMove)
{
	// キー押し判定
	bool bPushKey = false;

	// カメラ情報取得
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == NULL) { return bPushKey; }
	D3DXVECTOR3 CameraPos = pCamera->GetPosEye();

	// カメラとのベクトル
	D3DXVECTOR3 Vector;
	Vector.x = CameraPos.x - m_Pos.x;
	Vector.z = CameraPos.z - m_Pos.z;
	Vector.y = 0.0f;

	// カメラとの角度
	float Angle = -atan2(Vector.z, Vector.x) + D3DX_PI * 0.5f;

	// 前進キー判定
	bool Input_MoveDown = false;
	m_Speed = 0.5f;

	if (CInputKey::InputPlayerDash())
	{
		m_Speed = 1.5f;
	}
	if (CInputKey::InputPlayerMoveStick())
	{
		D3DXVECTOR2 Move = CInputKey::GetAnalogLValue();
		m_Rot.y = atan2(Move.x, Move.y);
		m_Rot.y += Angle;
		pMove->x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		pMove->z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		bPushKey = true;
	}

	// 前進
	if (CInputKey::InputPlayerMoveU())
	{
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }
		m_Rot.y += (Angle - m_Rot.y)*0.1f;
		pMove->x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		pMove->z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		bPushKey = true;
	}

	// 後退
	if (CInputKey::InputPlayerMoveD())
	{
		Angle += D3DX_PI;

		// 近いルードで回す
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }

		// 角度計算
		m_Rot.y += (Angle - m_Rot.y)*0.1f;

		// 前進キーフラグ
		Input_MoveDown = true;
		pMove->x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		pMove->z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		bPushKey = true;
	}

	// 左移動
	if (CInputKey::InputPlayerMoveL())
	{
		if (Input_MoveDown)
		{
			Angle += D3DX_PI * 0.5f;
		}
		else
		{
			Angle -= D3DX_PI * 0.5f;
		}
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }
		m_Rot.y += (Angle - m_Rot.y)*0.1f;
		pMove->x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		pMove->z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		bPushKey = true;
	}

	// 右移動
	if (CInputKey::InputPlayerMoveR())
	{
		// 前進キーを押しているとき
		if (Input_MoveDown)
		{
			Angle -= D3DX_PI * 0.5f;
		}
		else
		{
			Angle += D3DX_PI * 0.5f;
		}
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }
		m_Rot.y += (Angle - m_Rot.y)*0.1f;
		pMove->x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		pMove->z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		bPushKey = true;
	}
	return bPushKey;
}

//=======================================================================================
//   状態変更処理
//=======================================================================================
void CPlayer::ChangeState(CPlayerState* pState)
{
	delete m_pState;
	m_pState = pState;
}

#ifdef _DEBUG
//=======================================================================================
//   デバッグ表示
//=======================================================================================
void CPlayer::ImGui()
{
	//std::string ModeName[5];
	//ModeName[0] = "NORMAL";
	//ModeName[1] = "MOVE";
	//ModeName[2] = "ATTACK";
	//ModeName[3] = "JUMP";
	//ModeName[4] = "JUMPATTACK";
	//ImGui::Text("Mode %s", ModeName[m_Mode].c_str());
	ImGui::DragFloat3("Pos", &m_Pos[0], 0.01f);
	ImGui::InputInt("Life", &m_Life);
	ImGui::InputFloat("MoveSpeed", &m_Speed, 0.01f);
	ImGui::InputFloat("Jump", &m_Jump, 0.01f);
	ImGui::InputFloat("", &m_Jump, 0.01f);
	
}
#endif