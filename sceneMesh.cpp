//=============================================================================
// ���b�V������
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sceneMesh.h"

//*************
// ���C������
//*************
CSceneMesh::CSceneMesh(int Priority) :CScene(Priority),
m_pVB_POS(NULL),
m_pVB_NORMAL(NULL),
m_pVB_COLOR(NULL),
m_pVB_TEX(NULL)
{
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

CSceneMesh::~CSceneMesh()
{
}

//=======================================================================================
//   ����������
//=======================================================================================
void CSceneMesh::Init(void)
{
	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_FIELD);
}

//=======================================================================================
//   �I������
//=======================================================================================
void CSceneMesh::Uninit()
{
	SAFE_RELEASE(m_pVB_POS);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVB_NORMAL);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVB_COLOR);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVB_TEX);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE( m_pVtxBuff );      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pIdxBuff);      // �C���f�b�N�X�o�b�t�@�̔j��
	CScene::Release();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CSceneMesh::Update()
{
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CSceneMesh::Draw()
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
	LPDIRECT3DVERTEXDECLARATION9 pDecl = *CVertexDecl::Get(CVertexDecl::TYPE_3D);
	pDevice->SetVertexDeclaration(pDecl);

	// �X�g���[���Ƃ��Ē��_�o�b�t�@��ݒ�
	pDevice->SetStreamSource(0, m_pVB_POS, 0, sizeof(CVertexDecl::VERTEX3D_POS));
	pDevice->SetStreamSource(1, m_pVB_NORMAL, 0, sizeof(CVertexDecl::VERTEX3D_NORMAL));
	pDevice->SetStreamSource(2, m_pVB_COLOR, 0, sizeof(CVertexDecl::VERTEX3D_COLOR));
	pDevice->SetStreamSource(3, m_pVB_TEX, 0, sizeof(CVertexDecl::VERTEX3D_TEX));

	// �f�o�C�X�ɃC���f�b�N�X�o�b�t�@�̐ݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// �`�撼�O�Ƀe�N�X�`�����Z�b�g�i�e�N�X�`���̐ݒ�j
	pDevice->SetTexture(0, m_pTexture);

	// �C���f�b�N�X�v���~�e�B�u�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,                 // �v���~�e�B�u�̎��
		0,
		0,
		m_VexNum,   // ���_��
		0,
		m_PolygonNum);                       // �v���~�e�B�u�̐��i�|���S���̐��j
}
