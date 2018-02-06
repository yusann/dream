//=============================================================================
// �V�F�[�_�}�l�[�W���[����
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
	// �c�@�A�C�R��
	D3DXVECTOR2 pos = screen_top_right;
	D3DXVECTOR2 scl = D3DXVECTOR2(70.0f, 100.0f);
	pos.x -= scl.x+20.0f;
	m_pLife = CPlayerLife::Create(	CTexture::GetTexture(CTexture::TEXTYPE_UI_NUM),
									pos,
									scl,
									LifeMax);

	// �X�^�~�i�Q�[�W
	pos = screen_center;
	scl = D3DXVECTOR2(100.0f, 30.0f);
	pos -= scl*0.5f;
	m_pStamina = CPlayerStamina::Create(	CTexture::GetTexture(CTexture::TEXTYPE_UI_STAMINA),
											pos,
											scl);
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
	m_pLife->ChangeNum(Life);
}

//=======================================================================================
//   �X�^�~�i�o�[�̍X�V
//=======================================================================================
void CPlayerUIManager::SetStamina(float Stamina)
{
	m_pStamina->SetValue(Stamina);
}
