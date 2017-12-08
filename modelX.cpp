//=============================================================================
// X���f�����\�[�X
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "modelX.h"

//   �ÓI�����o�ϐ��錾
CModelX::MODELX		CModelX::m_modelX[TYPE_MAX] = {};

// �e�N�X�`���p�X
char CModelX::m_TexName[TYPE_MAX][128] =
{
	"data/MODEL/player.x",
	"data/MODEL/enemy000.x",
	"data/MODEL/block00.x"
};

//*************
// ���C������
//*************
CModelX::CModelX()
{
}

CModelX::~CModelX()
{
}

//=======================================================================================
//   ����������
//=======================================================================================
void CModelX::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	for (int j = 0; j < TYPE_MAX; j++)
	{
		// �}�b�s���O�p�e�N�X�`���C���^�[�t�F�[�X�̃����[�X����
		for (int i = 0; i < MODEL_MATERIAL_MAX; i++)
		{
			m_modelX[j].pTexture[i] = NULL;
		}

		// ���f���̃G���[�`�F�b�N
		if (FAILED(D3DXLoadMeshFromX(m_TexName[j],              // �t�@�C����
			D3DXMESH_MANAGED,        // 
			pDevice,                 // �f�o�C�X
			NULL,
			&m_modelX[j].pBuffMat,        // ���f���̃}�e���A�����
			NULL,
			&m_modelX[j].NumMat,         // �}�e���A����
			&m_modelX[j].pMesh)))          // ���b�V�����
		{
			MessageBox(NULL, "���f��������܂���I", "�G���[", MB_OK | MB_ICONASTERISK);         // �I�����郁�b�Z�[�W
		}
		D3DXMATERIAL* pMat;
		pMat = (D3DXMATERIAL*)m_modelX[j].pBuffMat->GetBufferPointer();

		for (int i = 0; i < (int)m_modelX[j].NumMat; i++)
		{
			// �e�N�X�`���̐ݒ�
			if (pMat[i].pTextureFilename != NULL)
			{
				// �e�N�X�`���̓ǂݍ���(�f�B�X�N����)
				if (FAILED(D3DXCreateTextureFromFile(pDevice, pMat[i].pTextureFilename, &m_modelX[j].pTexture[i])))
				{
					MessageBox(NULL, "�摜������܂���I", "�G���[", MB_OK | MB_ICONASTERISK);         // �I�����郁�b�Z�[�W
					// �Ȃ����ɔ����e�N�X�`������
					m_modelX[j].pTexture[i] = CTexture::GetTexture((int)CTexture::TEXTYPE_WHITE);
				}
			}
			else
			{
				// �Ȃ����ɔ����e�N�X�`������
				m_modelX[j].pTexture[i] = NULL;
			}
		}
	}
}

//=======================================================================================
//   �I������
//=======================================================================================
void CModelX::Uninit()
{
	for (int j = 0; j < TYPE_MAX; j++)
	{
		// ���b�V�����̃����[�X����
		if (m_modelX[j].pMesh != NULL) {
			m_modelX[j].pMesh->Release();
			m_modelX[j].pMesh = NULL;
		}

		// �}�e���A�����̃����[�X����
		if (m_modelX[j].pBuffMat != NULL) {
			m_modelX[j].pBuffMat->Release();
			m_modelX[j].pBuffMat = NULL;
		}

		// �}�b�s���O�p�e�N�X�`���C���^�[�t�F�[�X�̃����[�X����
		for (int i = 0; i < MODEL_MATERIAL_MAX; i++)
		{
			if (m_modelX[j].pTexture[i] != NULL) {
				m_modelX[j].pTexture[i]->Release();
				m_modelX[j].pTexture[i] = NULL;
			}
		}
	}
}

CModelX::MODELX CModelX::GetModelX(TYPE type)
{
	return m_modelX[type];
}
