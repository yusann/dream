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
	CreateFX("shader/model.fx");


	// �V�F�[�_�v���O�����փe�N�j�b�N�ւ̃n���h���̎擾
	m_hTech = m_pFX->GetTechniqueByName("BasicTech");

	// �V�F�[�_�[�v���O�����̃O���[�o���ϐ��̃n���h���̎擾
	m_hMtxWVP = m_pFX->GetParameterByName(0, "g_mtxWVP");
	m_hMtxW = m_pFX->GetParameterByName(0, "g_mtxW");

	m_hLightDirW = m_pFX->GetParameterByName(0, "g_lightDirW");
	m_hPosEyeW = m_pFX->GetParameterByName(0, "g_posEyeW");
	m_hDiffColor = m_pFX->GetParameterByName(0, "g_diffColor");
	m_hSpecularPower = m_pFX->GetParameterByName(0, "g_specularPower");

	m_hTexture = m_pFX->GetParameterByName(0, "g_texture");
}

//=======================================================================================
//   �����o�[�ϐ��N���A
//=======================================================================================
void CShaderModel::Delete()
{
	SAFE_RELEASE(m_pFX);
}

//=======================================================================================
//   ���f���p�V�F�[�_�̃N���A
//=======================================================================================
void CShaderModel::SetTech(void)
{
	// �e�N�j�b�N�̐ݒ�i�V�F�[�_�v���O�����̐ݒ�j
	m_pFX->SetTechnique(m_hTech);
}
//=======================================================================================
//   ���f���p�V�F�[�_�̃Z�b�g
//=======================================================================================
void CShaderModel::Begin(const int pass)
{
	m_pFX->CommitChanges();

	// �V�F�[�_�v���O�����̊J�n�錾
	m_pFX->Begin(0, 0);
	m_pFX->BeginPass(pass);
}

//=======================================================================================
//   ���f���p�V�F�[�_�̃N���A
//=======================================================================================
void CShaderModel::End(void)
{
	// �V�F�[�_�v���O�����̏I���錾
	m_pFX->EndPass();
	m_pFX->End();
}

//=======================================================================================
//   ���_�V�F�[�_�̏�����
//=======================================================================================
void CShaderModel::SetVertexInfo( const D3DXMATRIX mtxW )			// ���[���h���W
{
	// �J�������擾
	CCamera* pCamera = CManager::GetCamera();
	// �r���[�s��
	D3DXMATRIX view = pCamera->GetMtxView();
	// �v���W�F�N�V�����s��
	D3DXMATRIX proj = pCamera->GetMtxProj();
	// ���[���h�E�r���[�E�v���W�F�N�V�����s��
	D3DXMATRIX mtxWVP = mtxW * view * proj;

	// �����
	m_pFX->SetMatrix(m_hMtxWVP, &mtxWVP);
	m_pFX->SetMatrix(m_hMtxW, &mtxW);
}

//=======================================================================================
//   �s�N�Z���V�F�[�_�̏�����
//=======================================================================================
void CShaderModel::SetPixelInfo(const D3DCOLORVALUE diffColor,	// �f�B�t���[�Y�J���[
								const LPDIRECT3DTEXTURE9 texture,
								const float specularPower		// �X�y�L�����[�p���[
)
{
	// ���C�g���擾
	CLight *pLight = CManager::GetLight();
	// ���C�g�x�N�g���i���[���h�j
	D3DXVECTOR3 lightDirW = pLight->GetDir();
	D3DXVec3Normalize(&lightDirW, &lightDirW);

	// �J�������擾
	CCamera *pCamera = CManager::GetCamera();
	// �J�������W�i���[���h�j
	D3DXVECTOR3 posEyeW = pCamera->GetPosEye();

	// �����
	m_pFX->SetValue(m_hLightDirW, &lightDirW, sizeof(lightDirW));
	m_pFX->SetValue(m_hPosEyeW, &posEyeW, sizeof(posEyeW));
	m_pFX->SetValue(m_hDiffColor, &diffColor, sizeof(diffColor));
	m_pFX->SetFloat(m_hSpecularPower, specularPower);
	m_pFX->SetTexture(m_hTexture, texture);
}