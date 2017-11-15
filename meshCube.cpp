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
	CSceneMesh::Draw();
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

	// ���_�o�b�t�@�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_VexNum,           // �쐬���������_�o�b�t�@�̃T�C�Y�i��̒��_*���_���j
		D3DUSAGE_WRITEONLY,                                      // �������ނ������Ȃ��i�`�F�b�N���Ȃ��j
		FVF_VERTEX_3D,                                           // �ǂ�Ȓ��_�ŏ����́i0�ɂ��Ă�OK�j
		D3DPOOL_MANAGED,                                         // �������Ǘ������C���ɂ���
		&m_pVtxBuff,
		NULL);

	// ���_���i�[�p�^���o�b�t�@�̐錾
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < 2; i++, pVtx += 4)
	{
		// ���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-0.5f, i * m_Scl.y,  0.5);
		pVtx[1].pos = D3DXVECTOR3( 0.5f, i * m_Scl.y,  0.5);
		pVtx[2].pos = D3DXVECTOR3( 0.5f, i * m_Scl.y, -0.5);
		pVtx[3].pos = D3DXVECTOR3(-0.5f, i * m_Scl.y, -0.5);

		pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
		pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
		pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
		pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�

		pVtx[0].color = m_Color;                       // �J���[�̐ݒ�
		pVtx[1].color = m_Color;                       // �J���[�̐ݒ�
		pVtx[2].color = m_Color;                       // �J���[�̐ݒ�
		pVtx[3].color = m_Color;                       // �J���[�̐ݒ�

		pVtx[0].tex = D3DXVECTOR2(0.25f*0.0f, (1.0f/3)*(2-i));            // �e�N�X�`�����W�̐ݒ�
		pVtx[1].tex = D3DXVECTOR2(0.25f*1.0f, (1.0f/3)*(2-i));            // �e�N�X�`�����W�̐ݒ�
		pVtx[2].tex = D3DXVECTOR2(0.25f*2.0f, (1.0f/3)*(2-i));            // �e�N�X�`�����W�̐ݒ�
		pVtx[3].tex = D3DXVECTOR2(0.25f*3.0f, (1.0f/3)*(2-i));            // �e�N�X�`�����W�̐ݒ�
	}
	// �����J����
	m_pVtxBuff->Unlock();
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
