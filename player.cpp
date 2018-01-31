//=============================================================================
// �v���C���[
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
#include "playerStateDamage.h"

#define MOVE (0.5f)
#define PLAYER_LIFE					(5)
#define PLAYER_MAGIC				(72)
#define PLAYER_JUMP					(1.6f)        // �W�����v��

CPlayer::CPlayer():CSceneMotionPartsX(CScene::OBJTYPE_PLAYER)
{
}

CPlayer::~CPlayer()
{
}

//==================================================================================================================================================
// �쐬����
//==================================================================================================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pSceneMD;			// �ϐ��錾
	pSceneMD = new CPlayer;		// ���I�m��
	pSceneMD->Init(pos);		// ������
	return pSceneMD;			// �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CPlayer::Init(D3DXVECTOR3 pos)
{
	// �ϐ��̏�����
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
	m_isDamage = false;

	m_pMotionPartsX = CMotionPartsX::GetMotionPartsX(CMotionPartsX::TYPE_PLAYER);

#ifdef _DEBUG
	m_Collision.Sphere = CMeshSphere::Create(m_Collision.Pos, m_Collision.Scl, 10, 10, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.3f));
#endif
	
	// �e�̏������i���_�����j
	CSceneMotionPartsX::Init();

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_PLAYER);

	// UI�̐���
	CObject2D::Create(CObject2D::TYPE_UI_LIFEBG);

	// ��Ԃ̐���
	m_pState = new CPlayerStateNormal;
}

