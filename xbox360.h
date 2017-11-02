//=============================================================================
//																			   
//									keyboard.h								
//																				
//=============================================================================
#ifndef _XBOX360_H_
#define _XBOX360_H_

//=============================================================================  
//							�萔��`																										
//=============================================================================
#define XBOX_KEY_MAX (16)
//=============================================================================   
//							���̓N���X																											
//=============================================================================
class CInputXbox : public CInput
{
public:
	typedef enum
	{
		CONTROLLER_1 = 0,
		CONTROLLER_2,
		CONTROLLER_3,
		CONTROLLER_4,
		CONTROLLER_MAX
	
	}CONTROLLER_NUM;
	typedef enum
	{
		LEFT = 0,
		RIGHT,
		TYPE_MAX
	}VALUE_TYPE;
	CInputXbox();																//	�R���X�g���N�^
	~CInputXbox();																//	�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);								//	������
	void Update(void);															//	�X�V
	void Uninit(void);															//	�I��
	bool GetXboxPress(CONTROLLER_NUM Idx, WORD nKey);							// XBOX�R���g���[���[�̓���
	bool GetXboxTrigger(CONTROLLER_NUM Idx, WORD nKey);							// XBOX�R���g���[���[�̃g���K�[
	bool GetXboxRepeat(CONTROLLER_NUM Idx, WORD nKey);							// XBOX�R���g���[���[�̃��s�[�g
	bool GetXboxRelease(CONTROLLER_NUM Idx, WORD nKey);							// XBOX�R���g���[���[�̃����[�X
	void FlushXboxTrigger(CONTROLLER_NUM Idx, WORD nKey);
	D3DXVECTOR2 GetAnalogValue(CONTROLLER_NUM Idx, CInputXbox::VALUE_TYPE type);	//�A�i���O�̒l��Ԃ�(-1�`1)
	int GetTriggerValue(CONTROLLER_NUM Idx, CInputXbox::VALUE_TYPE type);			//	LT�̒l��Ԃ�(0�`255)
private:
	WORD		m_aKeyState[CONTROLLER_MAX][XBOX_KEY_MAX];						// XBOX�R���g���[���[�̓��͏�񃏁[�N
	WORD		m_aKeyStateTrigger[CONTROLLER_MAX][XBOX_KEY_MAX];				// XBOX�R���g���[���[�̃g���K�[��񃏁[�N
	WORD		m_aKeyStateRelease[CONTROLLER_MAX][XBOX_KEY_MAX];				// XBOX�R���g���[���[�̃����[�X��񃏁[�N
	WORD		m_aKeyStateRepeat[CONTROLLER_MAX][XBOX_KEY_MAX];				// XBOX�R���g���[���[�̃��s�[�g��񃏁[�N
	WORD		m_aKeyStateRepeatCnt[CONTROLLER_MAX][XBOX_KEY_MAX];			// XBOX�R���g���[���[�̃��s�[�g�J�E���^
	D3DXVECTOR2 m_Analog[CONTROLLER_MAX][TYPE_MAX];
	int			m_Trigger[CONTROLLER_MAX][TYPE_MAX];
};


#endif