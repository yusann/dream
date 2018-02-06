//=============================================================================
// シェーダマネージャー処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerUIManager.h"

#include "scene.h"
#include "scene2D.h"
#include "playerLife.h"
#include "playerStamina.h"

#include "texture.h"

const D3DXVECTOR2 screen_center(SCREEN_WIDTH*0.5f, SCREEN_HEIGHT*0.5f);
const D3DXVECTOR2 screen_top_right(SCREEN_WIDTH, 0.0f);

CPlayerUIManager *CPlayerUIManager::Create(int LifeMax)
{
	CPlayerUIManager *pUI;                            // 変数宣言
	pUI = new CPlayerUIManager;                       // 動的確保
	pUI->Init(LifeMax);                            // 初期化
	return pUI;                             // 値を返す
}

//==================================================================================================================================================
// 初期化処理
//==================================================================================================================================================
void CPlayerUIManager::Init(int LifeMax)
{
	// 残機アイコン
	D3DXVECTOR2 pos = screen_top_right;
	D3DXVECTOR2 scl = D3DXVECTOR2(70.0f, 100.0f);
	pos.x -= scl.x+20.0f;
	m_pLife = CPlayerLife::Create(	CTexture::GetTexture(CTexture::TEXTYPE_UI_NUM),
									pos,
									scl,
									LifeMax);

	// スタミナゲージ
	pos = screen_center;
	scl = D3DXVECTOR2(100.0f, 30.0f);
	pos -= scl*0.5f;
	m_pStamina = CPlayerStamina::Create(	CTexture::GetTexture(CTexture::TEXTYPE_UI_STAMINA),
											pos,
											scl);
}

//==================================================================================================================================================
// 終了処理
//==================================================================================================================================================
void CPlayerUIManager::Uninit()
{
	SAFE_UNINIT(m_pLife);
	SAFE_UNINIT(m_pStamina);
}

//=======================================================================================
//   体力テクスチャの変更
//=======================================================================================
void CPlayerUIManager::SetLife(int Life)
{
	m_pLife->ChangeNum(Life);
}

//=======================================================================================
//   スタミナバーの更新
//=======================================================================================
void CPlayerUIManager::SetStamina(float Stamina)
{
	m_pStamina->SetValue(Stamina);
}
