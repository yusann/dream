//=============================================================================
// ���[�h
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "mode.h"
#include "modeResult.h"
#include "modeTitle.h"
#include "manager.h"
#include "input.h"
#include "inputKey.h"
#include "sound.h"

#include "scene.h"
#include "scene2D.h"
#include "fade.h"
#include "object2D.h"

//*****************************************************************************
//   �ÓI�����o�ϐ��錾
//*****************************************************************************
bool CModeResult::m_Clear = false;

//==================================================================================
//   ����������
//==================================================================================
void CModeResult::Init(void)
{
	if (m_Clear)
	{
		CObject2D::Create(CObject2D::TYPE_BG_RESULTWIN);
		CManager::GetSound()->Play(CSound::BGM_WIN000);
	}
	else
	{
		CObject2D::Create(CObject2D::TYPE_BG_RESULTLOSE);
		CManager::GetSound()->Play(CSound::BGM_LOSE000);
	}
}

//==================================================================================
//   �I������
//==================================================================================
void CModeResult::Uninit(void)
{
	CManager::GetSound()->Stop();

	// �I�u�W�F�N�g�̔j��
	CScene::ReleaseAll(CScene::OBJTYPE_FADE);
}

//==================================================================================
//   �X�V����
//==================================================================================
void CModeResult::Update(void)
{
	if (CInputKey::InputGameStart())
	{
		CFade::SetFade(new CModeTitle);
	}
}
