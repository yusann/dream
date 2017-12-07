//=============================================================================
// スカイドーム
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sceneMesh.h"
#include "skyDome.h"
#include "texture.h"

CSkyDome::CSkyDome() :CSceneMesh(CScene::OBJTYPE_FIELD)
{
}

CSkyDome::~CSkyDome()
{
}

//==================================================================================================================================================
// 作成処理
//==================================================================================================================================================
CSkyDome *CSkyDome::Create(D3DXVECTOR3 pos, float radius, int numBlockX, int numBlockY, D3DXCOLOR color)
{
	CSkyDome *pScene3D;                            // 変数宣言
	pScene3D = new CSkyDome;                       // 動的確保
	pScene3D->Init(pos, radius, numBlockX, numBlockY, color);                            // 初期化
	return pScene3D;                             // 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CSkyDome::Init(D3DXVECTOR3 pos, float radius, int numBlockX, int numBlockY, D3DXCOLOR color)
{
	// メンバ変数の初期化
	m_Pos = pos;

	// プライベート変数の初期化
	m_pIdxBuff = NULL;
	m_VexNum = (numBlockY * ((numBlockX + 1) * 2)) + ((numBlockY - 1) * 2);
	m_PolygonNum = m_VexNum - 2;

	m_Radius = radius;
	m_NumBlockX = numBlockX;
	m_NumBlockY = numBlockY;
	m_Color = color;

	// 頂点設定
	MakeVex();
	MakeBuff();

	// テクスチャセット
	m_pTexture = CTexture::GetTexture((int)CTexture::TEXTYPE_SKY000);

	// タイプの代入
	CSceneMesh::Init();
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CSkyDome::Uninit()
{
	CSceneMesh::Uninit();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CSkyDome::Update()
{
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CSkyDome::Draw()
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
void CSkyDome::MakeVex(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_POS) * ((m_NumBlockX + 1) * (m_NumBlockY + 1)),           // 作成したい頂点バッファのサイズ（一つの頂点*頂点数）
		D3DUSAGE_WRITEONLY,                         // 書き込むしかしない（チェックしない）
		0,                              // どんな頂点で書くの（0にしてもOK）
		D3DPOOL_MANAGED,                            // メモリ管理をお任せにする
		&m_pVB_POS,
		NULL);

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_POS* v0;
	m_pVB_POS->Lock(0, 0, (void**)&v0, 0);

	// 半径を記憶
	float Radius = m_Radius;
	for (int nCntHeight = 0; nCntHeight < m_NumBlockY + 1; nCntHeight++)
	{
		m_Radius = cos(D3DXToRadian((90 / m_NumBlockY) * nCntHeight)) * Radius;
		for (int nCntWidth = 0; nCntWidth < m_NumBlockX + 1; nCntWidth++, v0++)
		{
			// 頂点情報の設定
			v0[0].pos = D3DXVECTOR3(cos(D3DXToRadian((360 / m_NumBlockX) * nCntWidth)) * m_Radius,      // X座標の設定（ 3D座標・右回り ）
				sin(D3DXToRadian(((90 / m_NumBlockY) * nCntHeight))) * Radius,                                                                            // Y座標の設定
				sin(D3DXToRadian((360 / m_NumBlockX) * nCntWidth)) * m_Radius);    // Z座標の設定
		}
	}
	m_pVB_POS->Unlock();

	// オブジェクトの頂点バッファ(ノーマル座標)を生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_NORMAL) * ((m_NumBlockX + 1) * (m_NumBlockY + 1)),
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_NORMAL, NULL))) {
		MessageBox(NULL, "ノーマル座標生成エラー！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_NORMAL* v1;
	m_pVB_NORMAL->Lock(0, 0, (void**)&v1, 0);

	for (int nCntHeight = 0; nCntHeight < m_NumBlockY + 1; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < m_NumBlockX + 1; nCntWidth++, v1++)
		{
			v1[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // 法線の設定
		}
	}
	m_pVB_NORMAL->Unlock();

	// オブジェクトの頂点バッファ(色)を生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_COLOR) * ((m_NumBlockX + 1) * (m_NumBlockY + 1)),
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_COLOR, NULL))) {
		MessageBox(NULL, "頂点色生成エラー！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_COLOR* v2;
	m_pVB_COLOR->Lock(0, 0, (void**)&v2, 0);

	for (int nCntHeight = 0; nCntHeight < m_NumBlockY + 1; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < m_NumBlockX + 1; nCntWidth++, v2++)
		{
			v2[0].color = m_Color;                       // カラーの設定
		}
	}
	m_pVB_COLOR->Unlock();

	// オブジェクトの頂点バッファ(テクスチャ座標)を生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_TEX) * ((m_NumBlockX + 1) * (m_NumBlockY + 1)),
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_TEX, NULL))) {
		MessageBox(NULL, "テクスチャ座標生成エラー！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_TEX* v3;
	m_pVB_TEX->Lock(0, 0, (void**)&v3, 0);

	for (int nCntHeight = 0; nCntHeight < m_NumBlockY + 1; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < m_NumBlockX + 1; nCntWidth++, v3++)
		{
			v3[0].tex = D3DXVECTOR2(nCntWidth * (1.0f / m_NumBlockX),              // テクスチャU座標の設定
				(m_NumBlockY - nCntHeight) * (1.0f / m_NumBlockY));            // テクスチャV座標の設定

		}
	}
	m_pVB_TEX->Unlock();
}


