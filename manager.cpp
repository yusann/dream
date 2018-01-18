//=============================================================================
// マネージャー処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "inputKey.h"
#include "sound.h"

#include "mode.h"
#include "modeTitle.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "modelX.h"
#include "motionPartsX.h"

#include "scene.h"
#include "scene2D.h"

#include "scene3D.h"

#include "sceneMesh.h"
#include "meshField.h"
#include "meshCube.h"

#include "sceneBillboard.h"

#include "sceneModelX.h"
#include "sceneMotionPartsX.h"
#include "player.h"
#include "enemy.h"

#include "shaderManager.h"

//*****************************************************************************
//   静的メンバー変数宣言
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;                      // レンダラー
CSound *CManager::m_pSound = NULL;
CMode *CManager::m_pMode = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;

CManager::CManager()
{
}

CManager::~CManager()
{
}

//==================================================================================================================================================
// 初期化処理
//==================================================================================================================================================
HRESULT CManager::Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	// レンダラーの生成
	m_pRenderer = new CRenderer;
	m_pRenderer->Init( hWnd, bWindow );

	// キー判定の生成
	CInputKey::Init(hInstance, hWnd);

	// テクスチャを読み込み
	CTexture::Init();

	// モデルを読み込み
	CModelX::Init();

	// パーツモデルを読込
	CMotionPartsX::Init();

	// シェーダの読み込み
	CShaderManager::Init();

	// サウンドの生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// カメラの生成
	m_pCamera = new CCamera;
	m_pCamera->Init();

	// ライトの生成
	m_pLight = new CLight;
	m_pLight->Init();

	// オブジェクトの生成
	SetMode(new CModeTitle);


#ifdef _DEBUG
	ImGui_ImplDX9_Init(hWnd, GetRenderer()->GetDevice());
#endif

	return S_OK;

}

//==================================================================================================================================================
// 終了処理
//==================================================================================================================================================
void CManager::Uninit(void)
{
	SAFE_UNINIT(m_pMode);

	// オブジェクトの破棄
	CScene::ReleaseAll();

	// シェーダの破棄
	CShaderManager::Uninit();

	// パーツモデル破棄
	CMotionPartsX::Uninit();

	// モデルを破棄
	CModelX::Uninit();

	// テクスチャを破棄
	CTexture::Uninit();

	// カメラの破棄
	SAFE_UNINIT(m_pCamera);

	// ライトの破棄
	SAFE_UNINIT(m_pLight);

	// サウンドの破棄
	SAFE_UNINIT(m_pSound);

	// キー判定の破棄
	CInputKey::Uninit();

	// レンダラーの破棄
	SAFE_UNINIT(m_pRenderer);
}

//==================================================================================================================================================
// 更新処理
//==================================================================================================================================================
void CManager::Update(void)
{
#ifdef _DEBUG
	// ImGuiを作成
	ImGui_ImplDX9_NewFrame();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
#endif
	CInputKey::Update();			// キー判定更新
	m_pCamera->Update();			// カメラ更新
	m_pLight->Update();				// ライト更新

	// 更新処理
	CScene::UpdateAll();        // シーン
	m_pMode->Update();
}

//==================================================================================================================================================
// 描画処理
//==================================================================================================================================================
void CManager::Draw(void)
{
	m_pCamera->Set();		// カメラセット
	m_pLight->Set();		// ライトセット

	// 描画開始
	if (m_pRenderer->DrawBegin())
	{

		LPDIRECT3DDEVICE9 pDevice = NULL;
		pDevice = m_pRenderer->GetDevice();
		if (pDevice == NULL) {
			MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
			return;
		}

		D3DVIEWPORT9 backViewPort;
		D3DVIEWPORT9 viewPort = m_pLight->GetViewPort();
		LPDIRECT3DSURFACE9 campus, back, backZBuffer;
		LPDIRECT3DSURFACE9 ZBuffer = m_pLight->GetZBufferSurface();

		//pDevice->GetViewport(&backViewPort);
		pDevice->GetRenderTarget(0, &back);
		pDevice->GetDepthStencilSurface(&backZBuffer);
		m_pLight->GetTexture()->GetSurfaceLevel(0, &campus);

		//pDevice->SetViewport(&viewPort);
		pDevice->SetRenderTarget(0, campus);
		pDevice->SetDepthStencilSurface(ZBuffer);

		// バックバッファ＆Ｚバッファのクリア
		pDevice->Clear(0, NULL,                                 //
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,   // カラーバッファ | 深さ（深度）バッファ（クリアフラグ）
			D3DCOLOR_RGBA(255, 255, 255, 255),                       // 初期化色
			1.0f,                                                    // 0~1（0は手前、1は遠い）
			0);

		CScene::DrawDepthAll();             // シーン

		pDevice->SetRenderTarget(0, back);
		pDevice->SetDepthStencilSurface(backZBuffer);
		//pDevice->SetViewport(&backViewPort);

		// 描画処理
		CScene::DrawAll();             // シーン



#ifdef _DEBUG
		ImGui::Render();
#endif

		// 描画終了
		m_pRenderer->DrawEnd();
	}
}

//==================================================================================================================================================
// モードのセット処理
//==================================================================================================================================================
void CManager::SetMode(CMode *pMode)
{
	if (m_pMode != NULL)
	{
		m_pMode->Uninit();
		delete m_pMode;
	}
	m_pMode = pMode;
	if (m_pMode != NULL)
	{
		m_pMode->Init();
	}
}
