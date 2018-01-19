//=============================================================================
// G�o�b�t�@�i�f�t�@�[�h�����_�����O�j
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "GBuffer.h"
#include "scene.h"
#include "debugShadowMap.h"
#include "texture.h"

CGBuffer::CGBuffer():
	m_pTextureColor(NULL),
	m_pTextureNormal(NULL),
	m_pTexturePosition(NULL),
	m_pSurfaceColor(NULL),
	m_pSurfaceNormal(NULL),
	m_pSurfacePosition(NULL),
	m_pSurfaceDepth(NULL),
	m_pBackSurface(NULL),
	m_pBackDepth(NULL),
	m_pDebugDrawColor(NULL),
	m_pDebugDrawNormal(NULL),
	m_pDebugDrawPosition(NULL){}

//=======================================================================================
//   ����������
//=======================================================================================
void CGBuffer::Init(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̐���
	//D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
	//	D3DUSAGE_RENDERTARGET, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &m_pTextureColor);
	D3DXCreateTexture(pDevice, 2048, 2048, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &m_pTextureColor);
	D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &m_pTextureNormal);
	D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_A32B32G32R32F, D3DPOOL_DEFAULT, &m_pTexturePosition);

	// �T�[�t�F�C�X�̐���
	m_pTextureColor		->GetSurfaceLevel(0, &m_pSurfaceColor);
	m_pTextureNormal	->GetSurfaceLevel(0, &m_pSurfaceNormal);
	m_pTexturePosition	->GetSurfaceLevel(0, &m_pSurfacePosition);

	// �[�x�T�[�t�F�C�X�̐���
	pDevice->CreateDepthStencilSurface(2048, 2048, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, FALSE,
		&m_pSurfaceDepth, NULL);

	// �f�o�C�X�̃T�[�t�F�C�X�擾
	pDevice->GetRenderTarget(0, &m_pBackSurface);
	// �f�o�C�X�̐[�x�T�[�t�F�C�X�擾
	pDevice->GetDepthStencilSurface(&m_pBackDepth);

	m_pDebugDrawColor = CDebugShadowMap::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH*0.2f, SCREEN_HEIGHT*0.2f, 0.0f));
}

//=======================================================================================
//   �I������
//=======================================================================================
void CGBuffer::Uninit()
{
	SAFE_RELEASE(m_pTextureColor);
	SAFE_RELEASE(m_pTextureNormal);
	SAFE_RELEASE(m_pTexturePosition);
	SAFE_RELEASE(m_pSurfaceColor);
	SAFE_RELEASE(m_pSurfaceNormal);
	SAFE_RELEASE(m_pSurfacePosition);
	SAFE_RELEASE(m_pSurfaceDepth);
	SAFE_RELEASE(m_pBackSurface);
	SAFE_RELEASE(m_pBackDepth);
	SAFE_UNINIT(m_pDebugDrawColor);
	SAFE_UNINIT(m_pDebugDrawNormal);
	SAFE_UNINIT(m_pDebugDrawPosition);
}

void CGBuffer::SetTexture(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetRenderTarget(0, m_pSurfaceColor);
	pDevice->SetRenderTarget(1, m_pSurfaceNormal);
	pDevice->SetRenderTarget(2, m_pSurfacePosition);
	pDevice->SetDepthStencilSurface(m_pSurfaceDepth);

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	pDevice->Clear(0, NULL,                                 //
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,   // �J���[�o�b�t�@ | �[���i�[�x�j�o�b�t�@�i�N���A�t���O�j
		D3DCOLOR_RGBA(255, 255, 255, 255),                       // �������F
		1.0f,                                                    // 0~1�i0�͎�O�A1�͉����j
		0);

	CScene::DrawDepthAll();             // �V�[��
	//CScene::DrawGBufferAll();

	pDevice->SetRenderTarget(0, m_pBackSurface);
	pDevice->SetRenderTarget(1, NULL);
	pDevice->SetRenderTarget(2, NULL);
	pDevice->SetDepthStencilSurface(m_pBackDepth);

	m_pDebugDrawColor->Update(m_pTextureColor);
}

//=======================================================================================
//   �T�[�t�F�C�X�̐ݒ�
//=======================================================================================
void CGBuffer::SetSurface(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetRenderTarget(0, m_pSurfaceColor);
	pDevice->SetRenderTarget(1, m_pSurfaceNormal);
	pDevice->SetRenderTarget(2, m_pSurfacePosition);
	pDevice->SetDepthStencilSurface(m_pSurfaceDepth);
}

//=======================================================================================
//   �o�b�N�o�b�t�@��߂�
//=======================================================================================
void CGBuffer::SetBack(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetRenderTarget(0, m_pBackSurface);
	pDevice->SetRenderTarget(1, NULL);
	pDevice->SetRenderTarget(2, NULL);
	pDevice->SetDepthStencilSurface(m_pBackDepth);
}