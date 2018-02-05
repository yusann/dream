//=============================================================================
// シェーダマネージャー処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerUIManager.h"

#include "scene.h"
#include "scene2D.h"

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
	D3DXVECTOR2 pos = screen_top_right;
	D3DXVECTOR2 scl = D3DXVECTOR2(100.0f, 100.0f);
	pos.x -= scl.x;
	m_pLife = CScene2D::Create(	CTexture::GetTexture(CTexture::TEXTYPE_UI_NUM),
								pos,
								scl,
								CScene::OBJTYPE_UI,
								5,2);
	m_pLife->SetTexID(LifeMax);

	pos = screen_center;
	scl = D3DXVECTOR2(100.0f, 30.0f);
	pos -= scl*0.5f;
	m_pGage = CScene2D::Create(	CTexture::GetTexture(CTexture::TEXTYPE_UI_GAGEBG),
								pos,
								scl,
								CScene::OBJTYPE_UI);

	m_pStamina = CScene2D::Create(	CTexture::GetTexture(CTexture::TEXTYPE_UI_STAMINA),
									pos,
									scl,
									CScene::OBJTYPE_UI);
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
	m_pLife->SetTexID(Life);
}

//=======================================================================================
//   スタミナバーの更新
//=======================================================================================
void CPlayerUIManager::SetStamina(float Stamina)
{
	m_pStamina->SetVexGage(Stamina);
	if (Stamina <= 0.3f)
	{
		m_pStamina->SetVexColor(D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f));
	}
	else
	{
		m_pStamina->SetVexColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void CPlayerUIManager::SetStaminaDraw(bool isDraw)
{
	m_pStamina->SetisDraw(isDraw);
	m_pGage->SetisDraw(isDraw);
}