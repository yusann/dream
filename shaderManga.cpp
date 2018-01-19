//=============================================================================
// モデル用シェーダ処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "shaderBase.h"
#include "shaderManga.h"
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "GBuffer.h"

//*************
// メイン処理
//*************
CShaderManga::CShaderManga( ){
	Delete();
}

CShaderManga::~CShaderManga(){
	Delete();
}

//=======================================================================================
//   生成
//=======================================================================================
void CShaderManga::Create()
{
	// 変数初期化
	Delete();

	// シェーダーの生成
	CreateFX("shader/manga.fx");

	// シェーダプログラムへテクニックへのハンドルの取得
	m_hTech = m_pFX->GetTechniqueByName("BasicTech");

	// シェーダープログラムのグローバル変数のハンドルの取得
	m_hMtxWVP = m_pFX->GetParameterByName(0, "g_mtxWVP");
	m_hMtxWIT = m_pFX->GetParameterByName(0, "g_mtxWIT");
	m_hMtxWI = m_pFX->GetParameterByName(0, "g_mtxWI");
	m_hMtxW = m_pFX->GetParameterByName(0, "g_mtxW");

	m_hMtxLightWVP = m_pFX->GetParameterByName(0, "g_mtxLightWVP");
	m_hMtxLightWV = m_pFX->GetParameterByName(0, "g_mtxLightWV");
	m_hLightFar = m_pFX->GetParameterByName(0, "g_lightFar");
	m_hDepthTex = m_pFX->GetParameterByName(0, "g_depthTex");
	m_hDepthEpsilon = m_pFX->GetParameterByName(0, "g_depthEpsilon");

	m_hLightDirW = m_pFX->GetParameterByName(0, "g_lightDirW");
	m_hPosEyeW = m_pFX->GetParameterByName(0, "g_posEyeW");
	m_hDiffColor = m_pFX->GetParameterByName(0, "g_diffColor");

	m_hContourScl = m_pFX->GetParameterByName(0, "g_contourScl");

	m_hTexture = m_pFX->GetParameterByName(0, "g_texture");
	m_hAnimeDrawTex = m_pFX->GetParameterByName(0, "g_animeDrawTex");
}

//=======================================================================================
//   メンバー変数クリア
//=======================================================================================
void CShaderManga::Delete()
{
	SAFE_RELEASE(m_pFX);
}

//=======================================================================================
//   モデル用シェーダの開始
//=======================================================================================
void CShaderManga::Begin(const int pass)
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
void CShaderManga::End(void)
{
	// シェーダプログラムの終了宣言
	m_pFX->EndPass();
	m_pFX->End();
}

//=======================================================================================
//   頂点シェーダの情報を代入
//=======================================================================================
void CShaderManga::SetVertexInfo( const D3DXMATRIX mtxW, const float contourScl )			// ワールド座標
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
	D3DXMATRIX mtxWIT,mtxWI;
	D3DXMatrixInverse(&mtxWI, NULL, &mtxW);
	D3DXMatrixTranspose(&mtxWIT, &mtxWI);

	// ライト情報取得
	CLight* pLight = CManager::GetLight();
	// ライトビュー行列
	D3DXMATRIX lightView = pLight->GetMtxView();
	// ライトプロジェクション行列
	D3DXMATRIX lightProj = pLight->GetMtxProj();
	// ライトワールド・ビュー・プロジェクション行列
	D3DXMATRIX mtxLightWVP = mtxW * lightView * lightProj;
	// ライトワールド・ビュー・プロジェクション行列
	D3DXMATRIX mtxLightWV = mtxW * lightView;
	// ライト範囲の取得
	float lightFar = pLight->GetFar();
	float depthEpsilon = pLight->GetDepthEpsilon() * pLight->GetDepthEpsilonScl();

	// 情報代入
	m_pFX->SetMatrix(m_hMtxWVP, &mtxWVP);
	m_pFX->SetMatrix(m_hMtxWIT, &mtxWIT);
	m_pFX->SetMatrix(m_hMtxWI, &mtxWI);
	m_pFX->SetMatrix(m_hMtxW, &mtxW);
	m_pFX->SetFloat(m_hContourScl, contourScl);

	m_pFX->SetMatrix(m_hMtxLightWVP, &mtxLightWVP);
	m_pFX->SetMatrix(m_hMtxLightWV, &mtxLightWV);
	m_pFX->SetFloat(m_hLightFar, lightFar);
	m_pFX->SetFloat(m_hDepthEpsilon, depthEpsilon);
	D3DXVECTOR3 lightDirW = pLight->GetDir();
	D3DXVec3Normalize(&lightDirW, &lightDirW);
	m_pFX->SetValue(m_hLightDirW, &lightDirW, sizeof(lightDirW));
}

//=======================================================================================
//   ピクセルシェーダの情報を代入
//=======================================================================================
void CShaderManga::SetPixelInfo(const D3DCOLORVALUE diffColor,		// ディフューズカラー
								const LPDIRECT3DTEXTURE9 texture	// テクスチャ
)
{
	// ライト情報取得
	CLight *pLight = CManager::GetLight();
	// ライトベクトル（ワールド）
	D3DXVECTOR3 lightDirW = pLight->GetDir();
	D3DXVec3Normalize(&lightDirW, &lightDirW);
	// 深度テクスチャ
	//LPDIRECT3DTEXTURE9 depthTex = pLight->GetTexture();
	LPDIRECT3DTEXTURE9 depthTex = CManager::GetGBuffer()->GetTextureColor();

	// カメラ情報取得
	CCamera *pCamera = CManager::GetCamera();
	// カメラ座標（ワールド）
	D3DXVECTOR3 posEyeW = pCamera->GetPosEye();

	// 情報代入
	m_pFX->SetValue(m_hLightDirW, &lightDirW, sizeof(lightDirW));
	m_pFX->SetValue(m_hPosEyeW, &posEyeW, sizeof(posEyeW));
	m_pFX->SetValue(m_hDiffColor, &diffColor, sizeof(diffColor));
	m_pFX->SetTexture(m_hTexture, texture);
	m_pFX->SetTexture(m_hAnimeDrawTex, CTexture::GetTexture(CTexture::TEXTYPE_ANIME_DRAW));
	m_pFX->SetTexture(m_hDepthTex, depthTex);
}