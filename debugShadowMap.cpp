//=============================================================================
// 2D�I�u�W�F�N�g
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "GBuffer.h"
#include "mode.h"
#include "modeGame.h"
#include "scene.h"
#include "scene2D.h"
#include "debugShadowMap.h"
#include "light.h"
#include "texture.h"


std::vector<CDebugShadowMap*> CDebugShadowMap::m_Debug;

CDebugShadowMap::CDebugShadowMap():
	m_Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_Scl(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pTexture(NULL),
	m_pVB(NULL){}

//=======================================================================================
// �쐬����
//=======================================================================================
CDebugShadowMap *CDebugShadowMap::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl){
	CDebugShadowMap *pScene2D;                            // �ϐ��錾
	pScene2D = new CDebugShadowMap;                       // ���I�m��
	pScene2D->Init(pos,scl);                            // ������
	m_Debug.push_back(pScene2D);
	return pScene2D;                             // �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CDebugShadowMap::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scl)
{
	// �����o�ϐ��̏�����
	m_Pos = pos;
	m_Scl = scl;
	m_pTexture = NULL;
	MakeVex();
}

//=======================================================================================
//   �I������
//=======================================================================================
void CDebugShadowMap::Uninit()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pTexture);
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CDebugShadowMap::Update(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CDebugShadowMap::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�̃f�N�����[�V�����̐ݒ�
	CVertexDecl::SetTex2D(pDevice, m_pVB);

	// �`�撼�O�Ƀe�N�X�`�����Z�b�g�i�e�N�X�`���̐ݒ�j
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,        // �v���~�e�B�u�̎��
		0,                          // �I�t�Z�b�g�i���_���j
		NUM_POLYGON);              // �v���~�e�B�u�̐��i�|���S���̐��j
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CDebugShadowMap::DrawAll()
{
	for (int i = 0; i < (signed)m_Debug.size(); i++)
	{
		m_Debug[i]->Draw();
	}
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CDebugShadowMap::UninitAll()
{
	for (int i = 0; i < (signed)m_Debug.size(); i++)
	{
		m_Debug[i]->Uninit();
	}
	m_Debug.clear();
}

//=======================================================================================
// �|���S���̒��_�ݒ�
//=======================================================================================
void CDebugShadowMap::MakeVex(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX2D) * NUM_VERTEX,           // �쐬���������_�o�b�t�@�̃T�C�Y�i��̒��_*���_���j
		D3DUSAGE_WRITEONLY,                         // �������ނ������Ȃ��i�`�F�b�N���Ȃ��j
		0,                              // �ǂ�Ȓ��_�ŏ����́i0�ɂ��Ă�OK�j
		D3DPOOL_MANAGED,                            // �������Ǘ������C���ɂ���
		&m_pVB,
		NULL);

	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�i 2D���W�E�E��� �j
	pVtx[0].pos = D3DXVECTOR4(m_Pos.x, m_Pos.y, 0.0f, 1.0f);                 // ����̍��W
	pVtx[1].pos = D3DXVECTOR4(m_Pos.x + m_Scl.x, m_Pos.y, 0.0f, 1.0f);                 // �E��̍��W
	pVtx[2].pos = D3DXVECTOR4(m_Pos.x, m_Pos.y + m_Scl.y, 0.0f, 1.0f);                 // �����̍��W
	pVtx[3].pos = D3DXVECTOR4(m_Pos.x + m_Scl.x, m_Pos.y + m_Scl.y, 0.0f, 1.0f);                 // �E���̍��W

	// ���_�J���[�̐ݒ�i0~255�̐����l�j
	pVtx[0].color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);  // ����̐F
	pVtx[1].color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);  // �E��̐F
	pVtx[2].color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);  // �����̐F
	pVtx[3].color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);  // �E���̐F

	// ���_�f�[�^��UV�f�[�^�̒ǉ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);                    // �����UV���W
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);                    // �E���UV���W
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);                    // ������UV���W
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);                    // �E����UV���W

	// �����J����
	m_pVB->Unlock();
}
