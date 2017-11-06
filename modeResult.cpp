//=============================================================================
// モード
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
//   静的メンバ変数宣言
//*****************************************************************************
bool CModeResult::m_Clear = false;

//==================================================================================
//   初期化処理
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
//   終了処理
//==================================================================================
void CModeResult::Uninit(void)
{
	CManager::GetSound()->Stop();

	// オブジェクトの破棄
	CScene::ReleaseAll(CScene::OBJTYPE_FADE);
}

//==================================================================================
//   更新処理
//==================================================================================
void CModeResult::Update(void)
{
	if (CInputKey::InputGameStart())
	{
		CFade::SetFade(new CModeTitle);
	}
}
