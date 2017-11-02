//*****************************************************************************
//   �C���N���[�h�t�@�C��
//*****************************************************************************
#include "header/main.h"
#include "header/manager.h"
#include "header/mode.h"
#include "header/scene.h"
#include "header/scene2D.h"
#include "header/sceneModelX.h"
#include "header/sceneBillboard.h"
#include "header/player.h"
#include "header/enemy.h"
#include "header/bullet.h"
#include "header/sceneMesh.h"
#include "header/meshField.h"

#include "header/object2D.h"

#include "header/input.h"
#ifdef _DEBUG
#include "header/debug.h"
#endif

#define MOVE (0.5f)
#define PLAYER_LIFE			(253)
#define PLAYER_MAGIC		(72)
//=======================================================================================
//   �R���X�g���N�^
//=======================================================================================
CPlayer::CPlayer():CSceneModelX(CScene::OBJTYPE_PLAYER)
{
}

//=======================================================================================
//   �f�X�g���N�^
//=======================================================================================
CPlayer::~CPlayer()
{
}

//==================================================================================================================================================
// �쐬����
//==================================================================================================================================================
CPlayer *CPlayer::Create(VECTOR3 pos)
{
	CPlayer *pSceneMD;			// �ϐ��錾
	pSceneMD = new CPlayer;		// ���I�m��
	pSceneMD->Init(pos);		// ������
	return pSceneMD;			// �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CPlayer::Init(VECTOR3 pos)
{
	// �ϐ��̏�����
	m_Pos = pos;
	m_Level = 1;
	m_LifeMax = PLAYER_LIFE;
	m_MagicMax = PLAYER_MAGIC;
	m_Life = m_LifeMax;
	m_Magic = m_MagicMax;
	m_model = CModelX::GetModelX(CModelX::TYPE_PLAYER);

	// �e�̏������i���_�����j
	CSceneModelX::Init();

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_PLAYER);

	// UI�̐���
	CObject2D::Create(CObject2D::TYPE_UI_LIFEBG);
	CObject2D::Create(CObject2D::TYPE_UI_MAGICBG);
	CObject2D::Create(CObject2D::TYPE_UI_LIFE);
	CObject2D::Create(CObject2D::TYPE_UI_MAGIC);
}

//=======================================================================================
//   �I������
//=======================================================================================
void CPlayer::Uninit()
{
	CSceneModelX::Uninit();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CPlayer::Update()
{
	// �L�[����
	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_A))
	{
		m_Rot.y -= 0.1f;
		if (m_Rot.y <= -D3DX_PI) {
			m_Rot.y += D3DX_PI * 2;
		}
		m_Move.x = -(float)cos(-m_Rot.y + D3DXToRadian(-90))*0.3f;
		m_Move.z = -(float)sin(-m_Rot.y + D3DXToRadian(-90))*0.3f;
	}
	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_D))
	{
		m_Rot.y += 0.1f;
		if (m_Rot.y >= D3DX_PI) {
			m_Rot.y += -D3DX_PI * 2;
		}
		m_Move.x = -(float)cos(-m_Rot.y + D3DXToRadian(-90))*0.3f;
		m_Move.z = -(float)sin(-m_Rot.y + D3DXToRadian(-90))*0.3f;
	}
	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_W))
	{
		m_Move.x = -(float)cos(-m_Rot.y + D3DXToRadian(-90))*0.5f;
		m_Move.z = -(float)sin(-m_Rot.y + D3DXToRadian(-90))*0.5f;
	}
	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_S))
	{
		m_Move.x = (float)cos(-m_Rot.y + D3DXToRadian(-90))*0.5f;
		m_Move.z = (float)sin(-m_Rot.y + D3DXToRadian(-90))*0.5f;
	}
	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_B))
	{

		CBullet::Create(CBullet::TYPE_PLAYER, VECTOR3(m_Pos.x, m_Pos.y+5.0f, m_Pos.z), -m_Rot.y+(D3DX_PI*0.5f));
	}

	// �ړ�����
	m_Pos += m_Move;
	m_Move.x = 0.0f;
	m_Move.z = 0.0f;
	CMeshField *pMeshField = CModeGame::GetMeshField();
	if (pMeshField == NULL) { return; }
	m_Pos.y = pMeshField->GetHeight(m_Pos);
	if (m_Life <= 0)
	{
		Uninit();
		return;
	}
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CPlayer::Draw()
{
#ifdef _DEBUG
	CDebug::AddText("�v���C���[���W�@�i%.2f, %.2f, %.2f�j\n", m_Pos.x, m_Pos.y, m_Pos.z);
	CDebug::AddText("�v���C���[�����@�i%.2f, %.2f, %.2f�j\n", m_Rot.x, m_Rot.y, m_Rot.z);
	CDebug::AddText("�v���C���[�X�e�[�^�X\n");
	CDebug::AddText("���C�t�F%d/%d\n", m_Life, m_LifeMax);
	CDebug::AddText("�}�W�b�N�F%d/%d\n", m_Magic, m_MagicMax);
#endif
	CSceneModelX::Draw();
}

//=======================================================================================
//   �q�b�g����
//=======================================================================================
void CPlayer::Hit(int Damage)
{
	m_Life -= Damage;
}

//=======================================================================================
//   �X�e�[�^�X�擾����
//=======================================================================================
CPlayer::STATUS CPlayer::GetStatus(void)
{
	STATUS player;
	player.LifeMax = m_LifeMax;
	player.MagicMax = m_MagicMax;
	player.Life = m_Life;
	player.Magic = m_Magic;
	return player;
}