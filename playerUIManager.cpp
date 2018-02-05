//=============================================================================
// �V�F�[�_�}�l�[�W���[����
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
	CPlayerUIManager *pUI;                            // �ϐ��錾
	pUI = new CPlayerUIManager;                       // ���I�m��
	pUI->Init(LifeMax);                            // ������
	return pUI;                             // �l��Ԃ�
}

//==================================================================================================================================================
// ����������
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
// �I������
//==================================================================================================================================================
void CPlayerUIManager::Uninit()
{
	SAFE_UNINIT(m_pLife);
	SAFE_UNINIT(m_pStamina);
}

//=======================================================================================
//   �̗̓e�N�X�`���̕ύX
//=======================================================================================
void CPlayerUIManager::SetLife(int Life)
{
	m_pLife->SetTexID(Life);
}

//=======================================================================================
//   �X�^�~�i�o�[�̍X�V
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