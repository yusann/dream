//=============================================================================
// �V�F�[�_�̃x�[�X
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "shaderBase.h"

//==============================================
//   �R���X�g���N�^
//==============================================
CShaderBase::CShaderBase() :
	m_pFX(NULL)
{
}

//==============================================
//   �f�X�g���N�^
//==============================================
CShaderBase::~CShaderBase()
{
}

//=======================================================================================
//   �V�F�[�_�[�̐���
//=======================================================================================
void CShaderBase::CreateFX(const char* hlslFile)		// .hlsl�̃t�@�C����
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::Create()��pDevece��NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �V�F�[�_�v���O�����̓ǂݍ��݂ƃR���p�C��
	LPD3DXBUFFER	err = 0;
	D3DXCreateEffectFromFile(pDevice, TEXT(hlslFile), 0, 0, D3DXSHADER_DEBUG, 0, &m_pFX, &err);
	if (err) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "�V�F�[�_�ǂݍ��݃G���[", MB_OK);
		return;
	}
}
