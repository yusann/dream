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
	m_hMtxW = m_pFX->GetParameterByName(0, "g_mtxW");

	m_hLightDirW = m_pFX->GetParameterByName(0, "g_lightDirW");
	m_hPosEyeW = m_pFX->GetParameterByName(0, "g_posEyeW");
	m_hDiffColor = m_pFX->GetParameterByName(0, "g_diffColor");
	m_hSpecularPower = m_pFX->GetParameterByName(0, "g_specularPower");

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
//   モデル用シェーダのクリア
//=======================================================================================
void CShaderModel::SetTech(void)
{
	// テクニックの設定（シェーダプログラムの設定）
	m_pFX->SetTechnique(m_hTech);
}
//=======================================================================================
//   モデル用シェーダのセット
//=======================================================================================
void CShaderModel::Begin(const int pass)
{
	m_pFX->CommitChanges();

	// シェーダプログラムの開始宣言
	m_pFX->Begin(0, 0);
	m_pFX->BeginPass(pass);
}

//=======================================================================================
//   モデル用シェーダのクリア
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
	m_pFX->SetMatrix(m_hMtxW, &mtxW);
}

//=======================================================================================
//   ピクセルシェーダの情報を代入
//=======================================================================================
void CShaderModel::SetPixelInfo(const D3DCOLORVALUE diffColor,	// ディフューズカラー
								const LPDIRECT3DTEXTURE9 texture,
								const float specularPower		// スペキュラーパワー
)
{
	// ライト情報取得
	CLight *pLight = CManager::GetLight();
	// ライトベクトル（ワールド）
	D3DXVECTOR3 lightDirW = pLight->GetDir();
	D3DXVec3Normalize(&lightDirW, &lightDirW);

	// カメラ情報取得
	CCamera *pCamera = CManager::GetCamera();
	// カメラ座標（ワールド）
	D3DXVECTOR3 posEyeW = pCamera->GetPosEye();

	// 情報代入
	m_pFX->SetValue(m_hLightDirW, &lightDirW, sizeof(lightDirW));
	m_pFX->SetValue(m_hPosEyeW, &posEyeW, sizeof(posEyeW));
	m_pFX->SetValue(m_hDiffColor, &diffColor, sizeof(diffColor));
	m_pFX->SetFloat(m_hSpecularPower, specularPower);
	m_pFX->SetTexture(m_hTexture, texture);
}