//=============================================================================
// �r���{�[�h����
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sceneBillboard.h"
#include "camera.h"
#include "equation.h"

//*************
// ���C������
//*************
CSceneBillboard::CSceneBillboard(int Priority) :CScene(Priority),
m_pVB_POS(NULL),
m_pVB_NORMAL(NULL),
m_pVB_COLOR(NULL),
m_pVB_TEX(NULL)
{
	m_TexWidth = 1;
	m_TexHeight = 1;
	m_TexPos = D3DXVECTOR2(0.0f, 0.0f);
	m_TexScl = D3DXVECTOR2(1.0f, 1.0f);
	D3DXQuaternionIdentity(&m_Quaternion);
}

CSceneBillboard::~CSceneBillboard()
{
}

//=======================================================================================
//   ����������
//=======================================================================================
void CSceneBillboard::Init()
{
	m_Angle = CEquation::Angle(m_Scl.x, m_Scl.y);
	m_Length = CEquation::Length(m_Scl.x, m_Scl.y);
	// ���_�ݒ�
	MakeVex();
}

//=======================================================================================
//   �I������
//=======================================================================================
void CSceneBillboard::Uninit()
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
void CSceneBillboard::Update()
{
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CSceneBillboard::Draw(DRAWTYPE type)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�̃f�N�����[�V�����̐ݒ�
	LPDIRECT3DVERTEXDECLARATION9 pDecl = *CVertexDecl::Get(CVertexDecl::TYPE_3D);
	pDevice->SetVertexDeclaration(pDecl);

	// �X�g���[���Ƃ��Ē��_�o�b�t�@��ݒ�
	pDevice->SetStreamSource(0, m_pVB_POS, 0, sizeof(CVertexDecl::VERTEX3D_POS));
	pDevice->SetStreamSource(1, m_pVB_NORMAL, 0, sizeof(CVertexDecl::VERTEX3D_NORMAL));
	pDevice->SetStreamSource(2, m_pVB_COLOR, 0, sizeof(CVertexDecl::VERTEX3D_COLOR));
	pDevice->SetStreamSource(3, m_pVB_TEX, 0, sizeof(CVertexDecl::VERTEX3D_TEX));

	// �`�撼�O�Ƀe�N�X�`�����Z�b�g�i�e�N�X�`���̐ݒ�j
	pDevice->SetTexture(0, m_pTexture);

	// �J�����̎擾
	CCamera* pCamera;
	pCamera = CManager::GetCamera();

	// �ϊ��s��̐錾
	D3DXMATRIX mtxPos;             // ���[�J�����W
	D3DXMATRIX mtxWorld;           // ���[���h���
	D3DXMATRIX mtxViewInverse;     // �]�u�s��
	D3DXMATRIX mtxViewCamera = pCamera->GetMtxView();      // �J�����s��̎擾
	
	// ���[�J�����W�̑��
	D3DXMatrixTranslation(&mtxPos,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z);

	// �t�s��̍쐬
	D3DXMatrixTranspose(&mtxViewInverse, &mtxViewCamera);

	// ���s�ړ������������i�]�u�O�j
	mtxViewInverse._14 = 0.0f;
	mtxViewInverse._24 = 0.0f;
	mtxViewInverse._34 = 0.0f;

	// ���[���h��񏈗�
	D3DXMatrixIdentity(&mtxWorld);                       // ���[���h�̒��g��������
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);   // ���[���h���W�̑��
	mtxWorld = mtxViewInverse * mtxWorld;

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);       // ���[���h���Z�b�g
	
	 // �A���t�@�e�X�g�iON�j
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);         // �A���t�@�e�X�g���\��
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);                   // �Q�ƒl�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);     // �Q�ƒl < ��

	// ���C�g�̐ݒ�iOFF�j
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	switch (type)
	{
	case NORMAL:
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,        // �v���~�e�B�u�̎��
			0,                          // �I�t�Z�b�g�i���_���j
			NUM_POLYGON);              // �v���~�e�B�u�̐��i�|���S���̐��j
		break;
	case ADD:
		// ���Z�����iON�j
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,        // �v���~�e�B�u�̎��
			0,                          // �I�t�Z�b�g�i���_���j
			NUM_POLYGON);              // �v���~�e�B�u�̐��i�|���S���̐��j

		// ���Z�����iOFF�j
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	default:
		assert(!"�^�C�v�s��sceneBillboard::Draw()");
		break;
	}

	// ���C�g�̐ݒ�iON�j
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �A���t�@�e�X�g�iOFF�j
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=======================================================================================
// �|���S���̒��_�ݒ�
//=======================================================================================
void CSceneBillboard::MakeVex(void)
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
	// �X�P�[����ݒ�
	v0[0].pos = D3DXVECTOR3(cosf(-m_Angle + D3DX_PI) * m_Length,      // X���W�̐ݒ�
		sinf(-m_Angle + D3DX_PI) * m_Length,      // Y���W�̐ݒ�
		0.0f);                                   // Z���W�̐ݒ�
	v0[1].pos = D3DXVECTOR3(cosf(m_Angle) * m_Length,             // X���W�̐ݒ�
		sinf(m_Angle) * m_Length,             // Y���W�̐ݒ�
		0.0f);                               // Z���W�̐ݒ�
	v0[2].pos = D3DXVECTOR3(cosf(m_Angle + D3DX_PI) * m_Length,      // X���W�̐ݒ�
		sinf(m_Angle + D3DX_PI) * m_Length,      // Y���W�̐ݒ�
		0.0f);                                  // Z���W�̐ݒ�
	v0[3].pos = D3DXVECTOR3(cosf(-m_Angle) * m_Length,          // X���W�̐ݒ�
		sinf(-m_Angle) * m_Length,          // Y���W�̐ݒ�
		0.0f);                             // Z���W�̐ݒ�
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

	v1[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v1[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v1[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v1[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
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
void CSceneBillboard::SetTexID(int nID)
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
	pVtx[0].tex = D3DXVECTOR2(m_TexPos.x + 0.001f, m_TexPos.y + 0.001f);                    // �����UV���W
	pVtx[1].tex = D3DXVECTOR2(m_TexPos.x - 0.001f + m_TexScl.x, m_TexPos.y + 0.001f);                    // �E���UV���W
	pVtx[2].tex = D3DXVECTOR2(m_TexPos.x + 0.001f, m_TexPos.y - 0.001f + m_TexScl.y);                    // ������UV���W
	pVtx[3].tex = D3DXVECTOR2(m_TexPos.x - 0.001f + m_TexScl.x, m_TexPos.y - 0.001f + m_TexScl.y);                    // �E����UV���W

	// �����J����
	m_pVB_TEX->Unlock();
}
