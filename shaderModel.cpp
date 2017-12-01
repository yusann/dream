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
	CreateVertex();
	CreatePixel();
}

//=======================================================================================
//   メンバー変数クリア
//=======================================================================================
void CShaderModel::Delete()
{
	SAFE_RELEASE(m_Pixel);
	SAFE_RELEASE(m_PixelTable);
	SAFE_RELEASE(m_Vertex);
	SAFE_RELEASE(m_VertexTable);
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
	pDevice->SetVertexShader(m_Vertex);
	pDevice->SetPixelShader(m_Pixel);
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
void CShaderModel::SetVertexInfo(const D3DXMATRIX mtxW,			// ワールド座標
								const D3DCOLORVALUE diffColor)	// ディフューズカラー
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
	m_VertexTable->SetMatrix(pDevice, "mtxWVP", &mtxWVP);
	m_VertexTable->SetMatrix(pDevice, "mtxW", &mtxW);
	m_VertexTable->SetValue(pDevice, "diffColor", &diffColor, sizeof(diffColor));
}

//=======================================================================================
//   ピクセルシェーダの情報を代入
//=======================================================================================
void CShaderModel::SetPixelInfo(const D3DXVECTOR3 modelPos,		// ターゲット座標
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
	// カメラからターゲットのベクトル（ワールド）
	D3DXVECTOR3 toEyeW = modelPos - posEyeW;

	// 情報代入
	m_PixelTable->SetValue(pDevice, "lightDirW", &lightDirW, sizeof(lightDirW));
	m_PixelTable->SetValue(pDevice, "posEyeW", &posEyeW, sizeof(posEyeW));
	m_PixelTable->SetFloat(pDevice, "specularPower", specularPower);
}

//=======================================================================================
//   テクスチャIDの取得
//=======================================================================================
UINT CShaderModel::GetSamplerIndex(void)
{
	return m_PixelTable->GetSamplerIndex("tex");
}

//=======================================================================================
//   頂点シェーダーの生成
//=======================================================================================
void CShaderModel::CreateVertex(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::CreateVertex()のpDeveceのNULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// エラーチェック用変数
	LPD3DXBUFFER err = NULL;
	LPD3DXBUFFER code = NULL;

	// ピクセルシェーダーの読み込み
	HRESULT hr = D3DXCompileShaderFromFile(
		"shader/modelPS.hlsl",		// ファイル名
		NULL,
		NULL,
		"main",				// エントリ関数
		"ps_3_0",			// シェーダーバージョン
		0,
		&code,
		&err,
		&m_PixelTable);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile(modelPS.hlsl)", MB_OK);
		return;
	}

	// ピクセルシェーダー生成
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &m_Pixel);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "CreatePixelShader(modelPS.hlsl)", MB_OK);
		return;
	}
	// ローカル破棄
	SAFE_RELEASE(err);
	SAFE_RELEASE(code);
}

//=======================================================================================
//   ピクセルシェーダーの生成
//=======================================================================================
void CShaderModel::CreatePixel(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::CreatePixel()のpDeveceのNULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// エラーチェック用変数
	LPD3DXBUFFER err = NULL;
	LPD3DXBUFFER code = NULL;

	// 頂点シェーダーの読み込み
	HRESULT hr = D3DXCompileShaderFromFile(
		"shader/modelVS.hlsl",		// ファイル名
		NULL,
		NULL,
		"main",				// エントリ関数
		"vs_3_0",			// シェーダーバージョン
		0,
		&code,
		&err,
		&m_VertexTable);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile(modelVS.hlsl)", MB_OK);
		return;
	}

	// 頂点シェーダー生成
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &m_Vertex);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "CreateVertexShader(modelVS.hlsl)", MB_OK);
		return;
	}
	// ローカル破棄
	SAFE_RELEASE(err);
	SAFE_RELEASE(code);
}
