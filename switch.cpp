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
#include "switch.h"

#include "scene2D.h"
#include "shadowModel.h"
#ifdef _DEBUG
#include "meshCube.h"
#endif

CSwitch::CSwitch() :
	CSceneModelX(CScene::OBJTYPE_BLOCK)
{
#ifdef _DEBUG
	m_Collision = NULL;
#endif
}

CSwitch::CSwitch(D3DXVECTOR3 pos, D3DXVECTOR3 scl) :
	CSceneModelX(CScene::OBJTYPE_BLOCK)
{
	m_Scl = scl;
	m_Pos = pos;
}

CSwitch::~CSwitch()
{
}

//==============================================================================
//  ��������
//==============================================================================
CSwitch *CSwitch::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl)
{
	CSwitch *pSceneMD;                            // �ϐ��錾
	pSceneMD = new CSwitch(pos,scl);                       // ���I�m��
	pSceneMD->Init();                            // ������
	return pSceneMD;                             // �l��Ԃ�
}

//==============================================================================
//  ����������
//==============================================================================
void CSwitch::Init( void )
{
	m_Model = CModelX::GetModelX(CModelX::TYPE_BLOCK);
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// �e�̏�����
	CSceneModelX::Init();
#ifdef _DEBUG
	m_Collision = CMeshCube::Create();
#endif

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_SHADOW);
}

//==============================================================================
//  �I������
//==============================================================================
void CSwitch::Uninit( void )
{
	CSceneModelX::Uninit();
}

//==============================================================================
//  �X�V����
//==============================================================================
void CSwitch::Update( void )
{
#ifdef _DEBUG
	m_Collision->Update(m_Pos, m_Scl);
#endif
}

//==============================================================================
//  �`�揈��
//==============================================================================
void CSwitch::Draw( void )
{
	CSceneModelX::Draw();
}

#ifdef _DEBUG
//=======================================================================================
//   �f�o�b�O�\��
//=======================================================================================
void CSwitch::ImGui()
{
	ImGui::DragFloat3("Switch Pos", &m_Pos[0], 0.01f);
	ImGui::DragFloat3("Switch Scl", &m_Scl[0], 0.01f);
}
#endif