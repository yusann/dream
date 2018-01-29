//=============================================================================
// �p�[�e�B�N������
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

// �G���S��
// ��
#define PARTICLE_ENEMY_DEATH_STAR_NUM			(9)
#define PARTICLE_ENEMY_DEATH_STAR_SIZE			(6.0f)
#define PARTICLE_ENEMY_DEATH_STAR_LIFE			(20)
#define PARTICLE_ENEMY_DEATH_STAR_CHANGETIME	(12)
#define PARTICLE_ENEMY_DEATH_STAR_SPEED			(1.5f)
#define PARTICLE_ENEMY_DEATH_STAR_ROT			(0.2f)
#define PARTICLE_ENEMY_DEATH_STAR_STARTTIME		(10)
// �m�[�}��
#define PARTICLE_ENEMY_DEATH_NORMAL_SIZE		(10.0f)
#define PARTICLE_ENEMY_DEATH_NORMAL_SIZE_MOVE	(2.0f)
#define PARTICLE_ENEMY_DEATH_NORMAL_LIFE		(10)

// �G�_�b�V����
// ��
#define PARTICLE_ENEMY_DASH_STAR_NUM		(2)
#define PARTICLE_ENEMY_DASH_STAR_SIZE		(1.0f)
#define PARTICLE_ENEMY_DASH_STAR_LIFE		(20)
#define PARTICLE_ENEMY_DASH_STAR_CHANGETIME	(16)
#define PARTICLE_ENEMY_DASH_STAR_ROT		(0.2f)
// �m�[�}��
#define PARTICLE_ENEMY_DASH_NORMAL_NUM			(5)
#define PARTICLE_ENEMY_DASH_NORMAL_SIZE			(0.6f)
#define PARTICLE_ENEMY_DASH_NORMAL_SIZE_MOVE	(0.05f)
#define PARTICLE_ENEMY_DASH_NORMAL_LIFE			(10)

// �q�b�g��
// ��
#define PARTICLE_PLAYER_ATTACK_STAR_NUM			(3)
#define PARTICLE_PLAYER_ATTACK_STAR_SIZE		(1.5f)
#define PARTICLE_PLAYER_ATTACK_STAR_LIFE		(30)
#define PARTICLE_PLAYER_ATTACK_STAR_CHANGETIME	(20)
#define PARTICLE_PLAYER_ATTACK_STAR_ROT			(0.2f)
// �m�[�}��
#define PARTICLE_PLAYER_ATTACK_NORMAL_NUM			(5)
#define PARTICLE_PLAYER_ATTACK_NORMAL_SIZE			(1.0f)
#define PARTICLE_PLAYER_ATTACK_NORMAL_SIZE_MOVE		(0.05f)
#define PARTICLE_PLAYER_ATTACK_NORMAL_LIFE			(10)

// �X�C�b�`OFF��
// �m�[�}��
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
//   �Z�b�g����
//=======================================================================================
void CParticle::SetParticl(TYPE type, D3DXVECTOR3 pos)
{
	// �^�C�v���Ƒ��
	switch (type)
	{
		// �G���S��
	case TYPE_ENEMY_DEATH:
		EnemyDeath(type,pos);
		break;

		// �G�_�b�V����
	case TYPE_ENEMY_DASH:
		pos.y -= 5.0f;
		break;

		// �v���C���[�q�b�g��
	case TYPE_PLAYER_HIT:
		break;

		// �v���C���[�q�b�g��
	case TYPE_PLAYER_DISCOVERY:
		break;
		// �v���C���[�q�b�g��
	case TYPE_RUN:
		Run(type, pos);
		break;

	default:
		assert(!"�^�C�v�s��particle::SetParticl(...)");
		break;
	}
}

