//*****************************************************************************
//   �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "scene.h"
#include "sceneModelX.h"
#include "shaderManager.h"
#include "shaderBase.h"
#include "shaderModel.h"

//=======================================================================================
//   �R���X�g���N�^
//=======================================================================================
CSceneModelX::CSceneModelX(int Priority) :CScene(Priority)
{
	// �����o�ϐ��̏�����
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//=======================================================================================
//   �f�X�g���N�^
//=======================================================================================
CSceneModelX::~CSceneModelX()
{
}

//=======================================================================================
//   ����������
//=======================================================================================
void CSceneModelX::Init()
{
	// �e�N�X�`���Z�b�g
	m_pTexture = CTexture::GetTexture((int)CTexture::TEXTYPE_WHITE);
}

//=======================================================================================
//   �I������
//=======================================================================================
void CSceneModelX::Uninit()
{
	CScene::Release();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CSceneModelX::Update()
{
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CSceneModelX::Draw()
{
	if (m_Model.pBuffMat == NULL) { return; }

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
	D3DXMatrixRotationYawPitchRoll( &mtxRot,
									m_Rot.y,
									m_Rot.x,
									m_Rot.z );

	// ���[�J���X�P�[���̑��
	D3DXMatrixScaling( &mtxScl,
					   m_Scl.x,
					   m_Scl.y,
					   m_Scl.z );

	// ���[�J�����W�̑��
	D3DXMatrixTranslation( &mtxPos,
						   m_Pos.x,
						   m_Pos.y,
						   m_Pos.z );
	
	// ���[���h��񏈗�
	D3DXMatrixIdentity( &mtxWorld );                       // ���[���h�̒��g��������
	D3DXMatrixMultiply( &mtxWorld, &mtxWorld, &mtxRot );   // ���[���h��]�̑��
	D3DXMatrixMultiply( &mtxWorld, &mtxWorld, &mtxScl );   // ���[���h�X�P�[���̑��
	D3DXMatrixMultiply( &mtxWorld, &mtxWorld, &mtxPos );   // ���[���h���W�̑��
	pDevice->SetTransform( D3DTS_WORLD, &mtxWorld );       // ���[���h���Z�b�g

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial( &matDef );                 // ���݃f�o�C�X�ɐݒ肳��Ă�A�e���A�������擾

	D3DXMATERIAL* pMat;
	pMat = (D3DXMATERIAL*)m_Model.pBuffMat->GetBufferPointer();

	// �V�F�[�_�̃Z�b�g
	CShaderModel *pShaderModel = CShaderManager::GetModel();
	pShaderModel->Set();
	pShaderModel->SetVertexInfo(mtxWorld);

	for( int i = 0; i < (int)m_Model.NumMat; i++ )
	{
		// �}�e���A���̐ݒ�
		pShaderModel->SetPixelInfo(m_Pos, pMat[i].MatD3D.Diffuse);

		if (pMat[i].pTextureFilename == NULL)
		{
			MessageBox(NULL, "�e�N�X�`���擾���s", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		}
		// �e�N�X�`��ID�擾
		UINT samplerID = pShaderModel->GetSamplerIndex();

		// �e�N�X�`���̕`��
		pDevice->SetTexture(samplerID, m_Model.pTexture[i]);
			//pDevice->SetTexture( 0, m_pTexture );         // �e�N�X�`���}�b�s���O(��)
		
		// ���b�V���̕`��
		m_Model.pMesh->DrawSubset(i);
	}
	// �V�F�[�_�N���A
	pShaderModel->Clear();
}