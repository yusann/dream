//=============================================================================
// 2Dオブジェクト
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "mode.h"
#include "modeGame.h"
#include "scene.h"
#include "scene2D.h"
#include "debugShadowMap.h"
#include "light.h"
#include "texture.h"

CDebugShadowMap::CDebugShadowMap():CScene2D(CScene::OBJTYPE_UI)
{
}

CDebugShadowMap::~CDebugShadowMap()
{
}

//=======================================================================================
// 作成処理
//=======================================================================================
CDebugShadowMap *CDebugShadowMap::Create(){
	CDebugShadowMap *pScene2D;                            // 変数宣言
	pScene2D = new CDebugShadowMap;                       // 動的確保
	pScene2D->Init();                            // 初期化
	return pScene2D;                             // 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CDebugShadowMap::Init()
{
	// メンバ変数の初期化
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(SCREEN_WIDTH*0.2f, SCREEN_HEIGHT*0.2f, 0.0f);
	m_pTexture = CManager::GetLight()->GetTexture();

	// 親の初期化
	CScene2D::Init();

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_NONE);
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CDebugShadowMap::Uninit()
{
	CScene2D::Uninit();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CDebugShadowMap::Update()
{
	m_pTexture = CManager::GetLight()->GetTexture();
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CDebugShadowMap::Draw()
{
	CScene2D::Draw();
}