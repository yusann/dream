//=============================================================================
// ���b�V��������
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sceneMesh.h"
#include "meshCube.h"
#include "texture.h"

CMeshCube::CMeshCube() :CSceneMesh(CScene::OBJTYPE_DEBUG_MESH)
{
}

CMeshCube::~CMeshCube()
{
}

//=======================================================================================
// �쐬����
//=======================================================================================
CMeshCube *CMeshCube::Create(void)
{
	CMeshCube *pScene3D;                            // �ϐ��錾
	pScene3D = new CMeshCube;                       // ���I�m��
	pScene3D->Init();                            // ������
	return pScene3D;                             // �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CMeshCube::Init(void)
{
	// �����o�ϐ��̏�����
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f);

	// �v���C�x�[�g�ϐ��̏�����
	m_pIdxBuff = NULL;
	m_PolygonNum = 12;
	m_VexNum = 8;

	// ���_�ݒ�
	MakeVex();
	MakeBuff();

	// �e�N�X�`���Z�b�g
	m_pTexture = NULL;

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_DEBUG_MESH);

	CSceneMesh::Init();
}

//=======================================================================================
//   �I������
//=======================================================================================
void CMeshCube::Uninit()
{
	CSceneMesh::Uninit();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CMeshCube::Update(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl)
{
	m_Pos = Pos;
	m_Scl = Scl;
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CMeshCube::Draw()
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

	// ���[�J���X�P�[���̑��
	D3DXMatrixScaling(&mtxScl,
		m_Scl.x,
		m_Scl.y,
		m_Scl.z);

	// ���[�J�����W�̑��
	D3DXMatrixTranslation(&mtxPos,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z);

	// ���[���h��񏈗�
	D3DXMatrixIdentity(&mtxWorld);                       // ���[���h�̒��g��������
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);   // ���[���h��]�̑��
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);   // ���[���h�X�P�[���̑��
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);   // ���[���h���W�̑��
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);       // ���[���h���Z�b�g

														 // ���_�̃f�N�����[�V�����̐ݒ�
	CVertexDecl::SetTex3D(pDevice, m_pVB_POS, m_pVB_NORMAL, m_pVB_COLOR, m_pVB_TEX);

	// �f�o�C�X�ɃC���f�b�N�X�o�b�t�@�̐ݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//// �C���f�b�N�X�v���~�e�B�u�̕`��
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,                 // �v���~�e�B�u�̎��
	//	0,
	//	0,
	//	m_VexNum,   // ���_��
	//	0,
	//	m_PolygonNum);                       // �v���~�e�B�u�̐��i�|���S���̐��j

	// ���C�g�̐ݒ�iON�j
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=======================================================================================
// �|���S���̒��_�ݒ�
//=======================================================================================
void CMeshCube::MakeVex(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_POS) * m_VexNum,           // �쐬���������_�o�b�t�@�̃T�C�Y�i��̒��_*���_���j
		D3DUSAGE_WRITEONLY,                         // �������ނ������Ȃ��i�`�F�b�N���Ȃ��j
		0,                              // �ǂ�Ȓ��_�ŏ����́i0�ɂ��Ă�OK�j
		D3DPOOL_MANAGED,                            // �������Ǘ������C���ɂ���
		&m_pVB_POS,
		NULL);

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_POS* v0;
	m_pVB_POS->Lock(0, 0, (void**)&v0, 0);
	for (int i = 0; i < 2; i++, v0 += 4)
	{
		// ���_���̐ݒ�
		v0[0].pos = D3DXVECTOR3(-0.5f, i * m_Scl.y, 0.5);
		v0[1].pos = D3DXVECTOR3(0.5f, i * m_Scl.y, 0.5);
		v0[2].pos = D3DXVECTOR3(0.5f, i * m_Scl.y, -0.5);
		v0[3].pos = D3DXVECTOR3(-0.5f, i * m_Scl.y, -0.5);
	}
	m_pVB_POS->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�m�[�}�����W)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_NORMAL) * m_VexNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_NORMAL, NULL))) {
		MessageBox(NULL, "�m�[�}�����W�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_NORMAL* v1;
	m_pVB_NORMAL->Lock(0, 0, (void**)&v1, 0);
	for (int i = 0; i < 2; i++, v1 += 4)
	{
		v1[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
		v1[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
		v1[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
		v1[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
	}
	m_pVB_NORMAL->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�F)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_COLOR) * m_VexNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_COLOR, NULL))) {
		MessageBox(NULL, "���_�F�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_COLOR* v2;
	m_pVB_COLOR->Lock(0, 0, (void**)&v2, 0);
	for (int i = 0; i < 2; i++, v2 += 4)
	{
		v2[0].color = m_Color;                       // �J���[�̐ݒ�
		v2[1].color = m_Color;                       // �J���[�̐ݒ�
		v2[2].color = m_Color;                       // �J���[�̐ݒ�
		v2[3].color = m_Color;                       // �J���[�̐ݒ�
	}
	m_pVB_COLOR->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�e�N�X�`�����W)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_TEX) * m_VexNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_TEX, NULL))) {
		MessageBox(NULL, "�e�N�X�`�����W�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_TEX* v3;
	m_pVB_TEX->Lock(0, 0, (void**)&v3, 0);
	for (int i = 0; i < 2; i++, v3 += 4)
	{
		v3[0].tex = D3DXVECTOR2(0.25f*0.0f, (1.0f / 3)*(2 - i));            // �e�N�X�`�����W�̐ݒ�
		v3[1].tex = D3DXVECTOR2(0.25f*1.0f, (1.0f / 3)*(2 - i));            // �e�N�X�`�����W�̐ݒ�
		v3[2].tex = D3DXVECTOR2(0.25f*2.0f, (1.0f / 3)*(2 - i));            // �e�N�X�`�����W�̐ݒ�
		v3[3].tex = D3DXVECTOR2(0.25f*3.0f, (1.0f / 3)*(2 - i));            // �e�N�X�`�����W�̐ݒ�
	}
	m_pVB_TEX->Unlock();
}

//=======================================================================================
// �|���S���̃o�b�t�@�ݒ�
//=======================================================================================
void CMeshCube::MakeBuff(void)
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
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * (m_PolygonNum+2),        // ���_���iWORD��16Bid�j
									D3DUSAGE_WRITEONLY,              // �g�p�p�r�t���O�i�������ނ̂݁j
									D3DFMT_INDEX16,                  // �f�[�^�̃t�H�[�}�b�g�i32Bid�ݒ肵����16��32�ɕύX�j
									D3DPOOL_MANAGED,                 // �������̊Ǘ����@�i���C���j
									&m_pIdxBuff,              // �o�b�t�@�\�C���^�[�t�F�C�X�|�C���^�̃A�h���X
									NULL);

	// �C���f�b�N�X���i�[�p�^���o�b�t�@�̐錾
	WORD* pIdx;

	// ���b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0] = 4;
	pIdx[1] = 5;
	pIdx[2] = 7;
	pIdx[3] = 6;
	pIdx[4] = 2;
	pIdx[5] = 5;
	pIdx[6] = 1;
	pIdx[7] = 4;
	pIdx[8] = 0;
	pIdx[9] = 7;
	pIdx[10] = 3;
	pIdx[11] = 2;
	pIdx[12] = 0;
	pIdx[13] = 1;

	// ���b�N���
	m_pIdxBuff->Unlock();
}
