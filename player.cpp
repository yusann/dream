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
#include "shadow.h"

#include "player.h"
#include "enemy.h"
#include "block.h"
#include "bullet.h"
#include "particle.h"
#include "meshField.h"

#include "object2D.h"
#include "camera.h"
#include "collision.h"

#include "inputKey.h"
#ifdef _DEBUG
#include "meshSphere.h"
#endif

#define MOVE (0.5f)
#define PLAYER_LIFE					(1000)
#define PLAYER_MAGIC				(72)
#define PLAYER_JUMP					(1.6f)        // �W�����v��
#define PLAYER_GRAVITY				(0.08f)       // �d��

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
	m_Mode = MODE_NORMAL;
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

	m_Shadow = CShadow::Create(m_Pos, D3DXVECTOR3(4.0f, 4.0f, 1.0f));
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
	m_PosOld = m_Pos;
	// ���[�h�̐؂�ւ�
	if (m_Mode == MODE_MOVE)
	{
		m_Mode = MODE_NORMAL;
	}

	// �L�[����
	InputKey();

	m_Move.y -= PLAYER_GRAVITY;

	switch (m_Mode)
	{
	case MODE_NORMAL:     ModeNormal();     break;
	case MODE_MOVE:       ModeMove();       break;
	case MODE_ATTACK:     ModeAttack();     break;
	case MODE_JUMP:       ModeJump();       break;
	case MODE_JUMPATTACK: ModeJumpAttack(); break;
	default:
		assert("�v���C���[���[�h�G���[�I");
		break;
	}

	// �ړ�����
	m_Pos += m_Move;
	m_Move.x = 0.0f;
	m_Move.z = 0.0f;
	m_Shadow->SetPos(D3DXVECTOR3(m_Pos.x, 0.0f, m_Pos.z));
	m_Collision.Pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + 2.0f, m_Pos.z);
#ifdef _DEBUG
	m_Collision.Sphere->Update(m_Collision.Pos, m_Collision.Scl);
#endif

	// �u���b�N�̓����蔻��
	m_isBlock = false;
	CollisionBlock();

	// �n�ʔ���
	float PosY;
	// �u���b�N�̏�ɂ��鎞
	if (m_FloorPosY > 0.0f)
	{
		PosY = m_FloorPosY;
	}
	else{
		if (m_isBlock)
		{
			PosY = 0.0f;
		}
		else
		{
			CMeshField *pMeshField = CModeGame::GetMeshField();
			if (pMeshField == NULL) { return; }
			PosY = pMeshField->GetHeight(m_Pos);
			m_Shadow->SetPos(D3DXVECTOR3(m_Pos.x, PosY+1.0f, m_Pos.z));
		}
	}

	// ���n������
	if (m_Pos.y < PosY)
	{
		m_Move.y = 0.0f;
		m_Pos.y = PosY;
		m_Shadow->SetPos(m_Pos);
		if (m_Mode != MODE_ATTACK && m_Mode != MODE_MOVE&& m_Mode != MODE_JUMPATTACK)
		{
			m_Mode = MODE_NORMAL;
		}
		if (m_Mode != MODE_JUMPATTACK)
		{
			m_FloorPosY = 0.0f;
		}
	}
	float ShadowScl = m_Pos.y - m_Shadow->GetPos().y;
	m_Shadow->SetScl(ShadowScl*0.05f+1.0f);

	// �ړ��ł���͈�
	if (m_Pos.x > 550.0f) m_Pos.x = 550.0f;
	if (m_Pos.x < -600.0f) m_Pos.x = -600.0f;
	if (m_Pos.z > 550.0f) m_Pos.z = 550.0f;
	if (m_Pos.z < -600.0f) m_Pos.z = -600.0f;

	// ���[�V�����̑���@�X�V
	CSceneMotionPartsX::SetMotion(m_Mode);
	CSceneMotionPartsX::Update();

	// �G�Ƃ̓����蔻��
	CollisionEnemy();

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
	CSceneMotionPartsX::Draw();
}

//=======================================================================================
//   �L�[���菈��
//=======================================================================================
void CPlayer::InputKey(void)
{
	// �����Ԏ����s���Ȃ�
	if (m_Mode == MODE_ATTACK) { return; }
	if (m_Mode == MODE_JUMPATTACK) { return; }

	// �J�������擾
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == NULL) { return; }
	CCamera::CAMERA Camera = pCamera->GetCamera();

	// �J�����Ƃ̃x�N�g��
	D3DXVECTOR3 Vector;
	Vector.x = Camera.posEye.x - m_Pos.x;
	Vector.z = Camera.posEye.z - m_Pos.z;
	Vector.y = 0.0f;

	// �J�����Ƃ̊p�x
	float Angle = -atan2(Vector.z, Vector.x) + D3DX_PI*0.5f;

	// �O�i�L�[����
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

	// �O�i
	if (CInputKey::InputPlayerMoveU())
	{
		if (m_Mode != MODE_JUMP) m_Mode = MODE_MOVE;
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }
		m_Rot.y += (Angle - m_Rot.y)*0.1f;
		m_Move.x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		m_Move.z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
	}

	// ���
	if (CInputKey::InputPlayerMoveD())
	{
		if (m_Mode != MODE_JUMP) m_Mode = MODE_MOVE;
		Angle += D3DX_PI;

		// �߂����[�h�ŉ�
		if (m_Rot.y - Angle >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
		if (m_Rot.y - Angle < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }

		// �p�x�v�Z
		m_Rot.y += (Angle - m_Rot.y)*0.1f;

		// �O�i�L�[�t���O
		Input_MoveDown = true;
		m_Move.x = cosf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
		m_Move.z = sinf(-m_Rot.y + (-3.14f*0.5f))*m_Speed;
	}

	// ���ړ�
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

	// �E�ړ�
	if (CInputKey::InputPlayerMoveR())
	{
		if (m_Mode != MODE_JUMP) m_Mode = MODE_MOVE;

		// �O�i�L�[�������Ă���Ƃ�
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

	// �U��
	if (CInputKey::InputPlayerAttack())
	{
		m_Mode = MODE_ATTACK;
	}

	// �W�����v
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

//=======================================================================================
//   �m�[�}�����[�h����
//=======================================================================================
void CPlayer::ModeNormal()
{

}

//=======================================================================================
//   �ړ����[�h����
//=======================================================================================
void CPlayer::ModeMove()
{
}

//=======================================================================================
//   �U�����[�h����
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
		// �j���[�g�������[�h�ύX
		m_Mode = MODE_NORMAL;
	}
}

