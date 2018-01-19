//=============================================================================
// ���f���p�V�F�[�_����
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "shaderBase.h"
#include "shaderManga.h"
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "GBuffer.h"

//*************
// ���C������
//*************
CShaderManga::CShaderManga( ){
	Delete();
}

CShaderManga::~CShaderManga(){
	Delete();
}

//=======================================================================================
//   ����
//=======================================================================================
void CShaderManga::Create()
{
	// �ϐ�������
	Delete();

	// �V�F�[�_�[�̐���
	CreateFX("shader/manga.fx");

	// �V�F�[�_�v���O�����փe�N�j�b�N�ւ̃n���h���̎擾
	m_hTech = m_pFX->GetTechniqueByName("BasicTech");

	// �V�F�[�_�[�v���O�����̃O���[�o���ϐ��̃n���h���̎擾
	m_hMtxWVP = m_pFX->GetParameterByName(0, "g_mtxWVP");
	m_hMtxWIT = m_pFX->GetParameterByName(0, "g_mtxWIT");
	m_hMtxWI = m_pFX->GetParameterByName(0, "g_mtxWI");
	m_hMtxW = m_pFX->GetParameterByName(0, "g_mtxW");

	m_hMtxLightWVP = m_pFX->GetParameterByName(0, "g_mtxLightWVP");
	m_hMtxLightWV = m_pFX->GetParameterByName(0, "g_mtxLightWV");
	m_hLightFar = m_pFX->GetParameterByName(0, "g_lightFar");
	m_hDepthTex = m_pFX->GetParameterByName(0, "g_depthTex");
	m_hDepthEpsilon = m_pFX->GetParameterByName(0, "g_depthEpsilon");

	m_hLightDirW = m_pFX->GetParameterByName(0, "g_lightDirW");
	m_hPosEyeW = m_pFX->GetParameterByName(0, "g_posEyeW");
	m_hDiffColor = m_pFX->GetParameterByName(0, "g_diffColor");

	m_hContourScl = m_pFX->GetParameterByName(0, "g_contourScl");

	m_hTexture = m_pFX->GetParameterByName(0, "g_texture");
	m_hAnimeDrawTex = m_pFX->GetParameterByName(0, "g_animeDrawTex");
}

//=======================================================================================
//   �����o�[�ϐ��N���A
//=======================================================================================
void CShaderManga::Delete()
{
	SAFE_RELEASE(m_pFX);
}

//=======================================================================================
//   ���f���p�V�F�[�_�̊J�n
//=======================================================================================
void CShaderManga::Begin(const int pass)
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
void CShaderManga::End(void)
{
	// �V�F�[�_�v���O�����̏I���錾
	m_pFX->EndPass();
	m_pFX->End();
}

//=======================================================================================
//   ���_�V�F�[�_�̏�����
//=======================================================================================
void CShaderManga::SetVertexInfo( const D3DXMATRIX mtxW, const float contourScl )			// ���[���h���W
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
	D3DXMATRIX mtxWIT,mtxWI;
	D3DXMatrixInverse(&mtxWI, NULL, &mtxW);
	D3DXMatrixTranspose(&mtxWIT, &mtxWI);

	// ���C�g���擾
	CLight* pLight = CManager::GetLight();
	// ���C�g�r���[�s��
	D3DXMATRIX lightView = pLight->GetMtxView();
	// ���C�g�v���W�F�N�V�����s��
	D3DXMATRIX lightProj = pLight->GetMtxProj();
	// ���C�g���[���h�E�r���[�E�v���W�F�N�V�����s��
	D3DXMATRIX mtxLightWVP = mtxW * lightView * lightProj;
	// ���C�g���[���h�E�r���[�E�v���W�F�N�V�����s��
	D3DXMATRIX mtxLightWV = mtxW * lightView;
	// ���C�g�͈͂̎擾
	float lightFar = pLight->GetFar();
	float depthEpsilon = pLight->GetDepthEpsilon() * pLight->GetDepthEpsilonScl();

	// �����
	m_pFX->SetMatrix(m_hMtxWVP, &mtxWVP);
	m_pFX->SetMatrix(m_hMtxWIT, &mtxWIT);
	m_pFX->SetMatrix(m_hMtxWI, &mtxWI);
	m_pFX->SetMatrix(m_hMtxW, &mtxW);
	m_pFX->SetFloat(m_hContourScl, contourScl);

	m_pFX->SetMatrix(m_hMtxLightWVP, &mtxLightWVP);
	m_pFX->SetMatrix(m_hMtxLightWV, &mtxLightWV);
	m_pFX->SetFloat(m_hLightFar, lightFar);
	m_pFX->SetFloat(m_hDepthEpsilon, depthEpsilon);
	D3DXVECTOR3 lightDirW = pLight->GetDir();
	D3DXVec3Normalize(&lightDirW, &lightDirW);
	m_pFX->SetValue(m_hLightDirW, &lightDirW, sizeof(lightDirW));
}

//=======================================================================================
//   �s�N�Z���V�F�[�_�̏�����
//=======================================================================================
void CShaderManga::SetPixelInfo(const D3DCOLORVALUE diffColor,		// �f�B�t���[�Y�J���[
								const LPDIRECT3DTEXTURE9 texture	// �e�N�X�`��
)
{
	// ���C�g���擾
	CLight *pLight = CManager::GetLight();
	// ���C�g�x�N�g���i���[���h�j
	D3DXVECTOR3 lightDirW = pLight->GetDir();
	D3DXVec3Normalize(&lightDirW, &lightDirW);
	// �[�x�e�N�X�`��
	//LPDIRECT3DTEXTURE9 depthTex = pLight->GetTexture();
	LPDIRECT3DTEXTURE9 depthTex = CManager::GetGBuffer()->GetTextureColor();

	// �J�������擾
	CCamera *pCamera = CManager::GetCamera();
	// �J�������W�i���[���h�j
	D3DXVECTOR3 posEyeW = pCamera->GetPosEye();

	// �����
	m_pFX->SetValue(m_hLightDirW, &lightDirW, sizeof(lightDirW));
	m_pFX->SetValue(m_hPosEyeW, &posEyeW, sizeof(posEyeW));
	m_pFX->SetValue(m_hDiffColor, &diffColor, sizeof(diffColor));
	m_pFX->SetTexture(m_hTexture, texture);
	m_pFX->SetTexture(m_hAnimeDrawTex, CTexture::GetTexture(CTexture::TEXTYPE_ANIME_DRAW));
	m_pFX->SetTexture(m_hDepthTex, depthTex);
}