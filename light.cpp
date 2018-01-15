//*****************************************************************************
//   インクルードファイル
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "light.h"
#include "camera.h"

//=======================================================================================
//   コンストラクタ
//=======================================================================================
CLight::CLight()
{
	D3DXMatrixIdentity(&m_MtxView);
	D3DXMatrixIdentity(&m_MtxProj);
}

//=======================================================================================
//   デストラクタ
//=======================================================================================
CLight::~CLight()
{
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CLight::Init()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));              // 初期化  ={0}も可
	m_Light.Type = D3DLIGHT_DIRECTIONAL;             // タイプ
	m_Light.Position = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);       // 平行光源（ライトの色）
	m_Light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);       // 環境光
	m_Light.Direction = D3DXVECTOR3(1.0f, -1.0f, 1.0f);               // 向き
	// 単位ベクトルの算出
	D3DXVECTOR3	vecDir = -1.0f * m_Light.Position;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &vecDir);

	m_pTexture = NULL;
	D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &m_pTexture);
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CLight::Uninit()
{
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CLight::Update()
{
}

//=======================================================================================
//   セット処理
//=======================================================================================
void CLight::Set()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// プロジェクション行列
	D3DXMatrixPerspectiveFovLH(&m_MtxProj,				// Fovは画角
		D3DX_PI / 3.0f,										// 画角（視野角）60度にするためπ÷３
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,			// アスペクト比（floatで計算する、float>intなので片方でOK）
		1.0f,											// near 必ず0.0fより大きいこと  どこから描画するか
		10000.0f);										// far どこまで描画するか
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProj);

	// ビュー行列の作成 LH左手座標系
	D3DXVECTOR3	pos = m_Light.Position;
	D3DXMatrixLookAtLH(&m_MtxView, &pos, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // Eye,At,Upの情報からビュー行列(mtxView)を作る関数

																	  // ビュー行列セット
	pDevice->SetTransform(D3DTS_VIEW, &m_MtxView);
}