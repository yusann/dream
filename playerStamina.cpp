//=============================================================================
// 2Dオブジェクト
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "playerStamina.h"
#include "texture.h"

CPlayerStamina::CPlayerStamina():CScene2D(CScene::OBJTYPE_UI),
m_pBG(NULL),
m_Value(1.0f),
m_isDraw(true)
{}

CPlayerStamina::~CPlayerStamina()
{
}

//=======================================================================================
// 作成処理
//=======================================================================================
CPlayerStamina *CPlayerStamina::Create(	const LPDIRECT3DTEXTURE9 pTexture,
									const D3DXVECTOR2 Pos,
									const D3DXVECTOR2 Scl)
{
	CPlayerStamina *pScene2D;                            // 変数宣言
	pScene2D = new CPlayerStamina;                       // 動的確保
	pScene2D->Init(pTexture,Pos, Scl);			// 初期化
	return pScene2D;                             // 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CPlayerStamina::Init(	const LPDIRECT3DTEXTURE9 pTexture,
						const D3DXVECTOR2 Pos,
						const D3DXVECTOR2 Scl)
{
	// メンバ変数の初期化
	m_Pos = D3DXVECTOR3(Pos.x, Pos.y,0.0f);
	m_Scl = D3DXVECTOR3(Scl.x, Scl.y, 0.0f);
	m_pTexture = pTexture;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 親の初期化
	CScene2D::Init();

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_NONE);

	m_pBG = CScene2D::Create(	CTexture::GetTexture(CTexture::TEXTYPE_UI_GAGEBG),
								Pos,
								Scl,
								CScene::OBJTYPE_UI);
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CPlayerStamina::Uninit()
{
	CScene2D::Uninit();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayerStamina::Update()
{
	if (m_Value >= 1.0f)
	{
		m_isDraw = false;
		m_pBG->SetisDraw(m_isDraw);
		return;
	}
	m_isDraw = true;
	m_pBG->SetisDraw(m_isDraw);
	if (m_Value <= 0.3f)
	{
		m_Color = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
	}
	else
	{
		m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	SetVexGage(m_Value);
	SetVexColor(m_Color);
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CPlayerStamina::Draw()
{
	if (!m_isDraw)
		return;
	CScene2D::Draw();
}
