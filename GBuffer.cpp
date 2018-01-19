//=============================================================================
// Gバッファ（デファードレンダリング）
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
//   初期化処理
//=======================================================================================
void CGBuffer::Init(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの生成
	//D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
	//	D3DUSAGE_RENDERTARGET, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &m_pTextureColor);
	D3DXCreateTexture(pDevice, 2048, 2048, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &m_pTextureColor);
	D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &m_pTextureNormal);
	D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_A32B32G32R32F, D3DPOOL_DEFAULT, &m_pTexturePosition);

	// サーフェイスの生成
	m_pTextureColor		->GetSurfaceLevel(0, &m_pSurfaceColor);
	m_pTextureNormal	->GetSurfaceLevel(0, &m_pSurfaceNormal);
	m_pTexturePosition	->GetSurfaceLevel(0, &m_pSurfacePosition);

	// 深度サーフェイスの生成
	pDevice->CreateDepthStencilSurface(2048, 2048, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, FALSE,
		&m_pSurfaceDepth, NULL);

	// デバイスのサーフェイス取得
	pDevice->GetRenderTarget(0, &m_pBackSurface);
	// デバイスの深度サーフェイス取得
	pDevice->GetDepthStencilSurface(&m_pBackDepth);

	m_pDebugDrawColor = CDebugShadowMap::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH*0.2f, SCREEN_HEIGHT*0.2f, 0.0f));
}

//=======================================================================================
//   終了処理
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

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL,                                 //
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,   // カラーバッファ | 深さ（深度）バッファ（クリアフラグ）
		D3DCOLOR_RGBA(255, 255, 255, 255),                       // 初期化色
		1.0f,                                                    // 0~1（0は手前、1は遠い）
		0);

	CScene::DrawDepthAll();             // シーン
	//CScene::DrawGBufferAll();

	pDevice->SetRenderTarget(0, m_pBackSurface);
	pDevice->SetRenderTarget(1, NULL);
	pDevice->SetRenderTarget(2, NULL);
	pDevice->SetDepthStencilSurface(m_pBackDepth);

	m_pDebugDrawColor->Update(m_pTextureColor);
}

//=======================================================================================
//   サーフェイスの設定
//=======================================================================================
void CGBuffer::SetSurface(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetRenderTarget(0, m_pSurfaceColor);
	pDevice->SetRenderTarget(1, m_pSurfaceNormal);
	pDevice->SetRenderTarget(2, m_pSurfacePosition);
	pDevice->SetDepthStencilSurface(m_pSurfaceDepth);
}

//=======================================================================================
//   バックバッファを戻す
//=======================================================================================
void CGBuffer::SetBack(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetRenderTarget(0, m_pBackSurface);
	pDevice->SetRenderTarget(1, NULL);
	pDevice->SetRenderTarget(2, NULL);
	pDevice->SetDepthStencilSurface(m_pBackDepth);
}