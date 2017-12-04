//=============================================================================
// モデル用シェーダ処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "shaderBase.h"
#include "shaderModel.h"
#include "light.h"
#include "camera.h"

//*************
// メイン処理
//*************
CShaderModel::CShaderModel( ){
	Delete();
}

CShaderModel::~CShaderModel(){
	Delete();
}

//=======================================================================================
//   生成
//=======================================================================================
void CShaderModel::Create()
{
	// 変数初期化
	Delete();

	// シェーダーの生成
	CreateVertex("shader/modelVS.hlsl");
	CreatePixel("shader/modelPS.hlsl");
}

//=======================================================================================
//   メンバー変数クリア
//=======================================================================================
void CShaderModel::Delete()
{
	SAFE_RELEASE(m_pPixel);
	SAFE_RELEASE(m_pPixelTable);
	SAFE_RELEASE(m_pVertex);
	SAFE_RELEASE(m_pVertexTable);
}

//=======================================================================================
//   モデル用シェーダのセット
//=======================================================================================
void CShaderModel::Set(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::Create()のpDeveceのNULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// シェーダーのセット
	pDevice->SetVertexShader(m_pVertex);
	pDevice->SetPixelShader(m_pPixel);
}

//=======================================================================================
//   モデル用シェーダのクリア
//=======================================================================================
void CShaderModel::Clear(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::Create()のpDeveceのNULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// シェーダーのクリア
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
}

//=======================================================================================
//   頂点シェーダの情報を代入
//=======================================================================================
void CShaderModel::SetVertexInfo( const D3DXMATRIX mtxW )			// ワールド座標
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::Create()のpDeveceのNULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// カメラ情報取得
	CCamera* pCamera = CManager::GetCamera();
	// ビュー行列
	D3DXMATRIX view = pCamera->GetMtxView();
	// プロジェクション行列
	D3DXMATRIX proj = pCamera->GetMtxProj();
	// ワールド・ビュー・プロジェクション行列
	D3DXMATRIX mtxWVP = mtxW * view * proj;

	// 情報代入
	m_pVertexTable->SetMatrix(pDevice, "mtxWVP", &mtxWVP);
	m_pVertexTable->SetMatrix(pDevice, "mtxW", &mtxW);
}

//=======================================================================================
//   ピクセルシェーダの情報を代入
//=======================================================================================
void CShaderModel::SetPixelInfo(const D3DXVECTOR3 modelPos,		// ターゲット座標
								const D3DCOLORVALUE diffColor,	// ディフューズカラー
								const float specularPower		// スペキュラーパワー
)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::Create()のpDeveceのNULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// ライト情報取得
	CLight *pLight = CManager::GetLight();
	// ライトベクトル（ワールド）
	D3DXVECTOR3 lightDirW = pLight->GetLight().vecDir;
	D3DXVec3Normalize(&lightDirW, &lightDirW);

	// カメラ情報取得
	CCamera *pCamera = CManager::GetCamera();
	// カメラ座標（ワールド）
	D3DXVECTOR3 posEyeW = pCamera->GetPosEye();

	// 情報代入
	m_pPixelTable->SetValue(pDevice, "lightDirW", &lightDirW, sizeof(lightDirW));
	m_pPixelTable->SetValue(pDevice, "posEyeW", &posEyeW, sizeof(posEyeW));
	m_pPixelTable->SetValue(pDevice, "diffColor", &diffColor, sizeof(diffColor));
	m_pPixelTable->SetFloat(pDevice, "specularPower", specularPower);
}

//=======================================================================================
//   テクスチャIDの取得
//=======================================================================================
UINT CShaderModel::GetSamplerIndex(void)
{
	return m_pPixelTable->GetSamplerIndex("tex");
}