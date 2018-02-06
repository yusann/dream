//=============================================================================
// 2D�I�u�W�F�N�g
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
// �쐬����
//=======================================================================================
CPlayerLife *CPlayerLife::Create(	const LPDIRECT3DTEXTURE9 pTexture,
									const D3DXVECTOR2 Pos,
									const D3DXVECTOR2 Scl,
									const int Num)
{
	CPlayerLife *pScene2D;                            // �ϐ��錾
	pScene2D = new CPlayerLife;                       // ���I�m��
	pScene2D->Init(pTexture,Pos, Scl, Num);			// ������
	return pScene2D;                             // �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CPlayerLife::Init(	const LPDIRECT3DTEXTURE9 pTexture,
						const D3DXVECTOR2 Pos,
						const D3DXVECTOR2 Scl,
						const int Num)
{
	// �����o�ϐ��̏�����
	m_Pos = D3DXVECTOR3(Pos.x, Pos.y,0.0f);
	m_Scl = D3DXVECTOR3(Scl.x, Scl.y, 0.0f);
	m_pTexture = pTexture;
	m_TexWidth = 5;
	m_TexHeight = 2;
	m_Type = TYPE_NONE;
	m_Num = Num;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�̏�����
	CScene2D::Init();
	SetTexID(m_Num);

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_NONE);

	D3DXVECTOR2 scl = D3DXVECTOR2(200.0f,100.0f);
	D3DXVECTOR2 pos = D3DXVECTOR2(Pos.x-scl.x, Pos.y);
	m_pLifeIcon = CScene2D::Create(CTexture::GetTexture(CTexture::TEXTYPE_UI_LIFE_ICON),
		pos,
		scl,
		CScene::OBJTYPE_UI);
}

//=======================================================================================
//   �I������
//=======================================================================================
void CPlayerLife::Uninit()
{
	CScene2D::Uninit();
}

//=======================================================================================
//   �X�V����
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
//   �`�揈��
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