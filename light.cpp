//=============================================================================
// ライト
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "light.h"
#include "camera.h"

//*****************************************************************************
//   静的メンバ変数
//*****************************************************************************
CLight::LIGHT CLight::m_light;

CLight::CLight()
{
}

CLight::~CLight()
{
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CLight::Init()
{
	int nCntLight;
	for (nCntLight = 0; nCntLight < 1; nCntLight++) {
		ZeroMemory(&m_light.light, sizeof(D3DLIGHT9));              // 初期化  ={0}も可
		m_light.light.Type = D3DLIGHT_DIRECTIONAL;             // タイプ
		m_light.light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);       // 平行光源（ライトの色）
		m_light.light.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);       // 環境光
		m_light.vecDir = D3DXVECTOR3(10.0f, -10.0f, 1.0f);               // 向き
	}

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
	int nCntLight;
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}
	// ライトの最大数分ループ
	for (nCntLight = 0; nCntLight < 1; nCntLight++) {

		// 単位ベクトルの算出
		D3DXVec3Normalize((D3DXVECTOR3*)&m_light.light.Direction, &m_light.vecDir);

		// デバイスにライトを設定
		pDevice->SetLight(nCntLight, &m_light.light);                   // nCntLight番目のライトの設定
		pDevice->LightEnable(nCntLight, TRUE);                  // nCntLight番目のライトをONにする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}