//=============================================================================
// �e
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"

#include "shadow.h"
#include "texture.h"
#include "equation.h"

CShadow::CShadow(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl) :CScene(CScene::OBJTYPE_SHADOW)
{
	m_Pos = Pos;
	m_Scl = Scl;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
}

CShadow::~CShadow()
{
}

//=======================================================================================
//   ��������
//=======================================================================================
CShadow* CShadow::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl)
{
	CShadow *pScene3D;                            // �ϐ��錾
	pScene3D = new CShadow(Pos, Scl);                       // ���I�m��
	pScene3D->Init();                            // ������
	return pScene3D;                             // �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CShadow::Init()
{
	m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_BULLET);

	// ���_�ݒ�
	MakeVex();

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_SHADOW);
}

//=======================================================================================
//   �I������
//=======================================================================================
void CShadow::Uninit()
{
	SAFE_RELEASE(m_pVtxBuff);      // ���_�o�b�t�@�̔j��
	CScene::Release();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CShadow::Update()
{
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CShadow::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 Pos = m_Pos;
	Pos.y += 0.1f;
	D3DXVECTOR3 Rot = D3DXVECTOR3(3.14159265f*0.5f,0.0f ,0.0f);
	D3DXVECTOR3 Scl = D3DXVECTOR3(m_Scl.z, m_Scl.z, 1.0f);

	CEquation::SetMatrix(&mtxWorld, Pos, Rot,Scl);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxBuff,              // �X�g���[���̂��ƂɂȂ钸�_�̃o�b�t�@�̎n�_
		0,                       // �I�t�Z�b�g�i�o�C�g�j
		sizeof(VERTEX_3D));      // ��̒��_�f�[�^�̃T�C�Y�i�X�g���C�h�ʁj

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �`�撼�O�Ƀe�N�X�`�����Z�b�g�i�e�N�X�`���̐ݒ�j
	pDevice->SetTexture(0, m_pTexture);

	// ���Z����ON
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

	// Z�o�b�t�@�̏����ݐݒ�iOFF�j
	//pDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,        // �v���~�e�B�u�̎��
		0,                          // �I�t�Z�b�g�i���_���j
		NUM_POLYGON);              // �v���~�e�B�u�̐��i�|���S���̐��j
	

	// Z�o�b�t�@�̏����ݐݒ�iOFF�j
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE );

	// ���Z�N���A
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}

//=======================================================================================
// �|���S���̒��_�ݒ�
//=======================================================================================
void CShadow::MakeVex(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,           // �쐬���������_�o�b�t�@�̃T�C�Y�i��̒��_*���_���j
		D3DUSAGE_WRITEONLY,                         // �������ނ������Ȃ��i�`�F�b�N���Ȃ��j
		FVF_VERTEX_3D,                              // �ǂ�Ȓ��_�ŏ����́i0�ɂ��Ă�OK�j
		D3DPOOL_MANAGED,                            // �������Ǘ������C���ɂ���
		&m_pVtxBuff,
		NULL);

	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�i 2D���W�E�E��� �j
	pVtx[0].pos = D3DXVECTOR3(-m_Scl.x, m_Scl.y ,0.0f);                 // ����̍��W
	pVtx[1].pos = D3DXVECTOR3(m_Scl.x , m_Scl.y ,0.0f);                 // �E��̍��W
	pVtx[2].pos = D3DXVECTOR3(-m_Scl.x, -m_Scl.y,0.0f);                 // �����̍��W
	pVtx[3].pos = D3DXVECTOR3(m_Scl.x , -m_Scl.y,0.0f);                 // �E���̍��W

	// ���_�@���̐ݒ�
	pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);


	// ���_�J���[�̐ݒ�i0~255�̐����l�j
	pVtx[0].color = m_Color;  // ����̐F
	pVtx[1].color = m_Color;  // �E��̐F
	pVtx[2].color = m_Color;  // �����̐F
	pVtx[3].color = m_Color;  // �E���̐F

														// ���_�f�[�^��UV�f�[�^�̒ǉ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);                    // �����UV���W
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);                    // �E���UV���W
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);                    // ������UV���W
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);                    // �E����UV���W

															  // �����J����
	m_pVtxBuff->Unlock();
}