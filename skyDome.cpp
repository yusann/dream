//=============================================================================
// �X�J�C�h�[��
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sceneMesh.h"
#include "skyDome.h"
#include "texture.h"

CSkyDome::CSkyDome() :CSceneMesh(CScene::OBJTYPE_FIELD)
{
}

CSkyDome::~CSkyDome()
{
}

//==================================================================================================================================================
// �쐬����
//==================================================================================================================================================
CSkyDome *CSkyDome::Create(D3DXVECTOR3 pos, float radius, int numBlockX, int numBlockY, D3DXCOLOR color)
{
	CSkyDome *pScene3D;                            // �ϐ��錾
	pScene3D = new CSkyDome;                       // ���I�m��
	pScene3D->Init(pos, radius, numBlockX, numBlockY, color);                            // ������
	return pScene3D;                             // �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CSkyDome::Init(D3DXVECTOR3 pos, float radius, int numBlockX, int numBlockY, D3DXCOLOR color)
{
	// �����o�ϐ��̏�����
	m_Pos = pos;

	// �v���C�x�[�g�ϐ��̏�����
	m_pIdxBuff = NULL;
	m_VexNum = (numBlockY * ((numBlockX + 1) * 2)) + ((numBlockY - 1) * 2);
	m_PolygonNum = m_VexNum - 2;

	m_Radius = radius;
	m_NumBlockX = numBlockX;
	m_NumBlockY = numBlockY;
	m_Color = color;

	// ���_�ݒ�
	MakeVex();
	MakeBuff();

	// �e�N�X�`���Z�b�g
	m_pTexture = CTexture::GetTexture((int)CTexture::TEXTYPE_SKY000);

	// �^�C�v�̑��
	CSceneMesh::Init();
}

//=======================================================================================
//   �I������
//=======================================================================================
void CSkyDome::Uninit()
{
	CSceneMesh::Uninit();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CSkyDome::Update()
{
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CSkyDome::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}
	// ���C�g�̐ݒ�iOFF�j
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	CSceneMesh::Draw();
	// ���C�g�̐ݒ�iON�j
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=======================================================================================
// �|���S���̒��_�ݒ�
//=======================================================================================
void CSkyDome::MakeVex(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_POS) * ((m_NumBlockX + 1) * (m_NumBlockY + 1)),           // �쐬���������_�o�b�t�@�̃T�C�Y�i��̒��_*���_���j
		D3DUSAGE_WRITEONLY,                         // �������ނ������Ȃ��i�`�F�b�N���Ȃ��j
		0,                              // �ǂ�Ȓ��_�ŏ����́i0�ɂ��Ă�OK�j
		D3DPOOL_MANAGED,                            // �������Ǘ������C���ɂ���
		&m_pVB_POS,
		NULL);

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_POS* v0;
	m_pVB_POS->Lock(0, 0, (void**)&v0, 0);

	// ���a���L��
	float Radius = m_Radius;
	for (int nCntHeight = 0; nCntHeight < m_NumBlockY + 1; nCntHeight++)
	{
		m_Radius = cos(D3DXToRadian((90 / m_NumBlockY) * nCntHeight)) * Radius;
		for (int nCntWidth = 0; nCntWidth < m_NumBlockX + 1; nCntWidth++, v0++)
		{
			// ���_���̐ݒ�
			v0[0].pos = D3DXVECTOR3(cos(D3DXToRadian((360 / m_NumBlockX) * nCntWidth)) * m_Radius,      // X���W�̐ݒ�i 3D���W�E�E��� �j
				sin(D3DXToRadian(((90 / m_NumBlockY) * nCntHeight))) * Radius,                                                                            // Y���W�̐ݒ�
				sin(D3DXToRadian((360 / m_NumBlockX) * nCntWidth)) * m_Radius);    // Z���W�̐ݒ�
		}
	}
	m_pVB_POS->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�m�[�}�����W)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_NORMAL) * ((m_NumBlockX + 1) * (m_NumBlockY + 1)),
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_NORMAL, NULL))) {
		MessageBox(NULL, "�m�[�}�����W�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_NORMAL* v1;
	m_pVB_NORMAL->Lock(0, 0, (void**)&v1, 0);

	for (int nCntHeight = 0; nCntHeight < m_NumBlockY + 1; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < m_NumBlockX + 1; nCntWidth++, v1++)
		{
			v1[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
		}
	}
	m_pVB_NORMAL->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�F)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_COLOR) * ((m_NumBlockX + 1) * (m_NumBlockY + 1)),
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_COLOR, NULL))) {
		MessageBox(NULL, "���_�F�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_COLOR* v2;
	m_pVB_COLOR->Lock(0, 0, (void**)&v2, 0);

	for (int nCntHeight = 0; nCntHeight < m_NumBlockY + 1; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < m_NumBlockX + 1; nCntWidth++, v2++)
		{
			v2[0].color = m_Color;                       // �J���[�̐ݒ�
		}
	}
	m_pVB_COLOR->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�e�N�X�`�����W)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_TEX) * ((m_NumBlockX + 1) * (m_NumBlockY + 1)),
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_TEX, NULL))) {
		MessageBox(NULL, "�e�N�X�`�����W�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_TEX* v3;
	m_pVB_TEX->Lock(0, 0, (void**)&v3, 0);

	for (int nCntHeight = 0; nCntHeight < m_NumBlockY + 1; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < m_NumBlockX + 1; nCntWidth++, v3++)
		{
			v3[0].tex = D3DXVECTOR2(nCntWidth * (1.0f / m_NumBlockX),              // �e�N�X�`��U���W�̐ݒ�
				(m_NumBlockY - nCntHeight) * (1.0f / m_NumBlockY));            // �e�N�X�`��V���W�̐ݒ�

		}
	}
	m_pVB_TEX->Unlock();
}


