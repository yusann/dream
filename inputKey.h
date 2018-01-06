#ifndef _INPUTKEY_H_
#define _INPUTKEY_H_

//   �O���錾
class CInputKeyboard;
class CInputMouse;
class CInputXbox;
class CSound;

//*****************************************************************************
//   ���̓N���X��`
//*****************************************************************************
class CInputKey
{
public:
	static void Init(HINSTANCE hInstance, HWND hWnd);
	static void Uninit(void);                             // �I������
	static void Update(void);                             // �X�V����
	static CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CInputMouse* GetInputMouse(void) { return m_pInputMouse; }
	static CInputXbox* GetInputXbox(void) { return m_pInputXbox; }
	static D3DXVECTOR2 GetAnalogLValue(void);
	static D3DXVECTOR2 GetAnalogRValue(void);

	// �Q�[���S�ʃL�[����
	static BOOL InputGameStart(void);
	static BOOL InputPause(void);

	// �v���C���[�L�[����
	static BOOL InputPlayerMove(void);				// �ړ�
	static BOOL InputPlayerMoveStick(void);			// �X�e�B�b�N����̈ړ�
	static BOOL InputPlayerMoveU(void);				// �O�i
	static BOOL InputPlayerMoveD(void);				// ���
	static BOOL InputPlayerMoveL(void);				// ���ړ�
	static BOOL InputPlayerMoveR(void);				// �E�ړ�
	static BOOL InputPlayerJump(void);				// �W�����v
	static BOOL InputPlayerAttack(void);			// �U��
	static BOOL InputPlayerDash(void);				// �_�b�V��

private:
	static CInputKeyboard *m_pInputKeyboard;	// �L�[�{�[�h����
	static CInputXbox *m_pInputXbox;			// 
	static CInputMouse *m_pInputMouse;			// �}�E�X����
	static CSound *m_pSound;					// �T�E���h
};

#endif