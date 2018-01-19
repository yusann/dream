#ifndef _MANAGER_H_
#define _MANAGER_H_

#ifdef _DEBUG
#include "imGui/imgui.h"
#include "imGui/imgui_impl_dx9.h"
#endif

//   前方宣言
class CRenderer;
class CSound;
class CTexture;
class CMode;
class CCamera;
class CLight;
class CGBuffer;

#ifdef _DEBUG
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

//*****************************************************************************
//   マネージャークラス定義
//*****************************************************************************
class CManager
{
public:
	CManager();                                   // デフォルトコンストラクタ
	~CManager();                                  // デストラクタ
	
	HRESULT Init( HINSTANCE hInstance,             // 初期化処理
			   HWND      hWnd,
			   BOOL      bWindow);              // フルスクリーンのONOFF
	void Uninit(void);                             // 終了処理
	void Update(void);                             // 更新処理
	void Draw(void);                               // 描画処理

#ifdef _DEBUG
	static void WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return;
	}
#endif
	static void SetMode(CMode *pMode);

	// 取得処理
	static CRenderer *GetRenderer() { return m_pRenderer; }
	static CSound    *GetSound()    { return m_pSound; }
	static CCamera   *GetCamera()   { return m_pCamera; }
	static CLight    *GetLight()    { return m_pLight; }
	static CGBuffer  *GetGBuffer()  { return m_pGBuffer; }

private:
	static CRenderer *m_pRenderer;            // レンダラー
	static CSound *m_pSound;
	static CMode *m_pMode;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CGBuffer *m_pGBuffer;
};

#endif