//=======================================================================================
// �|���S���̃o�b�t�@�ݒ�
//=======================================================================================
void CSkyDome::MakeBuff(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �C���f�b�N�X�o�b�t�@�̍쐬
	HRESULT hr;
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * m_VexNum,        // ���_���iWORD��16Bid�j
									D3DUSAGE_WRITEONLY,              // �g�p�p�r�t���O�i�������ނ̂݁j
									D3DFMT_INDEX16,                  // �f�[�^�̃t�H�[�}�b�g�i32Bid�ݒ肵����16��32�ɕύX�j
									D3DPOOL_MANAGED,                 // �������̊Ǘ����@�i���C���j
									&m_pIdxBuff,              // �o�b�t�@�\�C���^�[�t�F�C�X�|�C���^�̃A�h���X
									NULL);

	// �C���f�b�N�X���i�[�p�^���o�b�t�@�̐錾
	WORD* pIdx;

	// ���b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// Z���̃��[�v
	for (int nCntHeight = 0; nCntHeight < m_NumBlockY; nCntHeight++)
	{
		// X���̃��[�v
		for (int nCntWidth = 0; nCntWidth < m_NumBlockX + 1; nCntWidth++, pIdx += 2)                          // ���[�v�����pIdx��2�O�i
		{
			// �@��������
			// 1��ڈȊO��1�s�ڂ̏���
			if (nCntHeight != 0 && nCntWidth == 0) {
				pIdx[0] = (unsigned short)((m_NumBlockX + 1) + (nCntHeight * (m_NumBlockX + 1) + nCntWidth));                  // �������ɃC���f�b�N�X������
				pIdx += 1;                                                                               // 1�O�i
			}
			// �d�����Ȃ����_�̏���
			pIdx[0] = (unsigned short)((m_NumBlockX + 1) + (nCntHeight * (m_NumBlockX + 1) + nCntWidth));
			pIdx[1] = (unsigned short)((m_NumBlockX + 1) + (nCntHeight * (m_NumBlockX + 1) + nCntWidth) - (m_NumBlockX + 1));

			// �ŏI��ڈȊO�̍ŏI�s�ڂ̏���
			if (nCntHeight != m_NumBlockY - 1 && nCntWidth == m_NumBlockX) {
				pIdx[2] = (unsigned short)((m_NumBlockX + 1) + (nCntHeight * (m_NumBlockX + 1) + nCntWidth) - (m_NumBlockX + 1));  // �������ɃC���f�b�N�X������
				pIdx += 1;                                                                               // 1�O�i
			}
		}
	}

	// ���b�N���
	m_pIdxBuff->Unlock();
}
