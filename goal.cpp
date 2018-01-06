//=============================================================================
// �u���b�N
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mode.h"
#include "scene.h"
#include "sceneModelX.h"
#include "goal.h"

CGoal::CGoal() :
	CSceneModelX(CScene::OBJTYPE_BLOCK)
{
}

CGoal::CGoal(D3DXVECTOR3 pos, D3DXVECTOR3 scl) :
	CSceneModelX(CScene::OBJTYPE_BLOCK)
{
	m_Scl = scl;
	m_Pos = pos;
}

CGoal::~CGoal()
{
}

//==============================================================================
//  ��������
//==============================================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl)
{
	CGoal *pSceneMD;                            // �ϐ��錾
	pSceneMD = new CGoal(pos,scl);                       // ���I�m��
	pSceneMD->Init();                            // ������
	return pSceneMD;                             // �l��Ԃ�
}

//==============================================================================
//  ����������
//==============================================================================
void CGoal::Init( void )
{
	m_Model = CModelX::GetModelX(CModelX::TYPE_GOAL);
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// �e�̏�����
	CSceneModelX::Init();


	// �ϊ��s��̐錾
	D3DXMATRIX mtxRot;             // ���[�J����]
	D3DXMATRIX mtxScl;             // ���[�J���X�P�[��
	D3DXMATRIX mtxPos;             // ���[�J�����W
	D3DXMATRIX mtxWorld;           // ���[���h���

								   // ���[�J����]�̑��
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_Rot.y,
		m_Rot.x,
		m_Rot.z);

	// ���[�J���X�P�[���̑��
	D3DXMatrixScaling(&mtxScl,
		m_Scl.x,
		m_Scl.y,
		m_Scl.z);

	// ���[�J�����W�̑��
	D3DXMatrixTranslation(&mtxPos,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z);

	// ���[���h��񏈗�
	D3DXMatrixIdentity(&mtxWorld);                       // ���[���h�̒��g��������
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);   // ���[���h��]�̑��
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);   // ���[���h�X�P�[���̑��
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);   // ���[���h���W�̑��

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_BLOCK);
}

//==============================================================================
//  �I������
//==============================================================================
void CGoal::Uninit( void )
{
	CSceneModelX::Uninit();
}

//==============================================================================
//  �X�V����
//==============================================================================
void CGoal::Update( void )
{
}

//==============================================================================
//  �`�揈��
//==============================================================================
void CGoal::Draw( void )
{
	CSceneModelX::Draw();
}