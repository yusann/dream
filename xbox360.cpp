//*****************************************************************************
//																			   
//								light.cpp								
//												
//*****************************************************************************
//=============================================================================
// �w�b�_�t�@�C��
//=============================================================================
#include "main.h"
#include "input.h"
#include "xbox360.h"
#define REPEAT_COUNT (20)
#define ANALOG_METER_MAX (32767.0f)
//=============================================================================
// CInputXbox�R���X�g���X�^
//=============================================================================
CInputXbox::CInputXbox()
{
	// �e���[�N�̃N���A
	ZeroMemory(m_aKeyState, sizeof m_aKeyState);
	ZeroMemory(m_aKeyStateTrigger, sizeof m_aKeyStateTrigger);
	ZeroMemory(m_aKeyStateRelease, sizeof m_aKeyStateRelease);
	ZeroMemory(m_aKeyStateRepeat, sizeof m_aKeyStateRepeat);
	ZeroMemory(m_aKeyStateRepeatCnt, sizeof m_aKeyStateRepeatCnt);
}

//=============================================================================
// CInputXbox�f�X�g���X�^
//=============================================================================
CInputXbox::~CInputXbox()
{
}

//=============================================================================
// XBOX�R���g���[���[�̏���������
//=============================================================================
HRESULT CInputXbox::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr = S_OK;

	return hr;
}

//=============================================================================
// XBOX�R���g���[���[���͏����̊J��
//=============================================================================
void CInputXbox::Uninit(void)
{
	// ���͏����̊J��
	CInput::Uninit();
}

//=============================================================================
// XBOX�R���g���[���[�̍X�V����
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
// XBOX�R���g���[���[�f�[�^�擾(�v���X)
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
// XBOX�R���g���[���[�f�[�^�擾(�g���K�[)
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
// XBOX�R���g���[���[�f�[�^�擾(�����[�X)
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
// XBOX�R���g���[���[�f�[�^�擾(���s�[�g)
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
// XBOX�R���g���[���[�f�[�^�폜(�g���K�[)
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
// �A�i���O�l
//=============================================================================
D3DXVECTOR2 CInputXbox::GetAnalogValue(CONTROLLER_NUM Idx, CInputXbox::VALUE_TYPE type)
{
	return m_Analog[Idx][type];
}
//=============================================================================
// �g���K�[�l
//=============================================================================
int CInputXbox::GetTriggerValue(CONTROLLER_NUM Idx, CInputXbox::VALUE_TYPE type)
{
	return m_Trigger[Idx][type];
}