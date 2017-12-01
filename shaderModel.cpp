//=============================================================================
// ���f���p�V�F�[�_����
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "shaderBase.h"
#include "shaderModel.h"
#include "light.h"
#include "camera.h"

//*************
// ���C������
//*************
CShaderModel::CShaderModel( ){
	Delete();
}

CShaderModel::~CShaderModel(){
	Delete();
}

//=======================================================================================
//   ����
//=======================================================================================
void CShaderModel::Create()
{
	// �ϐ�������
	Delete();

	// �V�F�[�_�[�̐���
	CreateVertex();
	CreatePixel();
}

//=======================================================================================
//   �����o�[�ϐ��N���A
//=======================================================================================
void CShaderModel::Delete()
{
	SAFE_RELEASE(m_Pixel);
	SAFE_RELEASE(m_PixelTable);
	SAFE_RELEASE(m_Vertex);
	SAFE_RELEASE(m_VertexTable);
}

//=======================================================================================
//   ���f���p�V�F�[�_�̃Z�b�g
//=======================================================================================
void CShaderModel::Set(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::Create()��pDevece��NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �V�F�[�_�[�̃Z�b�g
	pDevice->SetVertexShader(m_Vertex);
	pDevice->SetPixelShader(m_Pixel);
}

//=======================================================================================
//   ���f���p�V�F�[�_�̃N���A
//=======================================================================================
void CShaderModel::Clear(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::Create()��pDevece��NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �V�F�[�_�[�̃N���A
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
}

//=======================================================================================
//   ���_�V�F�[�_�̏�����
//=======================================================================================
void CShaderModel::SetVertexInfo(const D3DXMATRIX mtxW,			// ���[���h���W
								const D3DCOLORVALUE diffColor)	// �f�B�t���[�Y�J���[
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::Create()��pDevece��NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �J�������擾
	CCamera* pCamera = CManager::GetCamera();
	// �r���[�s��
	D3DXMATRIX view = pCamera->GetMtxView();
	// �v���W�F�N�V�����s��
	D3DXMATRIX proj = pCamera->GetMtxProj();
	// ���[���h�E�r���[�E�v���W�F�N�V�����s��
	D3DXMATRIX mtxWVP = mtxW * view * proj;

	// �����
	m_VertexTable->SetMatrix(pDevice, "mtxWVP", &mtxWVP);
	m_VertexTable->SetMatrix(pDevice, "mtxW", &mtxW);
	m_VertexTable->SetValue(pDevice, "diffColor", &diffColor, sizeof(diffColor));
}

//=======================================================================================
//   �s�N�Z���V�F�[�_�̏�����
//=======================================================================================
void CShaderModel::SetPixelInfo(const D3DXVECTOR3 modelPos,		// �^�[�Q�b�g���W
								const float specularPower		// �X�y�L�����[�p���[
)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::Create()��pDevece��NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���C�g���擾
	CLight *pLight = CManager::GetLight();
	// ���C�g�x�N�g���i���[���h�j
	D3DXVECTOR3 lightDirW = pLight->GetLight().vecDir;
	D3DXVec3Normalize(&lightDirW, &lightDirW);

	// �J�������擾
	CCamera *pCamera = CManager::GetCamera();
	// �J�������W�i���[���h�j
	D3DXVECTOR3 posEyeW = pCamera->GetPosEye();
	// �J��������^�[�Q�b�g�̃x�N�g���i���[���h�j
	D3DXVECTOR3 toEyeW = modelPos - posEyeW;

	// �����
	m_PixelTable->SetValue(pDevice, "lightDirW", &lightDirW, sizeof(lightDirW));
	m_PixelTable->SetValue(pDevice, "posEyeW", &posEyeW, sizeof(posEyeW));
	m_PixelTable->SetFloat(pDevice, "specularPower", specularPower);
}

//=======================================================================================
//   �e�N�X�`��ID�̎擾
//=======================================================================================
UINT CShaderModel::GetSamplerIndex(void)
{
	return m_PixelTable->GetSamplerIndex("tex");
}

//=======================================================================================
//   ���_�V�F�[�_�[�̐���
//=======================================================================================
void CShaderModel::CreateVertex(void)
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
		"shader/modelPS.hlsl",		// �t�@�C����
		NULL,
		NULL,
		"main",				// �G���g���֐�
		"ps_3_0",			// �V�F�[�_�[�o�[�W����
		0,
		&code,
		&err,
		&m_PixelTable);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile(modelPS.hlsl)", MB_OK);
		return;
	}

	// �s�N�Z���V�F�[�_�[����
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &m_Pixel);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "CreatePixelShader(modelPS.hlsl)", MB_OK);
		return;
	}
	// ���[�J���j��
	SAFE_RELEASE(err);
	SAFE_RELEASE(code);
}

//=======================================================================================
//   �s�N�Z���V�F�[�_�[�̐���
//=======================================================================================
void CShaderModel::CreatePixel(void)
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
		"shader/modelVS.hlsl",		// �t�@�C����
		NULL,
		NULL,
		"main",				// �G���g���֐�
		"vs_3_0",			// �V�F�[�_�[�o�[�W����
		0,
		&code,
		&err,
		&m_VertexTable);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile(modelVS.hlsl)", MB_OK);
		return;
	}

	// ���_�V�F�[�_�[����
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &m_Vertex);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "CreateVertexShader(modelVS.hlsl)", MB_OK);
		return;
	}
	// ���[�J���j��
	SAFE_RELEASE(err);
	SAFE_RELEASE(code);
}