//=======================================================================================
//   �I������
//=======================================================================================
void CPlayer::Uninit()
{
	CSceneMotionPartsX::Uninit();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CPlayer::Update()
{
	m_pState->Update(this);

	CSceneMotionPartsX::Update();

	// �u���b�N�̓����蔻��
	m_Collision.Pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + 2.0f, m_Pos.z);
#ifdef _DEBUG
	m_Collision.Sphere->Update(m_Collision.Pos, m_Collision.Scl);
#endif
	m_onBlock = false;
	CollisionBlock();

	// �G�Ƃ̓����蔻��
	CollisionEnemy();

	// ���G���Ԍo��
	static int damageTime = 0;
	if (m_isDamage)
	{
		damageTime++;
		if (damageTime >= 100)
		{
			m_isDamage = false;
			damageTime = 0;
		}
	}

	// ���S
	if (m_Life <= 0) {
		Uninit();
		return;
	}
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CPlayer::Draw()
{
	if (m_isDamage)
	{
		static int i = 0;
		i = i % 10 + 1;
		if (i > 3)
		{
			CSceneMotionPartsX::Draw();
		}
	}
	else
	{
		CSceneMotionPartsX::Draw();
	}
}

void CPlayer::Hit(D3DXVECTOR2 damageVector)
{
	ChangeState(new CPlayerStateDamage(damageVector));
	m_Life --;
	m_isDamage = true;
}

//=======================================================================================
//   �G�Ƃ̓����蔻��
//=======================================================================================
void CPlayer::CollisionEnemy(void)
{
	if (m_isDamage)
		return;
	// �V�[���̎擾
	CScene *pScene;
	pScene = CScene::GetScene(CScene::OBJTYPE_ENEMY);

	// NULL�`�F�b�N
	while (pScene != NULL)
	{
		// �G�̐錾
		CEnemy *pEnemy;
		pEnemy = (CEnemy*)pScene;
		D3DXVECTOR3 EnemyPos = pEnemy->GetCollisionPos();
		float EnemyScl = pEnemy->GetCollisionScl();
		
		if ( CCollision::Sphere( m_Collision.Pos, m_Collision.Scl, EnemyPos, EnemyScl ) )
		{
			Hit(D3DXVECTOR2( m_Pos.x- EnemyPos.x,m_Pos.z-EnemyPos.z));
			return;
		}
		pScene = pScene->SetNextScene();
	}
}

//=======================================================================================
//   �u���b�N�Ƃ̓����蔻��
//=======================================================================================
void CPlayer::CollisionBlock(void)
{
	// �V�[���̎擾
	CScene *pScene;
	pScene = CScene::GetScene(CScene::OBJTYPE_BLOCK);

	// �u���b�N�����I�ʗp
	float blockPosY = 0.0f;

	// NULL�`�F�b�N
	while (pScene != NULL)
	{
		// �u���b�N�̐錾
		CBlock *pBlock;
		pBlock = (CBlock*)pScene;
		D3DXVECTOR3 BlockPos = pBlock->GetPos();
		D3DXVECTOR3 BlockScl = pBlock->GetScl();

		// �e�ӂƂ̍����ϐ�
		float fLenX = 0.0f, fLenZ = 0.0f;

		// �����蔻��t���O
		bool bCollision = false;

		// �e�ӂƂ̓����蔻��`�F�b�N/////////////////////
		// X��
		bCollision = CCollision::AABB(m_Collision.Pos.x,
			BlockPos.x - (BlockScl.x * 0.5f) - m_Collision.Scl,
			BlockPos.x + (BlockScl.x * 0.5f) + m_Collision.Scl);
		// �������ĂȂ��ꍇ
		if (!bCollision)
		{	// ����
			pScene = pScene->SetNextScene(); 
			continue;
		};

		// Z��
		bCollision = CCollision::AABB(m_Collision.Pos.z,
			BlockPos.z - (BlockScl.z * 0.5f) - m_Collision.Scl,
			BlockPos.z + (BlockScl.z * 0.5f) + m_Collision.Scl);
		// �������ĂȂ��ꍇ
		if (!bCollision)
		{	// ����
			pScene = pScene->SetNextScene();
			continue;
		};

		// �u���b�N�̍����v�Z
		float fBlockHeight = BlockPos.y + BlockScl.y;

		float Check = (m_Pos.y - fBlockHeight)*(m_PosOld.y - fBlockHeight);
		
		// �u���b�N�̏�ɂ����
		if (m_Collision.Pos.y > fBlockHeight) { 
			m_onBlock = true;

			if (blockPosY < fBlockHeight)
			{	// ��ԍ����u���b�N�I��
				blockPosY = fBlockHeight;
			}
		}

		// Y��
		bCollision = CCollision::AABB(m_Collision.Pos.y,
			BlockPos.y - m_Collision.Scl,
			BlockPos.y + BlockScl.y + m_Collision.Scl);
		// �������ĂȂ��ꍇ
		if (!bCollision)
		{	// ����
			pScene = pScene->SetNextScene();
			continue;
		};

		// �����̎�
		if (m_Move.y < 0.0f && (m_Collision.Pos.y > fBlockHeight || Check <0.0f))
		{
			// �u���b�N�����̑��
			m_onBlock = true;
			blockPosY = fBlockHeight;

			// ����
			pScene = pScene->SetNextScene();
			continue;
		}

		// �e�ӂƂ̍����v�Z
		// X��
		fLenX = CCollision::AABBToPoint(m_Collision.Pos.x,
			BlockPos.x - (BlockScl.x * 0.5f) - m_Collision.Scl,
			BlockPos.x + (BlockScl.x * 0.5f) + m_Collision.Scl,
			fLenX);

		// Z��
		fLenZ = CCollision::AABBToPoint(m_Collision.Pos.z,
			BlockPos.z - (BlockScl.z * 0.5f) - m_Collision.Scl,
			BlockPos.z + (BlockScl.z * 0.5f) + m_Collision.Scl,
			fLenZ);

		// Z�ӂ�X�ӂ��߂荞�񂾏ꍇ
		if (fabs(fLenZ) > fabs(fLenX))
		{	// X����␳����
			m_Pos.x += fLenX;
		}
		else
		{	// Z����␳����
			m_Pos.z += fLenZ;
		}

		// ����
		pScene = pScene->SetNextScene();
	}
	// �u���b�N�����̑��
	m_FloorPosY = blockPosY;
}

//=======================================================================================
//   �G�ւ̃_���[�W����
//=======================================================================================
void CPlayer::HitEnemy(int Damage)
{
	// ������͈̓Z�b�g
	std::vector<CCollision::SPHERE*> Collision = GetCollisionSphere();
	for (auto it = Collision.begin(); it != Collision.end(); it++)
	{
		// �V�[���̎擾
		CScene *pScene;
		pScene = CScene::GetScene(CScene::OBJTYPE_ENEMY);

		// NULL�`�F�b�N
		while (pScene != NULL)
		{
			// �u���b�N�̐錾
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
//   �ړ����菈��
//=======================================================================================
bool CPlayer::InputKeyMove(D3DXVECTOR3 *pMove, const float speed)
{
	// �L�[��������
	bool bPushKey = false;

	// �J�������擾
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == NULL) { return bPushKey; }
	D3DXVECTOR3 CameraPos = pCamera->GetPosEye();

	// �J�����Ƃ̃x�N�g��
	D3DXVECTOR3 Vector;
	Vector.x = CameraPos.x - m_Pos.x;
	Vector.z = CameraPos.z - m_Pos.z;
	Vector.y = 0.0f;

	// �J�����Ƃ̊p�x
	float Angle = -atan2(Vector.z, Vector.x) + D3DX_PI * 0.5f;

	// �O�i�L�[����
	bool Input_MoveDown = false;
	m_Speed = speed;

	if (CInputKey::InputPlayerMoveStick())
	{
		D3DXVECTOR2 Move = CInputKey::GetAnalogLValue();
		m_Rot.y = atan2(Move.x, Move.y);
		m_Rot.y += Angle;
		pMove->x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		pMove->z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		bPushKey = true;
	}

	// �O�i
	if (CInputKey::InputPlayerMoveU())
	{
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }
		m_Rot.y += (Angle - m_Rot.y)*0.1f;
		pMove->x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		pMove->z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		bPushKey = true;
	}

	// ���
	if (CInputKey::InputPlayerMoveD())
	{
		Angle += D3DX_PI;

		// �߂����[�h�ŉ�
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }

		// �p�x�v�Z
		m_Rot.y += (Angle - m_Rot.y)*0.1f;

		// �O�i�L�[�t���O
		Input_MoveDown = true;
		pMove->x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		pMove->z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		bPushKey = true;
	}

	// ���ړ�
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

	// �E�ړ�
	if (CInputKey::InputPlayerMoveR())
	{
		// �O�i�L�[�������Ă���Ƃ�
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

void CPlayer::DamageMove(const D3DXVECTOR2 Move)
{
	D3DXVECTOR2 move;
	D3DXVec2Normalize(&move, &Move);

	m_Pos.x += move.x*1.5f;
	m_Pos.z += move.y*1.5f;
}

float CPlayer::GetFloorHeight()
{
	// �n�ʔ���
	if (!OnBlock())
	{
		CMeshField *pMeshField = CModeGame::GetMeshField();
		if (pMeshField == NULL) { return m_FloorPosY; }
		m_FloorPosY = pMeshField->GetHeight(m_Pos);
	}
	return m_FloorPosY;
}

//=======================================================================================
//   ��ԕύX����
//=======================================================================================
void CPlayer::ChangeState(CPlayerState* pState)
{
	if (m_pState != NULL)
	{
		delete m_pState;
		m_pState = pState;
	}
}

#ifdef _DEBUG
//=======================================================================================
//   �f�o�b�O�\��
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