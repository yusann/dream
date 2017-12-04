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
	CreateVertex("shader/modelVS.hlsl");
	CreatePixel("shader/modelPS.hlsl");
}

//=======================================================================================
//   �����o�[�ϐ��N���A
//=======================================================================================
void CShaderModel::Delete()
{
	SAFE_RELEASE(m_pPixel);
	SAFE_RELEASE(m_pPixelTable);
	SAFE_RELEASE(m_pVertex);
	SAFE_RELEASE(m_pVertexTable);
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
	pDevice->SetVertexShader(m_pVertex);
	pDevice->SetPixelShader(m_pPixel);
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
void CShaderModel::SetVertexInfo( const D3DXMATRIX mtxW )			// ���[���h���W
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
	m_pVertexTable->SetMatrix(pDevice, "mtxWVP", &mtxWVP);
	m_pVertexTable->SetMatrix(pDevice, "mtxW", &mtxW);
}

//=======================================================================================
//   �s�N�Z���V�F�[�_�̏�����
//=======================================================================================
void CShaderModel::SetPixelInfo(const D3DXVECTOR3 modelPos,		// �^�[�Q�b�g���W
								const D3DCOLORVALUE diffColor,	// �f�B�t���[�Y�J���[
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

	// �����
	m_pPixelTable->SetValue(pDevice, "lightDirW", &lightDirW, sizeof(lightDirW));
	m_pPixelTable->SetValue(pDevice, "posEyeW", &posEyeW, sizeof(posEyeW));
	m_pPixelTable->SetValue(pDevice, "diffColor", &diffColor, sizeof(diffColor));
	m_pPixelTable->SetFloat(pDevice, "specularPower", specularPower);
}

//=======================================================================================
//   �e�N�X�`��ID�̎擾
//=======================================================================================
UINT CShaderModel::GetSamplerIndex(void)
{
	return m_pPixelTable->GetSamplerIndex("tex");
}