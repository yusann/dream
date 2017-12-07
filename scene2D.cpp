//=============================================================================
// 2D����
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"

//*************
// ���C������
//*************
CScene2D::CScene2D(int Priority) :CScene(Priority)
{
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

CScene2D::~CScene2D()
{
}

//=======================================================================================
//   ����������
//=======================================================================================
void CScene2D::Init()
{
	// ���_�ݒ�
	MakeVex();
}

//=======================================================================================
//   �I������
//=======================================================================================
void CScene2D::Uninit()
{
	SAFE_RELEASE( m_pVtxBuff );      // ���_�o�b�t�@�̔j��
	CScene::Release();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CScene2D::Update()
{
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CScene2D::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�̃f�N�����[�V�����̐ݒ�
	LPDIRECT3DVERTEXDECLARATION9 pDecl = *CVertexDecl::Get(CVertexDecl::TYPE_2D);
	pDevice->SetVertexDeclaration(pDecl);

	// �X�g���[���Ƃ��Ē��_�o�b�t�@��ݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CVertexDecl::VERTEX2D));

	// �`�撼�O�Ƀe�N�X�`�����Z�b�g�i�e�N�X�`���̐ݒ�j
	pDevice->SetTexture( 0, m_pTexture );

	// �|���S���̕`��
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,        // �v���~�e�B�u�̎��
							0,                          // �I�t�Z�b�g�i���_���j
							NUM_POLYGON );              // �v���~�e�B�u�̐��i�|���S���̐��j
}

//=======================================================================================
// �|���S���̒��_�ݒ�
//=======================================================================================
void CScene2D::MakeVex(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer( sizeof( CVertexDecl::VERTEX2D ) * NUM_VERTEX,           // �쐬���������_�o�b�t�@�̃T�C�Y�i��̒��_*���_���j
								 D3DUSAGE_WRITEONLY,                         // �������ނ������Ȃ��i�`�F�b�N���Ȃ��j
								 0,                              // �ǂ�Ȓ��_�ŏ����́i0�ɂ��Ă�OK�j
								 D3DPOOL_MANAGED,                            // �������Ǘ������C���ɂ���
								 &m_pVtxBuff,
								 NULL );

	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�i 2D���W�E�E��� �j
	pVtx[0].pos = D3DXVECTOR4( m_Pos.x          , m_Pos.y          , 0.0f, 1.0f);                 // ����̍��W
	pVtx[1].pos = D3DXVECTOR4( m_Pos.x + m_Scl.x, m_Pos.y          , 0.0f, 1.0f);                 // �E��̍��W
	pVtx[2].pos = D3DXVECTOR4( m_Pos.x          , m_Pos.y + m_Scl.y, 0.0f, 1.0f);                 // �����̍��W
	pVtx[3].pos = D3DXVECTOR4( m_Pos.x + m_Scl.x, m_Pos.y + m_Scl.y, 0.0f, 1.0f);                 // �E���̍��W

	// ���_�J���[�̐ݒ�i0~255�̐����l�j
	pVtx[0].color = m_Color;  // ����̐F
	pVtx[1].color = m_Color;  // �E��̐F
	pVtx[2].color = m_Color;  // �����̐F
	pVtx[3].color = m_Color;  // �E���̐F

	// ���_�f�[�^��UV�f�[�^�̒ǉ�
	pVtx[0].tex = D3DXVECTOR2( 0.0f , 0.0f );                    // �����UV���W
	pVtx[1].tex = D3DXVECTOR2( 1.0f , 0.0f );                    // �E���UV���W
	pVtx[2].tex = D3DXVECTOR2( 0.0f , 1.0f );                    // ������UV���W
	pVtx[3].tex = D3DXVECTOR2( 1.0f , 1.0f );                    // �E����UV���W

	// �����J����
	m_pVtxBuff->Unlock();
}

//=======================================================================================
// �|���S���̐F�X�V
//=======================================================================================
void CScene2D::SetVexColor()
{
	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�i0~255�̐����l�j
	pVtx[0].color = m_Color;  // ����̐F
	pVtx[1].color = m_Color;  // �E��̐F
	pVtx[2].color = m_Color;  // �����̐F
	pVtx[3].color = m_Color;  // �E���̐F

	// �����J����
	m_pVtxBuff->Unlock();
}


//=======================================================================================
// �|���S���̃T�C�Y�X�V
//=======================================================================================
void CScene2D::SetVexPos()
{
	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�i 2D���W�E�E��� �j
	pVtx[0].pos = D3DXVECTOR4(m_Pos.x          , m_Pos.y, 0.0f,1.0f);                 // ����̍��W
	pVtx[1].pos = D3DXVECTOR4(m_Pos.x + m_Scl.x, m_Pos.y, 0.0f,1.0f);                 // �E��̍��W
	pVtx[2].pos = D3DXVECTOR4(m_Pos.x          , m_Pos.y + m_Scl.y, 0.0f,1.0f);                 // �����̍��W
	pVtx[3].pos = D3DXVECTOR4(m_Pos.x + m_Scl.x, m_Pos.y + m_Scl.y, 0.0f,1.0f);                 // �E���̍��W

							// �����J����
	m_pVtxBuff->Unlock();
}


//=======================================================================================
// �|���S����UV���W�X�V
//=======================================================================================
void CScene2D::SetVexUV(float Percentage)
{
	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�f�[�^��UV�f�[�^�̒ǉ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);                    // �����UV���W
	pVtx[1].tex = D3DXVECTOR2(Percentage, 0.0f);                    // �E���UV���W
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);                    // ������UV���W
	pVtx[3].tex = D3DXVECTOR2(Percentage, 1.0f);                    // �E����UV���W

							// �����J����
	m_pVtxBuff->Unlock();
}