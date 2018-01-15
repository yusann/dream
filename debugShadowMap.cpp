//=============================================================================
// 2D�I�u�W�F�N�g
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "mode.h"
#include "modeGame.h"
#include "scene.h"
#include "scene2D.h"
#include "debugShadowMap.h"
#include "light.h"
#include "texture.h"

CDebugShadowMap::CDebugShadowMap():CScene2D(CScene::OBJTYPE_UI)
{
}

CDebugShadowMap::~CDebugShadowMap()
{
}

//=======================================================================================
// �쐬����
//=======================================================================================
CDebugShadowMap *CDebugShadowMap::Create(){
	CDebugShadowMap *pScene2D;                            // �ϐ��錾
	pScene2D = new CDebugShadowMap;                       // ���I�m��
	pScene2D->Init();                            // ������
	return pScene2D;                             // �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CDebugShadowMap::Init()
{
	// �����o�ϐ��̏�����
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(SCREEN_WIDTH*0.2f, SCREEN_HEIGHT*0.2f, 0.0f);
	m_pTexture = CManager::GetLight()->GetTexture();

	// �e�̏�����
	CScene2D::Init();

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_NONE);
}

//=======================================================================================
//   �I������
//=======================================================================================
void CDebugShadowMap::Uninit()
{
	CScene2D::Uninit();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CDebugShadowMap::Update()
{
	m_pTexture = CManager::GetLight()->GetTexture();
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CDebugShadowMap::Draw()
{
	CScene2D::Draw();
}