//=======================================================================================
//   ��������
//=======================================================================================
CParticle *CParticle::Create(TYPE type, OBJTYPE objType, D3DXVECTOR3 pos, D3DXVECTOR3 size,int nLife, float fSpeed, float fAngle, D3DXVECTOR3 sizeMove, float fRot, int nTime, int nChangeTime)
{
	CParticle *pParticle;                            // �ϐ��錾
	pParticle = new CParticle;                       // ���I�m��
	pParticle->Init(type,objType, pos, size,nLife, fSpeed, fAngle,sizeMove,fRot,nTime, nChangeTime);                            // ������
	return pParticle;                             // �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CParticle::Init(TYPE type, OBJTYPE objType, D3DXVECTOR3 pos, D3DXVECTOR3 size,int nLife, float fSpeed, float fAngle, D3DXVECTOR3 sizeMove, float fRot, int nTime, int nChangeTime)
{
	// ���ʕϐ����
	m_type = type;							// �^�C�v
	m_Pos = pos;							// ���W
	m_fSpeed = fSpeed;						// ����
	m_fAngle = fAngle;						// �p�x
	m_sizeMove = sizeMove;					// �T�C�Y�ύX��
	m_fRotMove = fRot;						// ��]��
	m_nLife = nLife;						// ��������
	m_Scl = size;							// �T�C�Y
	m_nTime = nTime;						// �X�^�[�g�^�C��
	m_nChangeTime = nChangeTime;			// �X�V�p�^�[���ύX�^�C��
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F
	m_TexID = 0.0f;
	
	// �e�̏�����
	CSceneBillboard::Init(); 

	// �^�C�v���Ƒ��
	switch (objType)
	{
	// �I�u�W�F�N�g�i�m�[�}���@���j
	case OBJTYPE_NORMAL:
		m_drawType = DRAW_TYPE_BLENDADD;	// �`�惂�[�h
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_PARTICLE00);		// �e�N�X�`��

		break;

	// �I�u�W�F�N�g�i���j
	case OBJTYPE_STAR:
		m_drawType = DRAW_TYPE_NORMAL;		// �`�惂�[�h
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_PARTICLE01);		// �e�N�X�`��

		m_Pos.y += 2.0f;
		m_TexWidth = 4;
		m_TexHeight = 4;
		CSceneBillboard::SetTexID((int)m_TexID);

		break;

		// �I�u�W�F�N�g�i�r�b�N���}�[�N�j
	case OBJTYPE_SURPRISED:
		m_drawType = DRAW_TYPE_NORMAL;		// �`�惂�[�h
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_PARTICLE02);		// �e�N�X�`��
		m_Color.a = 0.0f;
		break;

	case OBJTYPE_SMOKE:
		m_Pos.x += CEquation::Random(-20, 20)*0.1f;
		m_Pos.z += CEquation::Random(-20, 20)*0.1f;
		m_Pos.y += 2.0f;
		m_Rot = CEquation::Random(-314, 314)*0.01f;
		m_drawType = DRAW_TYPE_NORMAL;		// �`�惂�[�h
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_SMOKE);		// �e�N�X�`��
		break;

	default:
		assert(!"�^�C�v�s��particle::Init(...)");
		break;
	}

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_PARTICLE);
}

//=======================================================================================
//   �I������
//=======================================================================================
void CParticle::Uninit()
{
	CSceneBillboard::Uninit();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CParticle::Update()
{
	m_nTime--;
	if (m_nTime <= 0)
	{
		// �^�C���N���A
		m_nTime = 0;

		// ���������炷
		m_nLife--;

		if (m_nLife > m_nChangeTime)
		{
			// �T�C�Y�X�V
			m_Scl -= m_sizeMove;
			// �ړ�����
			m_Pos.x += cos(m_fAngle) * m_fSpeed;
			m_Pos.z += sin(m_fAngle) * m_fSpeed;
			CSceneBillboard::Update();
			CEquation::SetVertexScaleXY(m_pVB_POS, m_Angle, m_Length, m_Rot);
		}
		else
		{
			switch (m_type)
			{
				// �G���S��
			case TYPE_ENEMY_DEATH:
			{
				CEquation::SetVertexScaleXY(m_pVB_POS, m_Angle, m_Length, m_Rot);
				m_Rot += m_fRotMove;
				break;
			}

				// �G�_�b�V����
			case TYPE_ENEMY_DASH:
				break;

				// �v���C���[�q�b�g��
			case TYPE_PLAYER_HIT:
				break;

				// �v���C���[������
			case TYPE_PLAYER_DISCOVERY:
				break;

				// �X�C�b�`OFF��
			case TYPE_SWITCH_OFF:
				break;
			case TYPE_RUN:
				// �T�C�Y�X�V
				m_Scl += m_sizeMove;
				CSceneBillboard::Update();
				CEquation::SetVertexScaleXY(m_pVB_POS, m_Angle, m_Length, m_Rot);
				break;
			}
		}
	}
	// ���C�t���Ȃ��Ȃ���
	if (m_nLife <= 0)
	{
		// �j��
		Uninit();
		return;
	}
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CParticle::Draw()
{
	CSceneBillboard::Draw(CSceneBillboard::NORMAL);
}

//=======================================================================================
//   �G���S���p�[�e�B�N������
//=======================================================================================
void CParticle::EnemyDeath(TYPE type, D3DXVECTOR3 pos)
{
	// ���̐���
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
//   ���鎞�p�[�e�B�N������
//=======================================================================================
void CParticle::Run(TYPE type, D3DXVECTOR3 pos)
{
	// ���̐���
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
