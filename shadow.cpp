//=============================================================================
// 影
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"

#include "shadow.h"
#include "texture.h"
#include "equation.h"

CShadow::CShadow(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl) :CScene(CScene::OBJTYPE_SHADOW)
{
	m_Pos = Pos;
	m_Scl = Scl;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
}

CShadow::~CShadow()
{
}

//=======================================================================================
//   生成処理
//=======================================================================================
CShadow* CShadow::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl)
{
	CShadow *pScene3D;                            // 変数宣言
	pScene3D = new CShadow(Pos, Scl);                       // 動的確保
	pScene3D->Init();                            // 初期化
	return pScene3D;                             // 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CShadow::Init()
{
	m_pTexture = CTexture::GetTexture(CTexture::TEXTYPE_BULLET);

	// 頂点設定
	MakeVex();

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_SHADOW);
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CShadow::Uninit()
{
	SAFE_RELEASE(m_pVtxBuff);      // 頂点バッファの破棄
	CScene::Release();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CShadow::Update()
{
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CShadow::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 Pos = m_Pos;
	Pos.y += 0.1f;
	D3DXVECTOR3 Rot = D3DXVECTOR3(3.14159265f*0.5f,0.0f ,0.0f);
	D3DXVECTOR3 Scl = D3DXVECTOR3(m_Scl.z, m_Scl.z, 1.0f);

	CEquation::SetMatrix(&mtxWorld, Pos, Rot,Scl);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0,
		m_pVtxBuff,              // ストリームのもとになる頂点のバッファの始点
		0,                       // オフセット（バイト）
		sizeof(VERTEX_3D));      // 一つの頂点データのサイズ（ストライド量）

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// 描画直前にテクスチャをセット（テクスチャの設定）
	pDevice->SetTexture(0, m_pTexture);

	// 減算処理ON
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

	// Zバッファの書込み設定（OFF）
	//pDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,        // プリミティブの種類
		0,                          // オフセット（頂点数）
		NUM_POLYGON);              // プリミティブの数（ポリゴンの数）
	

	// Zバッファの書込み設定（OFF）
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE );

	// 減算クリア
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}

//=======================================================================================
// ポリゴンの頂点設定
//=======================================================================================
void CShadow::MakeVex(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,           // 作成したい頂点バッファのサイズ（一つの頂点*頂点数）
		D3DUSAGE_WRITEONLY,                         // 書き込むしかしない（チェックしない）
		FVF_VERTEX_3D,                              // どんな頂点で書くの（0にしてもOK）
		D3DPOOL_MANAGED,                            // メモリ管理をお任せにする
		&m_pVtxBuff,
		NULL);

	// 頂点情報を設定
	// 頂点情報格納用疑似バッファの宣言
	VERTEX_3D* pVtx;

	// 頂点バッファをロックして、仮想アドレスを取得する（0,0を記入すると全部をロック）
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定（ 2D座標・右回り ）
	pVtx[0].pos = D3DXVECTOR3(-m_Scl.x, m_Scl.y ,0.0f);                 // 左上の座標
	pVtx[1].pos = D3DXVECTOR3(m_Scl.x , m_Scl.y ,0.0f);                 // 右上の座標
	pVtx[2].pos = D3DXVECTOR3(-m_Scl.x, -m_Scl.y,0.0f);                 // 左下の座標
	pVtx[3].pos = D3DXVECTOR3(m_Scl.x , -m_Scl.y,0.0f);                 // 右下の座標

	// 頂点法線の設定
	pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);


	// 頂点カラーの設定（0~255の整数値）
	pVtx[0].color = m_Color;  // 左上の色
	pVtx[1].color = m_Color;  // 右上の色
	pVtx[2].color = m_Color;  // 左下の色
	pVtx[3].color = m_Color;  // 右下の色

														// 頂点データへUVデータの追加
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);                    // 左上のUV座標
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);                    // 右上のUV座標
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);                    // 左下のUV座標
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);                    // 右下のUV座標

															  // 鍵を開ける
	m_pVtxBuff->Unlock();
}