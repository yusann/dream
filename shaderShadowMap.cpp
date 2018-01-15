//=============================================================================
// モデル用シェーダ処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "shaderBase.h"
#include "shaderShadowMap.h"
#include "light.h"
#include "camera.h"
#include "texture.h"

//*************
// メイン処理
//*************
CShaderShadowMap::CShaderShadowMap( ){
	Delete();
}

CShaderShadowMap::~CShaderShadowMap(){
	Delete();
}

//=======================================================================================
//   生成
//=======================================================================================
void CShaderShadowMap::Create()
{
	// 変数初期化
	Delete();

	// シェーダーの生成
	CreateFX("shader/shadowMap.fx");

	// シェーダプログラムへテクニックへのハンドルの取得
	m_hTech = m_pFX->GetTechniqueByName("BasicTech");

	// シェーダープログラムのグローバル変数のハンドルの取得
	m_hMtxLightWVP = m_pFX->GetParameterByName(0, "g_mtxLightWVP");
	m_hMtxLightWV = m_pFX->GetParameterByName(0, "g_mtxLightWV");
	m_hFar = m_pFX->GetParameterByName(0, "g_far");
}

//=======================================================================================
//   メンバー変数クリア
//=======================================================================================
void CShaderShadowMap::Delete()
{
	SAFE_RELEASE(m_pFX);
}

//=======================================================================================
//   モデル用シェーダの開始
//=======================================================================================
void CShaderShadowMap::Begin(const int pass)
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
void CShaderShadowMap::End(void)
{
	// シェーダプログラムの終了宣言
	m_pFX->EndPass();
	m_pFX->End();
}

//=======================================================================================
//   頂点シェーダの情報を代入
//=======================================================================================
void CShaderShadowMap::SetVertexInfo( const D3DXMATRIX mtxW, const float contourScl )			// ワールド座標
{
	// カメラ情報取得
	CCamera* pCamera = CManager::GetCamera();
	// ビュー行列
	D3DXMATRIX view = pCamera->GetMtxView();
	// プロジェクション行列
	D3DXMATRIX proj = pCamera->GetMtxProj();
	// ワールド・ビュー・プロジェクション行列
	D3DXMATRIX mtxWVP = mtxW * view * proj;
	// 逆転置行列
	D3DXMATRIX mtxWIT;
	D3DXMatrixInverse(&mtxWIT, NULL, &mtxW);
	D3DXMatrixTranspose(&mtxWIT, &mtxWIT);

	// 情報代入
	m_pFX->SetMatrix(m_hMtxLightWVP, &mtxWVP);
	m_pFX->SetMatrix(m_hMtxLightWV, &mtxWIT);
	m_pFX->SetFloat(m_hFar, contourScl);
}
