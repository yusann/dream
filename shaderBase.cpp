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
	m_pFX(NULL)
{
}

//==============================================
//   デストラクタ
//==============================================
CShaderBase::~CShaderBase()
{
}

//=======================================================================================
//   シェーダーの生成
//=======================================================================================
void CShaderBase::CreateFX(const char* hlslFile)		// .hlslのファイル名
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "CShaderModel::Create()のpDeveceのNULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// シェーダプログラムの読み込みとコンパイル
	LPD3DXBUFFER	err = 0;
	D3DXCreateEffectFromFile(pDevice, TEXT(hlslFile), 0, 0, D3DXSHADER_DEBUG, 0, &m_pFX, &err);
	if (err) {
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "シェーダ読み込みエラー", MB_OK);
		return;
	}
}
