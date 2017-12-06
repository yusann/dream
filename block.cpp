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
#include "sceneMotionPartsX.h"
#include "sceneBillboard.h"
#include "sceneMesh.h"
#include "block.h"

#include "scene2D.h"
#include "shadowModel.h"
#ifdef _DEBUG
#include "meshCube.h"
#endif

CBlock::CBlock() :
	CSceneModelX(CScene::OBJTYPE_BLOCK),
	m_pShadow(NULL)
{
#ifdef _DEBUG
	m_Collision = NULL;
#endif
}

CBlock::CBlock(D3DXVECTOR3 pos, D3DXVECTOR3 scl) :
	CSceneModelX(CScene::OBJTYPE_BLOCK),
	m_pShadow(NULL)
{
	m_Scl = scl;
	m_Pos = pos;
}

CBlock::~CBlock()
{
}

//==============================================================================
//  ��������
//==============================================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl)
{
	CBlock *pSceneMD;                            // �ϐ��錾
	pSceneMD = new CBlock(pos,scl);                       // ���I�m��
	pSceneMD->Init();                            // ������
	return pSceneMD;                             // �l��Ԃ�
}

//==============================================================================
//  ����������
//==============================================================================
void CBlock::Init( void )
{
	m_Model = CModelX::GetModelX(CModelX::TYPE_BLOCK);
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// �e�̏�����
	CSceneModelX::Init();
	m_pShadow = CShadowModel::Create(m_Model.pMesh);


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
	m_pShadow->SetMatrix(mtxWorld);
#ifdef _DEBUG
	m_Collision = CMeshCube::Create();
#endif

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_BLOCK);
}

//==============================================================================
//  �I������
//==============================================================================
void CBlock::Uninit( void )
{
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}
	CSceneModelX::Uninit();
}

//==============================================================================
//  �X�V����
//==============================================================================
void CBlock::Update( void )
{
#ifdef _DEBUG
	m_Collision->Update(m_Pos, m_Scl);
#endif
}

//==============================================================================
//  �`�揈��
//==============================================================================
void CBlock::Draw( void )
{
	CSceneModelX::Draw();
}

#ifdef _DEBUG
//=======================================================================================
//   �f�o�b�O�\��
//=======================================================================================
void CBlock::ImGui()
{
	ImGui::DragFloat3("Pos", &m_Pos[0], 0.01f);
	ImGui::DragFloat3("Scl", &m_Scl[0], 0.01f);
}
#endif