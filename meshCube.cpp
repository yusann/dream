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

	// 変換行列の宣言
	D3DXMATRIX mtxRot;             // ローカル回転
	D3DXMATRIX mtxScl;             // ローカルスケール
	D3DXMATRIX mtxPos;             // ローカル座標
	D3DXMATRIX mtxWorld;           // ワールド情報

								   // ローカル回転の代入
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_Rot.y,
		m_Rot.x,
		m_Rot.z);

	// ローカルスケールの代入
	D3DXMatrixScaling(&mtxScl,
		m_Scl.x,
		m_Scl.y,
		m_Scl.z);

	// ローカル座標の代入
	D3DXMatrixTranslation(&mtxPos,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z);

	// ワールド情報処理
	D3DXMatrixIdentity(&mtxWorld);                       // ワールドの中身を初期化
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);   // ワールド回転の代入
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);   // ワールドスケールの代入
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);   // ワールド座標の代入
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);       // ワールド情報セット

														 // 頂点のデクラレーションの設定
	CVertexDecl::SetTex3D(pDevice, m_pVB_POS, m_pVB_NORMAL, m_pVB_COLOR, m_pVB_TEX);

	// デバイスにインデックスバッファの設定
	pDevice->SetIndices(m_pIdxBuff);

	//// インデックスプリミティブの描画
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,                 // プリミティブの種類
	//	0,
	//	0,
	//	m_VexNum,   // 頂点数
	//	0,
	//	m_PolygonNum);                       // プリミティブの数（ポリゴンの数）

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

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_POS) * m_VexNum,           // 作成したい頂点バッファのサイズ（一つの頂点*頂点数）
		D3DUSAGE_WRITEONLY,                         // 書き込むしかしない（チェックしない）
		0,                              // どんな頂点で書くの（0にしてもOK）
		D3DPOOL_MANAGED,                            // メモリ管理をお任せにする
		&m_pVB_POS,
		NULL);

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_POS* v0;
	m_pVB_POS->Lock(0, 0, (void**)&v0, 0);
	for (int i = 0; i < 2; i++, v0 += 4)
	{
		// 頂点情報の設定
		v0[0].pos = D3DXVECTOR3(-0.5f, i * m_Scl.y, 0.5);
		v0[1].pos = D3DXVECTOR3(0.5f, i * m_Scl.y, 0.5);
		v0[2].pos = D3DXVECTOR3(0.5f, i * m_Scl.y, -0.5);
		v0[3].pos = D3DXVECTOR3(-0.5f, i * m_Scl.y, -0.5);
	}
	m_pVB_POS->Unlock();

	// オブジェクトの頂点バッファ(ノーマル座標)を生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_NORMAL) * m_VexNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_NORMAL, NULL))) {
		MessageBox(NULL, "ノーマル座標生成エラー！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_NORMAL* v1;
	m_pVB_NORMAL->Lock(0, 0, (void**)&v1, 0);
	for (int i = 0; i < 2; i++, v1 += 4)
	{
		v1[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // 法線の設定
		v1[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // 法線の設定
		v1[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // 法線の設定
		v1[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // 法線の設定
	}
	m_pVB_NORMAL->Unlock();

	// オブジェクトの頂点バッファ(色)を生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_COLOR) * m_VexNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_COLOR, NULL))) {
		MessageBox(NULL, "頂点色生成エラー！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_COLOR* v2;
	m_pVB_COLOR->Lock(0, 0, (void**)&v2, 0);
	for (int i = 0; i < 2; i++, v2 += 4)
	{
		v2[0].color = m_Color;                       // カラーの設定
		v2[1].color = m_Color;                       // カラーの設定
		v2[2].color = m_Color;                       // カラーの設定
		v2[3].color = m_Color;                       // カラーの設定
	}
	m_pVB_COLOR->Unlock();

	// オブジェクトの頂点バッファ(テクスチャ座標)を生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_TEX) * m_VexNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_TEX, NULL))) {
		MessageBox(NULL, "テクスチャ座標生成エラー！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_TEX* v3;
	m_pVB_TEX->Lock(0, 0, (void**)&v3, 0);
	for (int i = 0; i < 2; i++, v3 += 4)
	{
		v3[0].tex = D3DXVECTOR2(0.25f*0.0f, (1.0f / 3)*(2 - i));            // テクスチャ座標の設定
		v3[1].tex = D3DXVECTOR2(0.25f*1.0f, (1.0f / 3)*(2 - i));            // テクスチャ座標の設定
		v3[2].tex = D3DXVECTOR2(0.25f*2.0f, (1.0f / 3)*(2 - i));            // テクスチャ座標の設定
		v3[3].tex = D3DXVECTOR2(0.25f*3.0f, (1.0f / 3)*(2 - i));            // テクスチャ座標の設定
	}
	m_pVB_TEX->Unlock();
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
