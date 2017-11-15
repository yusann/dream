//=============================================================================
// メッシュ立方体
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sceneMesh.h"
#include "meshCube.h"
#include "texture.h"

CMeshCube::CMeshCube() :CSceneMesh(CScene::OBJTYPE_DEBUG_MESH)
{
}

CMeshCube::~CMeshCube()
{
}

//=======================================================================================
// 作成処理
//=======================================================================================
CMeshCube *CMeshCube::Create(void)
{
	CMeshCube *pScene3D;                            // 変数宣言
	pScene3D = new CMeshCube;                       // 動的確保
	pScene3D->Init();                            // 初期化
	return pScene3D;                             // 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CMeshCube::Init(void)
{
	// メンバ変数の初期化
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f);

	// プライベート変数の初期化
	m_pIdxBuff = NULL;
	m_PolygonNum = 12;
	m_VexNum = 8;

	// 頂点設定
	MakeVex();
	MakeBuff();

	// テクスチャセット
	m_pTexture = NULL;

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_DEBUG_MESH);

	CSceneMesh::Init();
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CMeshCube::Uninit()
{
	CSceneMesh::Uninit();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CMeshCube::Update(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl)
{
	m_Pos = Pos;
	m_Scl = Scl;
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CMeshCube::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}
	// ライトの設定（OFF）
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	CSceneMesh::Draw();
	// ライトの設定（ON）
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=======================================================================================
// ポリゴンの頂点設定
//=======================================================================================
void CMeshCube::MakeVex(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// 頂点バッファを作る
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_VexNum,           // 作成したい頂点バッファのサイズ（一つの頂点*頂点数）
		D3DUSAGE_WRITEONLY,                                      // 書き込むしかしない（チェックしない）
		FVF_VERTEX_3D,                                           // どんな頂点で書くの（0にしてもOK）
		D3DPOOL_MANAGED,                                         // メモリ管理をお任せにする
		&m_pVtxBuff,
		NULL);

	// 頂点情報格納用疑似バッファの宣言
	VERTEX_3D* pVtx;

	// 頂点バッファをロックして、仮想アドレスを取得する（0,0を記入すると全部をロック）
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < 2; i++, pVtx += 4)
	{
		// 頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(-0.5f, i * m_Scl.y,  0.5);
		pVtx[1].pos = D3DXVECTOR3( 0.5f, i * m_Scl.y,  0.5);
		pVtx[2].pos = D3DXVECTOR3( 0.5f, i * m_Scl.y, -0.5);
		pVtx[3].pos = D3DXVECTOR3(-0.5f, i * m_Scl.y, -0.5);

		pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // 法線の設定
		pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // 法線の設定
		pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // 法線の設定
		pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // 法線の設定

		pVtx[0].color = m_Color;                       // カラーの設定
		pVtx[1].color = m_Color;                       // カラーの設定
		pVtx[2].color = m_Color;                       // カラーの設定
		pVtx[3].color = m_Color;                       // カラーの設定

		pVtx[0].tex = D3DXVECTOR2(0.25f*0.0f, (1.0f/3)*(2-i));            // テクスチャ座標の設定
		pVtx[1].tex = D3DXVECTOR2(0.25f*1.0f, (1.0f/3)*(2-i));            // テクスチャ座標の設定
		pVtx[2].tex = D3DXVECTOR2(0.25f*2.0f, (1.0f/3)*(2-i));            // テクスチャ座標の設定
		pVtx[3].tex = D3DXVECTOR2(0.25f*3.0f, (1.0f/3)*(2-i));            // テクスチャ座標の設定
	}
	// 鍵を開ける
	m_pVtxBuff->Unlock();
}

//=======================================================================================
// ポリゴンのバッファ設定
//=======================================================================================
void CMeshCube::MakeBuff(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// インデックスバッファの作成
	HRESULT hr;
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * (m_PolygonNum+2),        // 頂点数（WORDは16Bid）
									D3DUSAGE_WRITEONLY,              // 使用用途フラグ（書き込むのみ）
									D3DFMT_INDEX16,                  // データのフォーマット（32Bid設定した時16を32に変更）
									D3DPOOL_MANAGED,                 // メモリの管理方法（お任せ）
									&m_pIdxBuff,              // バッファ―インターフェイスポインタのアドレス
									NULL);

	// インデックス情報格納用疑似バッファの宣言
	WORD* pIdx;

	// ロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0] = 4;
	pIdx[1] = 5;
	pIdx[2] = 7;
	pIdx[3] = 6;
	pIdx[4] = 2;
	pIdx[5] = 5;
	pIdx[6] = 1;
	pIdx[7] = 4;
	pIdx[8] = 0;
	pIdx[9] = 7;
	pIdx[10] = 3;
	pIdx[11] = 2;
	pIdx[12] = 0;
	pIdx[13] = 1;

	// ロック解放
	m_pIdxBuff->Unlock();
}
