#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "vertexDecl.h"

// ライブラリファイル [構成プロパティ]->[リンカー]->[入力]->[追加の依存ファイル]に記述しても可能
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")         // システム時刻取得に必要
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"dinput8.lib")

// マクロ定義
#define NUM_POLYGON       (2)                                  // ポリゴン数
#define NUM_VERTEX        (4)                                  // 頂点数

//*****************************************************************************
//   レンダラクラスの定義
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();                                   // デフォルトコンストラクタ
	~CRenderer();                                  // デストラクタ
	
	HRESULT Init(HWND hWnd, BOOL bWindow);            // 初期化処理
	void Uninit(void);                             // 終了処理
	bool DrawBegin(void);
	void DrawEnd(void);

	LPDIRECT3DDEVICE9 GetDevice(void);             // デバイスの取得処理

private:
	LPDIRECT3D9				m_pD3D;                // Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;          // Deviceオブジェクト(描画に必要)
	bool					m_bDraw;
};

#endif