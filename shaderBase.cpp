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
	m_pPixel(NULL),
	m_pPixelTable(NULL),
	m_pVertex(NULL),
	m_pVertexTable(NULL)
{
}

//==============================================
//   �f�X�g���N�^
//==============================================
CShaderBase::~CShaderBase()
{
}

//=======================================================================================
//   ���_�V�F�[�_�[�̐���
//=======================================================================================
void CShaderBase::CreateVertex(const char* hlslFile)		// .hlsl�̃t�@�C����
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::CreatePixel()��pDevece��NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �G���[�`�F�b�N�p�ϐ�
	LPD3DXBUFFER err = NULL;
	LPD3DXBUFFER code = NULL;

	// ���_�V�F�[�_�[�̓ǂݍ���
	HRESULT hr = D3DXCompileShaderFromFile(
		hlslFile,		// �t�@�C����
		NULL,
		NULL,
		"main",				// �G���g���֐�
		"vs_3_0",			// �V�F�[�_�[�o�[�W����
		0,
		&code,
		&err,
		&m_pVertexTable);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile(modelVS.hlsl)", MB_OK);
		return;
	}

	// ���_�V�F�[�_�[����
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &m_pVertex);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "CreateVertexShader(modelVS.hlsl)", MB_OK);
		return;
	}
	// ���[�J���j��
	SAFE_RELEASE(err);
	SAFE_RELEASE(code);
}

//=======================================================================================
//   �s�N�Z���V�F�[�_�[�̐���
//=======================================================================================
void CShaderBase::CreatePixel(const char* hlslFile)		// .hlsl�̃t�@�C����
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::CreateVertex()��pDevece��NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �G���[�`�F�b�N�p�ϐ�
	LPD3DXBUFFER err = NULL;
	LPD3DXBUFFER code = NULL;

	// �s�N�Z���V�F�[�_�[�̓ǂݍ���
	HRESULT hr = D3DXCompileShaderFromFile(
		hlslFile,
		NULL,
		NULL,
		"main",				// �G���g���֐�
		"ps_3_0",			// �V�F�[�_�[�o�[�W����
		0,
		&code,
		&err,
		&m_pPixelTable);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile(modelPS.hlsl)", MB_OK);
		return;
	}

	// �s�N�Z���V�F�[�_�[����
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &m_pPixel);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "CreatePixelShader(modelPS.hlsl)", MB_OK);
		return;
	}
	// ���[�J���j��
	SAFE_RELEASE(err);
	SAFE_RELEASE(code);
}
