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

	// サウンドの生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// カメラの生成
	m_pCamera = new CCamera;
	m_pCamera->Init();

	// ライトの生成
	m_pLight = new CLight;
	m_pLight->Init();

	// テクスチャを読み込み
	CTexture::Init();

	// モデルを読み込み
	CModelX::Init();

	CMotionPartsX::Init();

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
