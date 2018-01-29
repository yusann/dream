//=============================================================================
// 2Dオブジェクト
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "mode.h"
#include "modeGame.h"
#include "scene.h"
#include "scene2D.h"
#include "sceneModelX.h"
#include "sceneMotionPartsX.h"
#include "object2D.h"
#include "player.h"
#include "texture.h"

CObject2D::CObject2D():CScene2D(CScene::OBJTYPE_UI)
{
}

CObject2D::~CObject2D()
{
}

//=======================================================================================
// 作成処理
//=======================================================================================
CObject2D *CObject2D::Create(TYPE Type)
{
	CObject2D *pScene2D;                            // 変数宣言
	pScene2D = new CObject2D;                       // 動的確保
	pScene2D->Init(Type);                            // 初期化
	return pScene2D;                             // 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CObject2D::Init(TYPE Type)
{
	// メンバ変数の初期化
	m_Type = Type;
	switch (Type)
	{
	case TYPE_BG_TITLE:
		m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_Scl = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		m_pTexture = CTexture::GetTexture( CTexture::TEXTYPE_TITLELOGO);
		break;
	case TYPE_BG_TITLE_SIBA:
		m_Pos = D3DXVECTOR3(-200.0f, SCREEN_HEIGHT -300.0f, 0.0f);
		m_Scl = D3DXVECTOR3(500.0f, 500.0f, 0.0f);
		m_TexScl = D3DXVECTOR2(0.5f, 1.0f);
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_TITLEBG);
		break;
	case TYPE_BG_TUTORIAL:
		m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Scl = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_TUTORIALBG);
		break;
	case TYPE_BG_RESULTWIN:
		m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Scl = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_RESULTWINBG);
		break;
	case TYPE_BG_RESULTLOSE:
		m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Scl = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_RESULTLOSTBG);
		break;
	case TYPE_UI_PUSH:
		m_Pos = D3DXVECTOR3(400.0f, 500.0f, 0.0f);
		m_Scl = D3DXVECTOR3(400.0f, 150.0f, 0.0f);
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_PUSHSTART);
		break;
	case TYPE_UI_LIFE:
		m_Pos = D3DXVECTOR3(SCREEN_WIDTH*0.06f, SCREEN_HEIGHT*0.95f, 0.0f);
		m_Scl = D3DXVECTOR3(SCREEN_WIDTH*0.18f, SCREEN_HEIGHT*0.015f, 0.0f);
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_UI_LIFE);
		break;
	case TYPE_UI_MAGIC:
		m_Pos = D3DXVECTOR3(SCREEN_WIDTH*0.06f, SCREEN_HEIGHT*0.97f, 0.0f);
		m_Scl = D3DXVECTOR3(SCREEN_WIDTH*0.09f, SCREEN_HEIGHT*0.0075f, 0.0f);
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_UI_MAGIC);
		break;
	case TYPE_UI_LIFEBG:
		m_Pos = D3DXVECTOR3(SCREEN_WIDTH*0.06f, SCREEN_HEIGHT*0.95f, 0.0f);
		m_Scl = D3DXVECTOR3(SCREEN_WIDTH*0.18f, SCREEN_HEIGHT*0.015f, 0.0f);
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_UI_GAGEBG);
		m_Color.a = 0.7f;
		break;
	case TYPE_UI_NUM:
		m_Pos = D3DXVECTOR3(SCREEN_WIDTH*0.03f, SCREEN_HEIGHT*0.97f, 0.0f);
		m_Scl = D3DXVECTOR3(SCREEN_WIDTH*0.01f, SCREEN_HEIGHT*0.01f, 0.0f);
		m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_UI_NUM);
		break;
	default:
		break;
	}
	m_SclOld = m_Scl;

	// 親の初期化
	CScene2D::Init();

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_NONE);
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CObject2D::Uninit()
{
	CScene2D::Uninit();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CObject2D::Update()
{
	switch (m_Type)
	{
	case TYPE_UI_PUSH:
	{
		static bool color = false;
		if (m_Color.a >= 1.0f)
		{
			color = true;
		}
		if (m_Color.a <= 0.0f)	
		{
			color = false;
		}
		if (color)
		{
			m_Color.a -= 0.02f;
		}
		else
		{
			m_Color.a += 0.04f;
		}
		SetVexColor();
	}
		break;
	case TYPE_BG_TITLE_SIBA:
	{
		static int sibaTime = 0;
		sibaTime = sibaTime % 100 + 1;
		if ((sibaTime > 80 && sibaTime < 85) ||
			(sibaTime > 95 && sibaTime < 100))
		{
			m_TexPos = D3DXVECTOR2(0.5f, 0.0f);
		}
		else
		{
			m_TexPos = D3DXVECTOR2(0.0f, 0.0f);
		}
		SetVexUV();
		break;
	}
	case TYPE_UI_MAGIC:
		break;
	default:
		break;
	}
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CObject2D::Draw()
{
	CScene2D::Draw();
}