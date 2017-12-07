//=============================================================================
// 3D����
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene3D.h"

//*************
// ���C������
//*************
CScene3D::CScene3D(int Priority) :CScene(Priority),
m_pVB_POS(NULL),
m_pVB_NORMAL(NULL),
m_pVB_COLOR(NULL),
m_pVB_TEX(NULL)
{
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TexWidth = 1;
	m_TexHeight = 1;
	m_TexPos = D3DXVECTOR2(0.0f, 0.0f);
	m_TexScl = D3DXVECTOR2(0.0f, 0.0f);
}

CScene3D::~CScene3D()
{
}

//=======================================================================================
//   ����������
//=======================================================================================
void CScene3D::Init()
{
	// ���_�ݒ�
	MakeVex();
}

//=======================================================================================
//   �I������
//=======================================================================================
void CScene3D::Uninit()
{
	SAFE_RELEASE(m_pVB_POS);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVB_NORMAL);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVB_COLOR);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVB_TEX);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE( m_pVtxBuff );      // ���_�o�b�t�@�̔j��
	CScene::Release();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CScene3D::Update()
{
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CScene3D::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

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

	// ���[�J�����W�̑��
	D3DXMatrixTranslation(&mtxPos,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z);

	// ���[���h��񏈗�
	D3DXMatrixIdentity(&mtxWorld);                       // ���[���h�̒��g��������
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);   // ���[���h��]�̑��
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);   // ���[���h���W�̑��
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);       // ���[���h���Z�b�g

	// ���_�̃f�N�����[�V�����̐ݒ�
	LPDIRECT3DVERTEXDECLARATION9 pDecl = *CVertexDecl::Get(CVertexDecl::TYPE_3D);
	pDevice->SetVertexDeclaration(pDecl);

	// �X�g���[���Ƃ��Ē��_�o�b�t�@��ݒ�
	pDevice->SetStreamSource(0, m_pVB_POS, 0, sizeof(CVertexDecl::VERTEX3D_POS));
	pDevice->SetStreamSource(1, m_pVB_NORMAL, 0, sizeof(CVertexDecl::VERTEX3D_NORMAL));
	pDevice->SetStreamSource(2, m_pVB_COLOR, 0, sizeof(CVertexDecl::VERTEX3D_COLOR));
	pDevice->SetStreamSource(3, m_pVB_TEX, 0, sizeof(CVertexDecl::VERTEX3D_TEX));

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
void CScene3D::MakeVex(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_POS) * NUM_VERTEX,           // �쐬���������_�o�b�t�@�̃T�C�Y�i��̒��_*���_���j
		D3DUSAGE_WRITEONLY,                         // �������ނ������Ȃ��i�`�F�b�N���Ȃ��j
		0,                              // �ǂ�Ȓ��_�ŏ����́i0�ɂ��Ă�OK�j
		D3DPOOL_MANAGED,                            // �������Ǘ������C���ɂ���
		&m_pVB_POS,
		NULL);

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_POS* v0;
	m_pVB_POS->Lock(0, 0, (void**)&v0, 0);
	// ���_���W�̐ݒ�i 2D���W�E�E��� �j
	v0[0].pos = D3DXVECTOR3(-m_Scl.x, m_Scl.y, m_Scl.z);                 // ����̍��W
	v0[1].pos = D3DXVECTOR3(m_Scl.x, m_Scl.y, m_Scl.z);                 // �E��̍��W
	v0[2].pos = D3DXVECTOR3(-m_Scl.x, -m_Scl.y, m_Scl.z);                 // �����̍��W
	v0[3].pos = D3DXVECTOR3(m_Scl.x, -m_Scl.y, m_Scl.z);                 // �E���̍��W
	m_pVB_POS->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�m�[�}�����W)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_NORMAL) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_NORMAL, NULL))) {
		MessageBox(NULL, "�m�[�}�����W�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_NORMAL* v1;
	m_pVB_NORMAL->Lock(0, 0, (void**)&v1, 0);
	// ���_�@���̐ݒ�
	v1[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v1[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v1[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v1[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_pVB_NORMAL->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�F)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_COLOR) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_COLOR, NULL))) {
		MessageBox(NULL, "���_�F�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_COLOR* v2;
	m_pVB_COLOR->Lock(0, 0, (void**)&v2, 0);
	v2[0].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // ����̐F
	v2[1].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �E��̐F
	v2[2].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �����̐F
	v2[3].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �E���̐F
	m_pVB_COLOR->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�e�N�X�`�����W)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_TEX) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_TEX, NULL))) {
		MessageBox(NULL, "�e�N�X�`�����W�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_TEX* v3;
	m_pVB_TEX->Lock(0, 0, (void**)&v3, 0);
	v3[0].tex = D3DXVECTOR2(0.0f, 0.0f);                    // �����UV���W
	v3[1].tex = D3DXVECTOR2(1.0f, 0.0f);                    // �E���UV���W
	v3[2].tex = D3DXVECTOR2(0.0f, 1.0f);                    // ������UV���W
	v3[3].tex = D3DXVECTOR2(1.0f, 1.0f);                    // �E����UV���W
	m_pVB_TEX->Unlock();
}

//=======================================================================================
//   �e�N�X�`��ID�Z�b�g
//=======================================================================================
void CScene3D::SetTexID(int nID)
{
	// �e�N�X�`���̃X�P�[�����
	m_TexScl.x = 1.0f / m_TexWidth;
	m_TexScl.y = 1.0f / m_TexHeight;

	// �e�N�X�`�����W�̑��
	m_TexPos.x = nID % m_TexWidth * m_TexScl.x;		//  X���W
	m_TexPos.y = nID / m_TexWidth * m_TexScl.y;		//  Y���W

	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX3D_TEX* pVtx;
	m_pVB_TEX->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�f�[�^��UV�f�[�^�̒ǉ�
	pVtx[0].tex = D3DXVECTOR2(m_TexPos.x+0.001f             , m_TexPos.y+0.001f);                    // �����UV���W
	pVtx[1].tex = D3DXVECTOR2(m_TexPos.x-0.001f + m_TexScl.x, m_TexPos.y+0.001f);                    // �E���UV���W
	pVtx[2].tex = D3DXVECTOR2(m_TexPos.x+0.001f             , m_TexPos.y-0.001f + m_TexScl.y);                    // ������UV���W
	pVtx[3].tex = D3DXVECTOR2(m_TexPos.x-0.001f + m_TexScl.x, m_TexPos.y-0.001f + m_TexScl.y);                    // �E����UV���W

	// �����J����
	m_pVB_TEX->Unlock();
}