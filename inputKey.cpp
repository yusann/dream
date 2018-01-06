//=============================================================================
// �L�[����}�l�[�W���[����
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "input.h"
#include "xbox360.h"
#include "sound.h"
#include "inputKey.h"

//*****************************************************************************
//   �ÓI�����o�[�ϐ��錾
//*****************************************************************************
CInputKeyboard *CInputKey::m_pInputKeyboard = NULL;			// �L�[�{�[�h����
CInputXbox *CInputKey::m_pInputXbox = NULL;					// �}�E�X����
CInputMouse *CInputKey::m_pInputMouse = NULL;				// �}�E�X����
CSound *CInputKey::m_pSound = NULL;							// �T�E���h

//==================================================================================================================================================
// ����������
//==================================================================================================================================================
void CInputKey::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �L�[�{�[�h�̐���
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init( hInstance, hWnd );

	// �}�E�X�̐���
	m_pInputMouse = new CInputMouse;
	m_pInputMouse->Init(hInstance, hWnd);

	// Xbox�R���g���[���[�̐���
	m_pInputXbox = new CInputXbox;
	m_pInputXbox->Init();

	// �T�E���h�̐���
	m_pSound = new CSound;
	m_pSound->Init(hWnd);
}

//==================================================================================================================================================
// �I������
//==================================================================================================================================================
void CInputKey::Uninit(void)
{
	// �T�E���h�̔j��
	SAFE_UNINIT(m_pSound);

	// Xbox�R���g���[���[���͂̔j��
	SAFE_UNINIT(m_pInputXbox);

	// �}�E�X���͂̔j��
	SAFE_UNINIT(m_pInputMouse);

	// �L�[�{�[�h���͂̔j��
	SAFE_UNINIT(m_pInputKeyboard);
}

//==================================================================================================================================================
// �X�V����
//==================================================================================================================================================
void CInputKey::Update(void)
{
	m_pInputKeyboard->Update();			// �L�[�{�[�h����
	m_pInputMouse->Update();			// �}�E�X����
	m_pInputXbox->Update();				// Xbox�R���g���[���[����
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
//  �Q�[���S�ʃL�[��������
//=======================================================================================
// �X�^�[�g
BOOL CInputKey::InputGameStart(void)
{
	if (m_pInputKeyboard->GetKeyTrigger(DIK_SPACE) ||
		m_pInputXbox->GetXboxTrigger(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_START)) {
		m_pSound->Play(CSound::SE_ENTER000);
		return TRUE;
	}
	return FALSE;
}
// �|�[�Y���[�h
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
//  �v���C���[�L�[��������
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
// �X�e�B�b�N����̈ړ�����
BOOL CInputKey::InputPlayerMoveStick(void)
{
	D3DXVECTOR2 work = m_pInputXbox->GetAnalogValue(CInputXbox::CONTROLLER_1, CInputXbox::LEFT);
	if (abs(work.x) + abs(work.y) > 0.5f)
	{
		return TRUE;
	}
	return FALSE;
}
// �O�i
BOOL CInputKey::InputPlayerMoveU(void)
{
	if (m_pInputKeyboard->GetKeyPress(DIK_W)) {
		return TRUE;
	}
	return FALSE;
}

// ���
BOOL CInputKey::InputPlayerMoveD(void)
{
	if (m_pInputKeyboard->GetKeyPress(DIK_S)) {
		return TRUE;
	}
	return FALSE;
}

// ���ړ�
BOOL CInputKey::InputPlayerMoveL(void)
{
	if (m_pInputKeyboard->GetKeyPress(DIK_A)) {
		return TRUE;
	}
	return FALSE;
}

// �E�ړ�
BOOL CInputKey::InputPlayerMoveR(void)
{
	if (m_pInputKeyboard->GetKeyPress(DIK_D)) {
		return TRUE;
	}
	return FALSE;
}

// �W�����v
BOOL CInputKey::InputPlayerJump(void)
{
	if (m_pInputKeyboard->GetKeyTrigger(DIK_SPACE)||
		m_pInputXbox->GetXboxTrigger(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_A)) {
		return TRUE;
	}
	return FALSE;
}

// ��U��
BOOL CInputKey::InputPlayerAttack(void)
{
	if (m_pInputKeyboard->GetKeyTrigger(DIK_B) ||
		m_pInputXbox->GetXboxTrigger(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_B)) {
		return TRUE;
	}
	return FALSE;
}

// �_�b�V��
BOOL CInputKey::InputPlayerDash(void)
{
	if (m_pInputKeyboard->GetKeyPress(DIK_Q) || m_pInputKeyboard->GetKeyPress(DIK_E) ||
		m_pInputXbox->GetXboxPress(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_X)) {
		return TRUE;
	}
	return FALSE;
}