//=======================================================================================
//   �W�����v���[�h����
//=======================================================================================
void CPlayer::ModeJump()
{
}

//=======================================================================================
//   �W�����v�A�^�b�N���[�h����
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

	// �n�ʔ���
	float PosY;
	// �u���b�N�̏�ɂ��鎞
	if (m_FloorPosY > 0.0f)
	{
		PosY = m_FloorPosY;
	}
	// �n�ʂɂ��鎞
	else {
		CMeshField *pMeshField = CModeGame::GetMeshField();
		if (pMeshField == NULL) { return; }
		PosY = pMeshField->GetHeight(m_Pos);
	}
	// ���n������
	if (m_Pos.y <= PosY)
	{
		m_Move.y = 1.0f;
		m_Mode = MODE_NORMAL;
	}
}

//=======================================================================================
//   �G�Ƃ̓����蔻��
//=======================================================================================
void CPlayer::CollisionEnemy(void)
{
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
			Hit(10);
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

	// �u���b�N�̍����ϐ�
	float fWorkBlockHeight = 0.0f;

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
		// �������ĂȂ��ꍇ����
		if (!bCollision)
		{
			pScene = pScene->SetNextScene(); 
			continue;
		};

		// Z��
		bCollision = CCollision::AABB(m_Collision.Pos.z,
			BlockPos.z - (BlockScl.z * 0.5f) - m_Collision.Scl,
			BlockPos.z + (BlockScl.z * 0.5f) + m_Collision.Scl);
		// �������ĂȂ��ꍇ����
		if (!bCollision)
		{
			pScene = pScene->SetNextScene();
			continue;
		};

		// �u���b�N�̍����v�Z
		float fBlockHeight = BlockPos.y + BlockScl.y;
		if (fWorkBlockHeight < fBlockHeight && m_Collision.Pos.y > fBlockHeight)
		{
			fWorkBlockHeight = fBlockHeight;
			m_Shadow->SetPos(D3DXVECTOR3(m_Pos.x, fWorkBlockHeight, m_Pos.z));
			m_isBlock = true;
		}

		float Check = (m_Pos.y - fBlockHeight)*(m_PosOld.y - fBlockHeight);

		// Y��
		bCollision = CCollision::AABB(m_Collision.Pos.y,
			BlockPos.y - m_Collision.Scl,
			BlockPos.y + BlockScl.y + m_Collision.Scl);
		// �������ĂȂ��ꍇ����
		if (!bCollision)
		{
			if (Check < 0.0f)
			{
				m_FloorPosY = fBlockHeight;
				// ���������t���O��Ԃ�
				break;
			}
			pScene = pScene->SetNextScene();
			continue;
		};

		// �����̎�
		if (m_Move.y < 0.0f && (m_Collision.Pos.y > fBlockHeight || Check <0.0f))
		{
			m_FloorPosY = fBlockHeight;

			// ���������t���O��Ԃ�
			break;
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
		if (fabs(fLenZ) > fabs(fLenX)) {

			// X����␳����
			m_Pos.x += fLenX;
		}

		// X�ӂ�Z�ӂ��߂荞�񂾏ꍇ
		if (fabs(fLenX) > fabs(fLenZ)) {

			// Z����␳����
			m_Pos.z += fLenZ;
		}

		pScene = pScene->SetNextScene();
	}
}

//=======================================================================================
//   �G�ւ̃_���[�W����
//=======================================================================================
void CPlayer::HitEnemy(int Damage)
{
	// ������͈̓Z�b�g
	std::vector<COLLISION_SPHERE*> Collision = GetCollisionSphere();
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
//   �X�e�[�^�X�擾����
//=======================================================================================
CPlayer::STATUS CPlayer::GetStatus()
{
	STATUS player;
	player.LifeMax = m_LifeMax;
	player.MagicMax = m_MagicMax;
	player.Life = m_Life;
	player.Magic = m_Magic;
	return player;
}

#ifdef _DEBUG
//=======================================================================================
//   �f�o�b�O�\��
//=======================================================================================
void CPlayer::ImGui()
{
	std::string ModeName[MODE_MAX];
	ModeName[0] = "NORMAL";
	ModeName[1] = "MOVE";
	ModeName[2] = "ATTACK";
	ModeName[3] = "JUMP";
	ModeName[4] = "JUMPATTACK";
	ImGui::Text("Mode %s", ModeName[m_Mode].c_str());
	ImGui::DragFloat3("Pos", &m_Pos[0], 0.01f);
	ImGui::InputInt("Life", &m_Life);
	ImGui::InputFloat("MoveSpeed", &m_Speed, 0.01f);
	ImGui::InputFloat("Jump", &m_Jump, 0.01f);
}
#endif