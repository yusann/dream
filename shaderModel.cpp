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
	CreateFX("shader/model.fx");

	// シェーダプログラムへテクニックへのハンドルの取得
	m_hTech = m_pFX->GetTechniqueByName("BasicTech");

	// シェーダープログラムのグローバル変数のハンドルの取得
	m_hMtxWVP = m_pFX->GetParameterByName(0, "g_mtxWVP");
	m_hTexture = m_pFX->GetParameterByName(0, "g_texture");
}

//=======================================================================================
//   メンバー変数クリア
//=======================================================================================
void CShaderModel::Delete()
{
	SAFE_RELEASE(m_pFX);
}

//=======================================================================================
//   モデル用シェーダの開始
//=======================================================================================
void CShaderModel::Begin(const int pass)
{
	// テクニックの設定（シェーダプログラムの設定）
	m_pFX->SetTechnique(m_hTech);
	m_pFX->CommitChanges();

	// シェーダプログラムの開始宣言
	m_pFX->Begin(0, 0);
	m_pFX->BeginPass(pass);
}

//=======================================================================================
//   モデル用シェーダの終了
//=======================================================================================
void CShaderModel::End(void)
{
	// シェーダプログラムの終了宣言
	m_pFX->EndPass();
	m_pFX->End();
}

//=======================================================================================
//   頂点シェーダの情報を代入
//=======================================================================================
void CShaderModel::SetVertexInfo( const D3DXMATRIX mtxW )			// ワールド座標
{
	// カメラ情報取得
	CCamera* pCamera = CManager::GetCamera();
	// ビュー行列
	D3DXMATRIX view = pCamera->GetMtxView();
	// プロジェクション行列
	D3DXMATRIX proj = pCamera->GetMtxProj();
	// ワールド・ビュー・プロジェクション行列
	D3DXMATRIX mtxWVP = mtxW * view * proj;

	// 情報代入
	m_pFX->SetMatrix(m_hMtxWVP, &mtxWVP);
}

//=======================================================================================
//   ピクセルシェーダの情報を代入
//=======================================================================================
void CShaderModel::SetPixelInfo(const LPDIRECT3DTEXTURE9 texture	// テクスチャ
)
{
	m_pFX->SetTexture(m_hTexture, texture);
}