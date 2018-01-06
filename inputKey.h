#ifndef _INPUTKEY_H_
#define _INPUTKEY_H_

//   前方宣言
class CInputKeyboard;
class CInputMouse;
class CInputXbox;
class CSound;

//*****************************************************************************
//   入力クラス定義
//*****************************************************************************
class CInputKey
{
public:
	static void Init(HINSTANCE hInstance, HWND hWnd);
	static void Uninit(void);                             // 終了処理
	static void Update(void);                             // 更新処理
	static CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CInputMouse* GetInputMouse(void) { return m_pInputMouse; }
	static CInputXbox* GetInputXbox(void) { return m_pInputXbox; }
	static D3DXVECTOR2 GetAnalogLValue(void);
	static D3DXVECTOR2 GetAnalogRValue(void);

	// ゲーム全般キー判定
	static BOOL InputGameStart(void);
	static BOOL InputPause(void);

	// プレイヤーキー判定
	static BOOL InputPlayerMove(void);				// 移動
	static BOOL InputPlayerMoveStick(void);			// スティック操作の移動
	static BOOL InputPlayerMoveU(void);				// 前進
	static BOOL InputPlayerMoveD(void);				// 後退
	static BOOL InputPlayerMoveL(void);				// 左移動
	static BOOL InputPlayerMoveR(void);				// 右移動
	static BOOL InputPlayerJump(void);				// ジャンプ
	static BOOL InputPlayerAttack(void);			// 攻撃
	static BOOL InputPlayerDash(void);				// ダッシュ

private:
	static CInputKeyboard *m_pInputKeyboard;	// キーボード入力
	static CInputXbox *m_pInputXbox;			// 
	static CInputMouse *m_pInputMouse;			// マウス入力
	static CSound *m_pSound;					// サウンド
};

#endif