//=======================================================================================
// ポリゴンのバッファ設定
//=======================================================================================
void CSkyDome::MakeBuff(void)
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
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * m_VexNum,        // 頂点数（WORDは16Bid）
									D3DUSAGE_WRITEONLY,              // 使用用途フラグ（書き込むのみ）
									D3DFMT_INDEX16,                  // データのフォーマット（32Bid設定した時16を32に変更）
									D3DPOOL_MANAGED,                 // メモリの管理方法（お任せ）
									&m_pIdxBuff,              // バッファ―インターフェイスポインタのアドレス
									NULL);

	// インデックス情報格納用疑似バッファの宣言
	WORD* pIdx;

	// ロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// Z軸のループ
	for (int nCntHeight = 0; nCntHeight < m_NumBlockY; nCntHeight++)
	{
		// X軸のループ
		for (int nCntWidth = 0; nCntWidth < m_NumBlockX + 1; nCntWidth++, pIdx += 2)                          // ループするとpIdxを2つ前進
		{
			// 法線裏向き
			// 1列目以外の1行目の処理
			if (nCntHeight != 0 && nCntWidth == 0) {
				pIdx[0] = (unsigned short)((m_NumBlockX + 1) + (nCntHeight * (m_NumBlockX + 1) + nCntWidth));                  // 同じ処にインデックスをうつ
				pIdx += 1;                                                                               // 1つ前進
			}
			// 重複しない頂点の処理
			pIdx[0] = (unsigned short)((m_NumBlockX + 1) + (nCntHeight * (m_NumBlockX + 1) + nCntWidth));
			pIdx[1] = (unsigned short)((m_NumBlockX + 1) + (nCntHeight * (m_NumBlockX + 1) + nCntWidth) - (m_NumBlockX + 1));

			// 最終列目以外の最終行目の処理
			if (nCntHeight != m_NumBlockY - 1 && nCntWidth == m_NumBlockX) {
				pIdx[2] = (unsigned short)((m_NumBlockX + 1) + (nCntHeight * (m_NumBlockX + 1) + nCntWidth) - (m_NumBlockX + 1));  // 同じ処にインデックスをうつ
				pIdx += 1;                                                                               // 1つ前進
			}
		}
	}

	// ロック解放
	m_pIdxBuff->Unlock();
}
