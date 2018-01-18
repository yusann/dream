//=============================================================================
// �e
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "shadowModel.h"
#include "light.h"

CShadowModel::CShadowModel() : CScene2D(CScene::OBJTYPE_SHADOW)
{
}

CShadowModel::~CShadowModel()
{
}

//==============================================================================
//  ��������
//==============================================================================
CShadowModel *CShadowModel::Create()
{
	CShadowModel *pSceneMD;                            // �ϐ��錾
	pSceneMD = new CShadowModel();
	pSceneMD->Init();                            // ������
	return pSceneMD;                             // �l��Ԃ�
}

//==============================================================================
//  ����������
//==============================================================================
void CShadowModel::Init( void )
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
void CShadowModel::Uninit( void )
{
	CScene2D::Uninit();
}

//==============================================================================
//  �X�V����
//==============================================================================
void CShadowModel::Update( void )
{
}

//==============================================================================
//  �`�揈��
//==============================================================================
void CShadowModel::Draw( void )
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �X�e���V���̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);			// �X�e���V���L����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// Z�o�b�t�@�������܂Ȃ�
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);			// �J���[�������܂Ȃ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0x000000ff);		// �X�e���V���}�X�N

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);	// ��r�֐��i�K�����i�j
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);				// �Q�ƒl
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Z�o�b�t�@�ň��������������i�������Ȃ��j
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// �����_�����������i�������Ȃ��j

	// �V���h�E�{�����[���̕\���X�e���V���ɕ`��
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);		// �����ɒʂ������i+1�j
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	DrawStencilShadowAll();

	// �V���h�E�{�����[���̗����X�e���V���ɕ`��
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);		// �����ɒʂ������i-1�j
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	
	DrawStencilShadowAll();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);			// �J���[�������މ\
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);				// �Q�ƒl
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);	// ��r�֐��i�ȉ��Ȃ�j

	//CScene2D::Draw();

	// �`��X�e�[�^�X�̕��A
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}
