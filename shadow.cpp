//=============================================================================
// 影
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "shadow.h"

CShadow *CShadow::m_pShadow = NULL;

CShadow::CShadow() : CScene2D(CScene::OBJTYPE_SHADOW)
{
}

CShadow::~CShadow()
{
}
CShadow *CShadow::Clear()
{
	if (m_pShadow == NULL)
	{
		m_pShadow = new CShadow;
		m_pShadow->Init();
	}
	return m_pShadow;
}

//==============================================================================
//  初期化処理
//==============================================================================
void CShadow::Init( void )
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_Color = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	m_pTexture = NULL;

	CScene2D::Init();

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_SHADOW);
}

//==============================================================================
//  終了処理
//==============================================================================
void CShadow::Uninit( void )
{
	CScene2D::Uninit();
}

//==============================================================================
//  更新処理
//==============================================================================
void CShadow::Update( void )
{
}

//==============================================================================
//  描画処理
//==============================================================================
void CShadow::Draw( void )
{
	return;
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// ステンシル値が1以上なら影を半透明で描画
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
		D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
		D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	CScene2D::Draw();

	// 描画ステータスの復帰
	pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}
