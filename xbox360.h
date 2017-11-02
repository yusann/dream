//=============================================================================
//																			   
//									keyboard.h								
//																				
//=============================================================================
#ifndef _XBOX360_H_
#define _XBOX360_H_

//=============================================================================  
//							定数定義																										
//=============================================================================
#define XBOX_KEY_MAX (16)
//=============================================================================   
//							入力クラス																											
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
	CInputXbox();																//	コンストラクタ
	~CInputXbox();																//	デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);								//	初期化
	void Update(void);															//	更新
	void Uninit(void);															//	終了
	bool GetXboxPress(CONTROLLER_NUM Idx, WORD nKey);							// XBOXコントローラーの入力
	bool GetXboxTrigger(CONTROLLER_NUM Idx, WORD nKey);							// XBOXコントローラーのトリガー
	bool GetXboxRepeat(CONTROLLER_NUM Idx, WORD nKey);							// XBOXコントローラーのリピート
	bool GetXboxRelease(CONTROLLER_NUM Idx, WORD nKey);							// XBOXコントローラーのリリース
	void FlushXboxTrigger(CONTROLLER_NUM Idx, WORD nKey);
	D3DXVECTOR2 GetAnalogValue(CONTROLLER_NUM Idx, CInputXbox::VALUE_TYPE type);	//アナログの値を返す(-1～1)
	int GetTriggerValue(CONTROLLER_NUM Idx, CInputXbox::VALUE_TYPE type);			//	LTの値を返す(0～255)
private:
	WORD		m_aKeyState[CONTROLLER_MAX][XBOX_KEY_MAX];						// XBOXコントローラーの入力情報ワーク
	WORD		m_aKeyStateTrigger[CONTROLLER_MAX][XBOX_KEY_MAX];				// XBOXコントローラーのトリガー情報ワーク
	WORD		m_aKeyStateRelease[CONTROLLER_MAX][XBOX_KEY_MAX];				// XBOXコントローラーのリリース情報ワーク
	WORD		m_aKeyStateRepeat[CONTROLLER_MAX][XBOX_KEY_MAX];				// XBOXコントローラーのリピート情報ワーク
	WORD		m_aKeyStateRepeatCnt[CONTROLLER_MAX][XBOX_KEY_MAX];			// XBOXコントローラーのリピートカウンタ
	D3DXVECTOR2 m_Analog[CONTROLLER_MAX][TYPE_MAX];
	int			m_Trigger[CONTROLLER_MAX][TYPE_MAX];
};


#endif