//=============================================================================
// 2D�I�u�W�F�N�g
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
// �쐬����
//=======================================================================================
CPlayerStamina *CPlayerStamina::Create(	const LPDIRECT3DTEXTURE9 pTexture,
									const D3DXVECTOR2 Pos,
									const D3DXVECTOR2 Scl)
{
	CPlayerStamina *pScene2D;                            // �ϐ��錾
	pScene2D = new CPlayerStamina;                       // ���I�m��
	pScene2D->Init(pTexture,Pos, Scl);			// ������
	return pScene2D;                             // �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CPlayerStamina::Init(	const LPDIRECT3DTEXTURE9 pTexture,
						const D3DXVECTOR2 Pos,
						const D3DXVECTOR2 Scl)
{
	// �����o�ϐ��̏�����
	m_Pos = D3DXVECTOR3(Pos.x, Pos.y,0.0f);
	m_Scl = D3DXVECTOR3(Scl.x, Scl.y, 0.0f);
	m_pTexture = pTexture;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�̏�����
	CScene2D::Init();

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_NONE);

	m_pBG = CScene2D::Create(	CTexture::GetTexture(CTexture::TEXTYPE_UI_GAGEBG),
								Pos,
								Scl,
								CScene::OBJTYPE_UI);
}

//=======================================================================================
//   �I������
//=======================================================================================
void CPlayerStamina::Uninit()
{
	CScene2D::Uninit();
}

//=======================================================================================
//   �X�V����
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
//   �`�揈��
//=======================================================================================
void CPlayerStamina::Draw()
{
	if (!m_isDraw)
		return;
	CScene2D::Draw();
}
