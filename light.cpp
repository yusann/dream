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
	m_PosEye = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	m_PosAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Direction = D3DXVECTOR3(1.0f, -1.0f, 1.0f);               // 向き

	m_Far = 3000.0f;
	m_DepthEpsilon = 5.0f;
	m_DepthEpsilonScl = 1.0f;
	// 単位ベクトルの算出
	D3DXVECTOR3	vecDir = -1.0f *m_PosEye;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Direction, &vecDir);

	m_pTexture = NULL;
	D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &m_pTexture);
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
	static float posX = 500.0f;
	static float posY = 1000.0f;
	static float posZ = 500.0f;
	ImGui::DragFloat("LightFar", &m_Far, 10.0f);
	ImGui::DragFloat("LightposX", &posX, 1.0f);
	ImGui::DragFloat("LightposY", &posY, 1.0f);
	ImGui::DragFloat("LightposZ", &posZ, 1.0f);
	ImGui::DragFloat("Depth Epsilon", &m_DepthEpsilon, 0.01f);
	ImGui::InputFloat("Depth Epsilon Scl", &m_DepthEpsilonScl);
	m_PosEye = D3DXVECTOR3(posX, posY, posZ);

	// 単位ベクトルの算出
	D3DXVECTOR3	vecDir = -1.0f *m_PosEye;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Direction, &vecDir);

	ImGui::Text("Light Direction(%.3f,%.3f,%.3f)", m_Direction.x, m_Direction.y, m_Direction.z);
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
		m_Far);										// far どこまで描画するか

	// ビュー行列の作成 LH左手座標系
	D3DXMatrixLookAtLH(&m_MtxView, &m_PosEye, &m_PosAt, &m_VecUp);    // Eye,At,Upの情報からビュー行列(mtxView)を作る関数
}