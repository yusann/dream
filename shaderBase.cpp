//=============================================================================
// シェーダのベース
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "shaderBase.h"

//==============================================
//   コンストラクタ
//==============================================
CShaderBase::CShaderBase() :
	m_pPixel(NULL),
	m_pPixelTable(NULL),
	m_pVertex(NULL),
	m_pVertexTable(NULL)
{
}

//==============================================
//   デストラクタ
//==============================================
CShaderBase::~CShaderBase()
{
}

//=======================================================================================
//   頂点シェーダーの生成
//=======================================================================================
void CShaderBase::CreateVertex(const char* hlslFile)		// .hlslのファイル名
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
		hlslFile,		// ファイル名
		NULL,
		NULL,
		"main",				// エントリ関数
		"vs_3_0",			// シェーダーバージョン
		0,
		&code,
		&err,
		&m_pVertexTable);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile(modelVS.hlsl)", MB_OK);
		return;
	}

	// 頂点シェーダー生成
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &m_pVertex);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "CreateVertexShader(modelVS.hlsl)", MB_OK);
		return;
	}
	// ローカル破棄
	SAFE_RELEASE(err);
	SAFE_RELEASE(code);
}

//=======================================================================================
//   ピクセルシェーダーの生成
//=======================================================================================
void CShaderBase::CreatePixel(const char* hlslFile)		// .hlslのファイル名
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
		hlslFile,
		NULL,
		NULL,
		"main",				// エントリ関数
		"ps_3_0",			// シェーダーバージョン
		0,
		&code,
		&err,
		&m_pPixelTable);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile(modelPS.hlsl)", MB_OK);
		return;
	}

	// ピクセルシェーダー生成
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &m_pPixel);
	if (FAILED(hr)) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "CreatePixelShader(modelPS.hlsl)", MB_OK);
		return;
	}
	// ローカル破棄
	SAFE_RELEASE(err);
	SAFE_RELEASE(code);
}
