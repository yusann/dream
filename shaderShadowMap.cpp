//=============================================================================
// ���f���p�V�F�[�_����
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "shaderBase.h"
#include "shaderShadowMap.h"
#include "light.h"
#include "camera.h"
#include "texture.h"

//*************
// ���C������
//*************
CShaderShadowMap::CShaderShadowMap( ){
	Delete();
}

CShaderShadowMap::~CShaderShadowMap(){
	Delete();
}

//=======================================================================================
//   ����
//=======================================================================================
void CShaderShadowMap::Create()
{
	// �ϐ�������
	Delete();

	// �V�F�[�_�[�̐���
	CreateFX("shader/shadowMap.fx");

	// �V�F�[�_�v���O�����փe�N�j�b�N�ւ̃n���h���̎擾
	m_hTech = m_pFX->GetTechniqueByName("BasicTech");

	// �V�F�[�_�[�v���O�����̃O���[�o���ϐ��̃n���h���̎擾
	m_hMtxLightWVP = m_pFX->GetParameterByName(0, "g_mtxLightWVP");
	m_hMtxLightWV = m_pFX->GetParameterByName(0, "g_mtxLightWV");
	m_hFar = m_pFX->GetParameterByName(0, "g_far");
}

//=======================================================================================
//   �����o�[�ϐ��N���A
//=======================================================================================
void CShaderShadowMap::Delete()
{
	SAFE_RELEASE(m_pFX);
}

//=======================================================================================
//   ���f���p�V�F�[�_�̊J�n
//=======================================================================================
void CShaderShadowMap::Begin(const int pass)
{
	// �e�N�j�b�N�̐ݒ�i�V�F�[�_�v���O�����̐ݒ�j
	m_pFX->SetTechnique(m_hTech);
	m_pFX->CommitChanges();

	// �V�F�[�_�v���O�����̊J�n�錾
	m_pFX->Begin(0, 0);
	m_pFX->BeginPass(pass);
}

//=======================================================================================
//   ���f���p�V�F�[�_�̏I��
//=======================================================================================
void CShaderShadowMap::End(void)
{
	// �V�F�[�_�v���O�����̏I���錾
	m_pFX->EndPass();
	m_pFX->End();
}

//=======================================================================================
//   ���_�V�F�[�_�̏�����
//=======================================================================================
void CShaderShadowMap::SetVertexInfo( const D3DXMATRIX mtxW, const float contourScl )			// ���[���h���W
{
	// �J�������擾
	CCamera* pCamera = CManager::GetCamera();
	// �r���[�s��
	D3DXMATRIX view = pCamera->GetMtxView();
	// �v���W�F�N�V�����s��
	D3DXMATRIX proj = pCamera->GetMtxProj();
	// ���[���h�E�r���[�E�v���W�F�N�V�����s��
	D3DXMATRIX mtxWVP = mtxW * view * proj;
	// �t�]�u�s��
	D3DXMATRIX mtxWIT;
	D3DXMatrixInverse(&mtxWIT, NULL, &mtxW);
	D3DXMatrixTranspose(&mtxWIT, &mtxWIT);

	// �����
	m_pFX->SetMatrix(m_hMtxLightWVP, &mtxWVP);
	m_pFX->SetMatrix(m_hMtxLightWV, &mtxWIT);
	m_pFX->SetFloat(m_hFar, contourScl);
}
