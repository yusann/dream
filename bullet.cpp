//=============================================================================
// �e
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
// �쐬����
//==================================================================================================================================================
CBullet *CBullet::Create(TYPE Type, D3DXVECTOR3 Pos, float Rot)
{
	CBullet *pSceneBI;                            // �ϐ��錾
	pSceneBI = new CBullet;                       // ���I�m��
	pSceneBI->Init(Type, Pos,Rot);                            // ������
	return pSceneBI;                             // �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CBullet::Init(TYPE Type, D3DXVECTOR3 Pos, float Rot)
{
	// �����o�ϐ��̏�����
	m_Type = Type;
	m_Pos = Pos;
	m_Scl = D3DXVECTOR3(BULLET_LEN, BULLET_LEN, 0.0f);
	m_Life = 60;
	m_Move = D3DXVECTOR3((float)cos(Rot)* 0.5f, 0.0f, (float)sin(Rot)*0.5f);

	// �e�̏�����
	CSceneBillboard::Init();

	// �e�N�X�`���Z�b�g
	m_pTexture = CTexture::GetTexture((int)CTexture::TEXTYPE_BULLET);

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_BULLET);
}

//=======================================================================================
//   �I������
//=======================================================================================
void CBullet::Uninit()
{
	CSceneBillboard::Uninit();
}

//=======================================================================================
//   �X�V����
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
	// �����蔻��
	switch (m_Type)
	{
	case TYPE_PLAYER:
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
		// �V�[���̎擾
		CScene *pScene;
		pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER);

		// NULL�`�F�b�N
		while (pScene != NULL)
		{
			// �u���b�N�̐錾
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
//   �`�揈��
//=======================================================================================
void CBullet::Draw()
{
	CSceneBillboard::Draw( CSceneBillboard::ADD );
}