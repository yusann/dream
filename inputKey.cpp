//=============================================================================
// キー判定マネージャー処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "input.h"
#include "xbox360.h"
#include "sound.h"
#include "inputKey.h"

//*****************************************************************************
//   静的メンバー変数宣言
//*****************************************************************************
CInputKeyboard *CInputKey::m_pInputKeyboard = NULL;			// キーボード入力
CInputXbox *CInputKey::m_pInputXbox = NULL;					// マウス入力
CInputMouse *CInputKey::m_pInputMouse = NULL;				// マウス入力
CSound *CInputKey::m_pSound = NULL;							// サウンド

//==================================================================================================================================================
// 初期化処理
//==================================================================================================================================================
void CInputKey::Init(HINSTANCE hInstance, HWND hWnd)
{
	// キーボードの生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init( hInstance, hWnd );

	// マウスの生成
	m_pInputMouse = new CInputMouse;
	m_pInputMouse->Init(hInstance, hWnd);

	// Xboxコントローラーの生成
	m_pInputXbox = new CInputXbox;
	m_pInputXbox->Init();

	// サウンドの生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);
}

//==================================================================================================================================================
// 終了処理
//==================================================================================================================================================
void CInputKey::Uninit(void)
{
	// サウンドの破棄
	SAFE_UNINIT(m_pSound);

	// Xboxコントローラー入力の破棄
	SAFE_UNINIT(m_pInputXbox);

	// マウス入力の破棄
	SAFE_UNINIT(m_pInputMouse);

	// キーボード入力の破棄
	SAFE_UNINIT(m_pInputKeyboard);
}

//==================================================================================================================================================
// 更新処理
//==================================================================================================================================================
void CInputKey::Update(void)
{
	m_pInputKeyboard->Update();			// キーボード入力
	m_pInputMouse->Update();			// マウス入力
	m_pInputXbox->Update();				// Xboxコントローラー入力
}

D3DXVECTOR2 CInputKey::GetAnalogLValue(void)
{
	return m_pInputXbox->GetAnalogValue(CInputXbox::CONTROLLER_1, CInputXbox::LEFT);
}
D3DXVECTOR2 CInputKey::GetAnalogRValue(void)
{ 
	return m_pInputXbox->GetAnalogValue(CInputXbox::CONTROLLER_1, CInputXbox::RIGHT);
}
//=======================================================================================
//  ゲーム全般キー押し判定
//=======================================================================================
// スタート
BOOL CInputKey::InputGameStart(void)
{
	if (m_pInputKeyboard->GetKeyTrigger(DIK_SPACE) ||
		m_pInputXbox->GetXboxTrigger(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_START)) {
		m_pSound->Play(CSound::SE_ENTER000);
		return TRUE;
	}
	return FALSE;
}
// ポーズモード
BOOL CInputKey::InputPause(void)
{
	if (m_pInputKeyboard->GetKeyTrigger(DIK_P) ||
		m_pInputXbox->GetXboxTrigger(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_START)) {
		m_pSound->Play(CSound::SE_ENTER000);
		return TRUE;
	}
	return FALSE;
}

//=======================================================================================
//  プレイヤーキー押し判定
//=======================================================================================
BOOL CInputKey::InputPlayerMove(void)
{
	D3DXVECTOR2 work = m_pInputXbox->GetAnalogValue(CInputXbox::CONTROLLER_1, CInputXbox::LEFT);
	if (InputPlayerMoveU() ||
		InputPlayerMoveD() ||
		InputPlayerMoveL() ||
		InputPlayerMoveR() ||
		abs(work.x) + abs(work.y) > 0.5f)
	{
		return TRUE;
	}
	return FALSE;
}
// スティック操作の移動処理
BOOL CInputKey::InputPlayerMoveStick(void)
{
	D3DXVECTOR2 work = m_pInputXbox->GetAnalogValue(CInputXbox::CONTROLLER_1, CInputXbox::LEFT);
	if (abs(work.x) + abs(work.y) > 0.5f)
	{
		return TRUE;
	}
	return FALSE;
}
// 前進
BOOL CInputKey::InputPlayerMoveU(void)
{
	if (m_pInputKeyboard->GetKeyPress(DIK_W)) {
		return TRUE;
	}
	return FALSE;
}

// 後退
BOOL CInputKey::InputPlayerMoveD(void)
{
	if (m_pInputKeyboard->GetKeyPress(DIK_S)) {
		return TRUE;
	}
	return FALSE;
}

// 左移動
BOOL CInputKey::InputPlayerMoveL(void)
{
	if (m_pInputKeyboard->GetKeyPress(DIK_A)) {
		return TRUE;
	}
	return FALSE;
}

// 右移動
BOOL CInputKey::InputPlayerMoveR(void)
{
	if (m_pInputKeyboard->GetKeyPress(DIK_D)) {
		return TRUE;
	}
	return FALSE;
}

// ジャンプ
BOOL CInputKey::InputPlayerJump(void)
{
	if (m_pInputKeyboard->GetKeyTrigger(DIK_SPACE)||
		m_pInputXbox->GetXboxTrigger(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_A)) {
		return TRUE;
	}
	return FALSE;
}

// 弱攻撃
BOOL CInputKey::InputPlayerAttack(void)
{
	if (m_pInputKeyboard->GetKeyTrigger(DIK_B) ||
		m_pInputXbox->GetXboxTrigger(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_B)) {
		return TRUE;
	}
	return FALSE;
}

// ダッシュ
BOOL CInputKey::InputPlayerDash(void)
{
	if (m_pInputKeyboard->GetKeyPress(DIK_Q) || m_pInputKeyboard->GetKeyPress(DIK_E) ||
		m_pInputXbox->GetXboxPress(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_X)) {
		return TRUE;
	}
	return FALSE;
}