//=============================================================================
// �e
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "shadow.h"

CShadow *CShadow::m_pShadow = NULL;

CShadow::CShadow() : CScene2D(CScene::OBJTYPE_SHADOW)
{
}

CShadow::~CShadow()
{
}
CShadow *CShadow::Clear()
{
	if (m_pShadow == NULL)
	{
		m_pShadow = new CShadow;
		m_pShadow->Init();
	}
	return m_pShadow;
}

//==============================================================================
//  ����������
//==============================================================================
void CShadow::Init( void )
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_Color = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	m_pTexture = NULL;

	CScene2D::Init();

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_SHADOW);
}

//==============================================================================
//  �I������
//==============================================================================
void CShadow::Uninit( void )
{
	CScene2D::Uninit();
}

//==============================================================================
//  �X�V����
//==============================================================================
void CShadow::Update( void )
{
}

//==============================================================================
//  �`�揈��
//==============================================================================
void CShadow::Draw( void )
{
	return;
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �X�e���V���l��1�ȏ�Ȃ�e�𔼓����ŕ`��
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
		D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
		D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	CScene2D::Draw();

	// �`��X�e�[�^�X�̕��A
	pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}
