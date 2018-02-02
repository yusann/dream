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
CScene2D::CScene2D(int Priority) :CScene(Priority),
m_pVB(NULL),
m_TexPos(D3DXVECTOR2(0.0f,0.0f)),
m_TexScl(D3DXVECTOR2(1.0f, 1.0f)),
m_TexWidth(1),
m_TexHeight(1)
{
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

CScene2D::~CScene2D()
{
}

//==================================================================================================================================================
// �쐬����
//==================================================================================================================================================
CScene2D *CScene2D::Create(const LPDIRECT3DTEXTURE9 pTexture,
	const D3DXVECTOR2 Pos,
	const D3DXVECTOR2 Scl,
	const CScene::OBJTYPE ObjType,
	const int TexWidth,
	const int TexHeight)
{
	CScene2D *pScene2D;                            // �ϐ��錾
	pScene2D = new CScene2D;                       // ���I�m��
	pScene2D->SetInfo(pTexture, Pos, Scl, ObjType, TexWidth, TexHeight);
	pScene2D->Init();                            // ������
	pScene2D->SetTexID();
	return pScene2D;                             // �l��Ԃ�
}

//=======================================================================================
//   ���̑��
//=======================================================================================
void CScene2D::SetInfo(const LPDIRECT3DTEXTURE9 pTexture,
	const D3DXVECTOR2 Pos,
	const D3DXVECTOR2 Scl,
	const CScene::OBJTYPE ObjType,
	const int TexWidth,
	const int TexHeight)
{
	m_pTexture = pTexture;
	m_Pos = D3DXVECTOR3(Pos.x, Pos.y, 0.0f);
	m_Scl = D3DXVECTOR3(Scl.x, Scl.y, 0.0f);
	m_TexWidth = TexWidth;
	m_TexHeight = TexHeight;
	CScene::SetObjType(ObjType);
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
	CVertexDecl::SetTex2D(pDevice, m_pVB);

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
								 &m_pVB,
								 NULL );

	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVB->Lock( 0, 0, (void**)&pVtx, 0);

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
	pVtx[0].tex = m_TexPos;                    // �����UV���W
	pVtx[1].tex = D3DXVECTOR2(m_TexPos.x+ m_TexScl.x, m_TexPos.y);                    // �E���UV���W
	pVtx[2].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y + m_TexScl.y);                    // ������UV���W
	pVtx[3].tex = m_TexPos+ m_TexScl;                    // �E����UV���W

	// �����J����
	m_pVB->Unlock();
}

//=======================================================================================
// �|���S���̐F�X�V
//=======================================================================================
void CScene2D::SetVexColor(D3DXCOLOR Color)
{
	m_Color = Color;
	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�i0~255�̐����l�j
	pVtx[0].color = m_Color;  // ����̐F
	pVtx[1].color = m_Color;  // �E��̐F
	pVtx[2].color = m_Color;  // �����̐F
	pVtx[3].color = m_Color;  // �E���̐F

	// �����J����
	m_pVB->Unlock();
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
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�i 2D���W�E�E��� �j
	pVtx[0].pos = D3DXVECTOR4(m_Pos.x          , m_Pos.y, 0.0f,1.0f);                 // ����̍��W
	pVtx[1].pos = D3DXVECTOR4(m_Pos.x + m_Scl.x, m_Pos.y, 0.0f,1.0f);                 // �E��̍��W
	pVtx[2].pos = D3DXVECTOR4(m_Pos.x          , m_Pos.y + m_Scl.y, 0.0f,1.0f);                 // �����̍��W
	pVtx[3].pos = D3DXVECTOR4(m_Pos.x + m_Scl.x, m_Pos.y + m_Scl.y, 0.0f,1.0f);                 // �E���̍��W

							// �����J����
	m_pVB->Unlock();
}


//=======================================================================================
// �|���S����UV���W�X�V
//=======================================================================================
void CScene2D::SetVexUV()
{
	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�f�[�^��UV�f�[�^�̒ǉ�
	pVtx[0].tex = m_TexPos;                    // �����UV���W
	pVtx[1].tex = D3DXVECTOR2(m_TexPos.x+ m_TexScl.x, m_TexPos.y);                    // �E���UV���W
	pVtx[2].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y + m_TexScl.y);                    // ������UV���W
	pVtx[3].tex = m_TexPos+ m_TexScl;                    // �E����UV���W

							// �����J����
	m_pVB->Unlock();
}
//=======================================================================================
//   �e�N�X�`��ID�Z�b�g
//=======================================================================================
void CScene2D::SetTexID(int nID)
{
	// �e�N�X�`���̃X�P�[�����
	m_TexScl.x = 1.0f / m_TexWidth;
	m_TexScl.y = 1.0f / m_TexHeight;

	// �e�N�X�`�����W�̑��
	m_TexPos.x = nID % m_TexWidth * m_TexScl.x;		//  X���W
	m_TexPos.y = nID / m_TexWidth * m_TexScl.y;		//  Y���W
	
	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX2D* pVtx;
	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�f�[�^��UV�f�[�^�̒ǉ�
	pVtx[0].tex = D3DXVECTOR2(m_TexPos.x + 0.001f             , m_TexPos.y + 0.001f);                    // �����UV���W
	pVtx[1].tex = D3DXVECTOR2(m_TexPos.x - 0.001f + m_TexScl.x, m_TexPos.y + 0.001f);                    // �E���UV���W
	pVtx[2].tex = D3DXVECTOR2(m_TexPos.x + 0.001f             , m_TexPos.y - 0.001f + m_TexScl.y);                    // ������UV���W
	pVtx[3].tex = D3DXVECTOR2(m_TexPos.x - 0.001f + m_TexScl.x, m_TexPos.y - 0.001f + m_TexScl.y);                    // �E����UV���W

	m_pVB->Unlock();
}

//=======================================================================================
// �Q�[�W�X�V����
//=======================================================================================
void CScene2D::SetVexGage(float Val)
{
	float sclX = m_Scl.x * Val;
	float tex_sclX = m_TexScl.x * Val;
	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);
	
	// ���_���W�̐ݒ�i 2D���W�E�E��� �j
	pVtx[0].pos = D3DXVECTOR4(m_Pos.x          , m_Pos.y, 0.0f,1.0f);                 // ����̍��W
	pVtx[1].pos = D3DXVECTOR4(m_Pos.x + sclX, m_Pos.y, 0.0f,1.0f);                 // �E��̍��W
	pVtx[2].pos = D3DXVECTOR4(m_Pos.x          , m_Pos.y + m_Scl.y, 0.0f,1.0f);                 // �����̍��W
	pVtx[3].pos = D3DXVECTOR4(m_Pos.x + sclX, m_Pos.y + m_Scl.y, 0.0f,1.0f);                 // �E���̍��W

	// ���_�f�[�^��UV�f�[�^�̒ǉ�
	pVtx[0].tex = m_TexPos;                    // �����UV���W
	pVtx[1].tex = D3DXVECTOR2(m_TexPos.x + tex_sclX, m_TexPos.y);                    // �E���UV���W
	pVtx[2].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y + m_TexScl.y);                    // ������UV���W
	pVtx[3].tex = D3DXVECTOR2(m_TexPos.x + tex_sclX, m_TexPos.y + m_TexScl.y);                    // �E����UV���W

	// �����J����
	m_pVB->Unlock();
}