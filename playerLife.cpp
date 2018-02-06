//=============================================================================
// 2Dオブジェクト
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "playerLife.h"
#include "texture.h"

CPlayerLife::CPlayerLife():CScene2D(CScene::OBJTYPE_UI)
{
}

CPlayerLife::~CPlayerLife()
{
}

//=======================================================================================
// 作成処理
//=======================================================================================
CPlayerLife *CPlayerLife::Create(	const LPDIRECT3DTEXTURE9 pTexture,
									const D3DXVECTOR2 Pos,
									const D3DXVECTOR2 Scl,
									const int Num)
{
	CPlayerLife *pScene2D;                            // 変数宣言
	pScene2D = new CPlayerLife;                       // 動的確保
	pScene2D->Init(pTexture,Pos, Scl, Num);			// 初期化
	return pScene2D;                             // 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CPlayerLife::Init(	const LPDIRECT3DTEXTURE9 pTexture,
						const D3DXVECTOR2 Pos,
						const D3DXVECTOR2 Scl,
						const int Num)
{
	// メンバ変数の初期化
	m_Pos = D3DXVECTOR3(Pos.x, Pos.y,0.0f);
	m_Scl = D3DXVECTOR3(Scl.x, Scl.y, 0.0f);
	m_pTexture = pTexture;
	m_TexWidth = 5;
	m_TexHeight = 2;
	m_Type = TYPE_NONE;
	m_Num = Num;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 親の初期化
	CScene2D::Init();
	SetTexID(m_Num);

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_NONE);

	D3DXVECTOR2 scl = D3DXVECTOR2(200.0f,100.0f);
	D3DXVECTOR2 pos = D3DXVECTOR2(Pos.x-scl.x, Pos.y);
	m_pLifeIcon = CScene2D::Create(CTexture::GetTexture(CTexture::TEXTYPE_UI_LIFE_ICON),
		pos,
		scl,
		CScene::OBJTYPE_UI);
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CPlayerLife::Uninit()
{
	CScene2D::Uninit();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayerLife::Update()
{
	if (m_Type == TYPE_NONE)
		return;
	static int frame = 0;
	frame++;
	if (m_Type == TYPE_OUT)
	{
		m_Pos.y -= 1.0f;
		m_Color.a -= 1.0f / 10.0f;
		if (frame > 10)
		{
			m_Type = TYPE_IN;
			frame = 0;
			m_Color.a = 0.0f;
			m_Pos.y = m_PosOld.y + 10.0f;
			SetTexID(m_Num);
		}
	}
	if (m_Type == TYPE_IN)
	{
		m_Pos.y -= 1.0f;
		m_Color.a += 1.0f / 10.0f;
		if (frame > 10)
		{
			m_Type = TYPE_NONE;
			frame = 0;
			m_Color.a = 1.0f;
			m_Pos.y = m_PosOld.y;
		}
	}
	SetVexColor(m_Color);
	SetVexPos();
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CPlayerLife::Draw()
{
	CScene2D::Draw();
}


void CPlayerLife::ChangeNum(int NextNum)
{
	if (m_Num == NextNum)
		return;
	m_Type = TYPE_OUT;
	m_Num = NextNum;
	m_PosOld = m_Pos;
}