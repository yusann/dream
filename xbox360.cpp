//*****************************************************************************
//																			   
//								light.cpp								
//												
//*****************************************************************************
//=============================================================================
// ヘッダファイル
//=============================================================================
#include "main.h"
#include "input.h"
#include "xbox360.h"
#define REPEAT_COUNT (20)
#define ANALOG_METER_MAX (32767.0f)
//=============================================================================
// CInputXboxコンストラスタ
//=============================================================================
CInputXbox::CInputXbox()
{
	// 各ワークのクリア
	ZeroMemory(m_aKeyState, sizeof m_aKeyState);
	ZeroMemory(m_aKeyStateTrigger, sizeof m_aKeyStateTrigger);
	ZeroMemory(m_aKeyStateRelease, sizeof m_aKeyStateRelease);
	ZeroMemory(m_aKeyStateRepeat, sizeof m_aKeyStateRepeat);
	ZeroMemory(m_aKeyStateRepeatCnt, sizeof m_aKeyStateRepeatCnt);
}

//=============================================================================
// CInputXboxデストラスタ
//=============================================================================
CInputXbox::~CInputXbox()
{
}

//=============================================================================
// XBOXコントローラーの初期化処理
//=============================================================================
HRESULT CInputXbox::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr = S_OK;

	return hr;
}

//=============================================================================
// XBOXコントローラー入力処理の開放
//=============================================================================
void CInputXbox::Uninit(void)
{
	// 入力処理の開放
	CInput::Uninit();
}

//=============================================================================
// XBOXコントローラーの更新処理
//=============================================================================
void CInputXbox::Update(void)
{
	XINPUT_STATE State;

	WORD counter;

	for( int nCount = 0; nCount < (int) CONTROLLER_MAX; nCount++)
	{

		counter = 1;

		ZeroMemory( &State, sizeof(State));
		XInputGetState( nCount, &State);

		m_Analog[nCount][LEFT] = D3DXVECTOR2(State.Gamepad.sThumbLX / ANALOG_METER_MAX, State.Gamepad.sThumbLY / ANALOG_METER_MAX);
		m_Analog[nCount][RIGHT] = D3DXVECTOR2(State.Gamepad.sThumbRX / ANALOG_METER_MAX, State.Gamepad.sThumbRY / ANALOG_METER_MAX);

		m_Trigger[nCount][LEFT] = State.Gamepad.bLeftTrigger;
		m_Trigger[nCount][RIGHT] = State.Gamepad.bRightTrigger;
	
		for(WORD nCntKey = 0; nCntKey < XBOX_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCount][nCntKey] = (m_aKeyState[nCount][nCntKey] ^ (State.Gamepad.wButtons & counter )) & (State.Gamepad.wButtons & counter);
			m_aKeyStateRelease[nCount][nCntKey] = (m_aKeyState[nCount][nCntKey] ^ (State.Gamepad.wButtons & counter )) & ~(State.Gamepad.wButtons & counter);
			m_aKeyStateRepeat[nCount][nCntKey] = m_aKeyStateTrigger[nCount][nCntKey];

			if((State.Gamepad.wButtons & counter))
			{
				m_aKeyStateRepeatCnt[nCount][nCntKey]++;
				if(m_aKeyStateRepeatCnt[nCount][nCntKey] >= REPEAT_COUNT)
				{
					m_aKeyStateRepeat[nCount][nCntKey] = (State.Gamepad.wButtons & counter);
				}
			}
			else
			{
				m_aKeyStateRepeatCnt[nCount][nCntKey] = 0;
				m_aKeyStateRepeat[nCount][nCntKey] = 0;
			}

		
			m_aKeyState[nCount][nCntKey] = (State.Gamepad.wButtons & counter);
			counter *= 2;
		}
	}
		
}

//=============================================================================
// XBOXコントローラーデータ取得(プレス)
//=============================================================================
bool CInputXbox::GetXboxPress(CONTROLLER_NUM Idx, WORD nKey)
{
	WORD Key = 0;

	while(nKey > 1)
	{
		nKey /= 2;
		Key++;
	}


	return (m_aKeyState[Idx][Key]) ? TRUE: FALSE;
}
//=============================================================================
// XBOXコントローラーデータ取得(トリガー)
//=============================================================================
bool CInputXbox::GetXboxTrigger(CONTROLLER_NUM Idx, WORD nKey)
{
	WORD Key = 0;

	while(nKey > 1)
	{
		nKey /= 2;
		Key++;
	}
	return (m_aKeyStateTrigger[Idx][Key]) ? TRUE: FALSE;
}

//=============================================================================
// XBOXコントローラーデータ取得(リリース)
//=============================================================================
bool CInputXbox::GetXboxRelease(CONTROLLER_NUM Idx, WORD nKey)
{
	WORD Key = 0;

	while(nKey > 1)
	{
		nKey /= 2;
		Key++;
	}
	return (m_aKeyStateRelease[Idx][Key] != 0) ? TRUE: FALSE;
}

//=============================================================================
// XBOXコントローラーデータ取得(リピート)
//=============================================================================
bool CInputXbox::GetXboxRepeat(CONTROLLER_NUM Idx, WORD nKey)
{
	WORD Key = 0;

	while(nKey > 1)
	{
		nKey /= 2;
		Key++;
	}
	
	return (m_aKeyStateRepeat[Idx][Key] != 0) ? TRUE: FALSE;
}

//=============================================================================
// XBOXコントローラーデータ削除(トリガー)
//=============================================================================
void CInputXbox::FlushXboxTrigger(CONTROLLER_NUM Idx, WORD nKey)
{
	WORD Key = 0;

	while(nKey > 1)
	{
		nKey /= 2;
		Key++;
	}

	m_aKeyStateTrigger[Idx][Key] = 0;
}
//=============================================================================
// アナログ値
//=============================================================================
D3DXVECTOR2 CInputXbox::GetAnalogValue(CONTROLLER_NUM Idx, CInputXbox::VALUE_TYPE type)
{
	return m_Analog[Idx][type];
}
//=============================================================================
// トリガー値
//=============================================================================
int CInputXbox::GetTriggerValue(CONTROLLER_NUM Idx, CInputXbox::VALUE_TYPE type)
{
	return m_Trigger[Idx][type];
}