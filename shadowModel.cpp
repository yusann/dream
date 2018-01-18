//=============================================================================
// 影
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "shadowModel.h"
#include "light.h"

CShadowModel::CShadowModel() : CScene2D(CScene::OBJTYPE_SHADOW)
{
}

CShadowModel::~CShadowModel()
{
}

//==============================================================================
//  生成処理
//==============================================================================
CShadowModel *CShadowModel::Create()
{
	CShadowModel *pSceneMD;                            // 変数宣言
	pSceneMD = new CShadowModel();
	pSceneMD->Init();                            // 初期化
	return pSceneMD;                             // 値を返す
}

//==============================================================================
//  初期化処理
//==============================================================================
void CShadowModel::Init( void )
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
void CShadowModel::Uninit( void )
{
	CScene2D::Uninit();
}

//==============================================================================
//  更新処理
//==============================================================================
void CShadowModel::Update( void )
{
}

//==============================================================================
//  描画処理
//==============================================================================
void CShadowModel::Draw( void )
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// ステンシルの設定
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);			// ステンシル有効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// Zバッファ書き込まない
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);			// カラー書き込まない
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0x000000ff);		// ステンシルマスク

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);	// 比較関数（必ず合格）
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);				// 参照値
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Zバッファで引っかかった時（何もしない）
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// 両方ダメだった時（何もしない）

	// シャドウボリュームの表をステンシルに描画
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);		// 両方に通った時（+1）
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	DrawStencilShadowAll();

	// シャドウボリュームの裏をステンシルに描画
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);		// 両方に通った時（-1）
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	
	DrawStencilShadowAll();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);			// カラー書き込む可能
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);				// 参照値
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);	// 比較関数（以下なら）

	//CScene2D::Draw();

	// 描画ステータスの復帰
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}
