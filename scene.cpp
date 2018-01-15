//=============================================================================
// シーン処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"

#include "manager.h"
#include "light.h"

//   静的メンバ変数
CScene *CScene::m_Top[OBJTYPE_MAX] = {};        // シーン
int CScene::m_NumScene = 0;                        // 総数

//*************
// メイン処理
//*************
CScene::CScene( int Priority ) :
	m_Prev(NULL),
	m_Next(NULL),
	m_Priority(NULL),
	m_ObjType(OBJTYPE_MAX),
	m_Pos(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_Scl(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_Color(D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f)),
	m_pTexture(NULL)
{
	if( m_Top[ Priority ] == NULL )      // NULLだったら
	{
		m_Top[ Priority ] = this;        // 自分を代入
		m_Priority = Priority;
		m_NumScene++;                        // 総数をカウント
	}
	else
	{
		CScene *scene = m_Top[ Priority ];
		while (scene->m_Next != NULL)
		{
			scene = scene->m_Next;
		}
		scene->m_Next = this;
		scene->m_Next->m_Priority = Priority;
		scene->m_Next->m_Prev = scene;
		m_NumScene++;                        // 総数をカウント
	}
}

CScene::~CScene()
{
}

//==================================================================================================================================================
//   更新処理
//==================================================================================================================================================
void CScene::UpdateAll(void)
{
	// 最大数分ループ
	for( int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++ )
	{
		CScene *scene = m_Top[nCntPriority];
		while (scene != NULL)      // NULLだったら
		{
			CScene *NextScene = scene->m_Next;
			scene->Update();
			scene = NextScene;
		}
	}
}

//==================================================================================================================================================
//   描画処理
//==================================================================================================================================================
void CScene::DrawAll(void)
{
	// 最大数分ループ
	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		CScene *scene = m_Top[nCntPriority];
		while (scene != NULL)      // NULLだったら
		{
			CScene *NextScene = scene->m_Next;
			scene->Draw();
			scene = NextScene;
		}
	}

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	LPDIRECT3DSURFACE9 campus, back;
	pDevice->GetRenderTarget(0, &back);

	CManager::GetLight()->GetTexture()->GetSurfaceLevel(0, &campus);
	pDevice->SetRenderTarget(0, campus);

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL,                                 //
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,   // カラーバッファ | 深さ（深度）バッファ（クリアフラグ）
		D3DCOLOR_RGBA(0, 0, 0, 0),                       // 初期化色
		1.0f,                                                    // 0~1（0は手前、1は遠い）
		0);

	// 最大数分ループ
	for( int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++ )
	{
		CScene *scene = m_Top[nCntPriority];
		while(scene != NULL)      // NULLだったら
		{
			CScene *NextScene = scene->m_Next;
			scene->DrawDepth();
			scene = NextScene;
		}
	}
	pDevice->SetRenderTarget(0, back);

}

//==================================================================================================================================================
//   リリース処理
//==================================================================================================================================================
void CScene::ReleaseAll(int CntMax)
{
	// 最大数分ループ
	for( int nCntPriority = 0; nCntPriority < CntMax; nCntPriority++ )
	{
		CScene *scene = m_Top[nCntPriority];
		CScene *sceneNext;
		while (scene != NULL)      // NULLだったら
		{
			sceneNext = scene->m_Next;
			scene->Uninit();
			scene = sceneNext;
		}
		m_Top[nCntPriority] = NULL;
	}
}

//==================================================================================================================================================
//   sceneのリリース処理
//==================================================================================================================================================
void CScene::Release(void)
{
	CScene *scene = this;
	if (scene != NULL)      // NULLだったら
	{
		if (scene->m_Prev != NULL)
		{
			// 前のシーンのNEXTアドレスの代入
			scene->m_Prev->m_Next = scene->m_Next;
			// 後のシーンのPREVアドレスの代入
			if (scene->m_Next != NULL)
			{
				scene->m_Next->m_Prev = scene->m_Prev;
			}
		}
		else
		{
			// thisはトップシーンの場合トップシーンを初期化
			if (scene->m_Next != NULL)
			{
				m_Top[m_Priority] = scene->m_Next;
				m_Top[m_Priority]->m_Prev = NULL;
			}
			else
			{
				m_Top[m_Priority] = NULL;
			}
		}
		delete scene;			// sceneを消す
		m_NumScene--;			// 総数をカウント
	}
}
