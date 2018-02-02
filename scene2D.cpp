//=============================================================================
// 2D処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"

//*************
// メイン処理
//*************
CScene2D::CScene2D(int Priority) :CScene(Priority),
m_pVB(NULL),
m_TexPos(D3DXVECTOR2(0.0f,0.0f)),
m_TexScl(D3DXVECTOR2(1.0f, 1.0f)),
m_TexWidth(1),
m_TexHeight(1)
{
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

CScene2D::~CScene2D()
{
}

//==================================================================================================================================================
// 作成処理
//==================================================================================================================================================
CScene2D *CScene2D::Create(const LPDIRECT3DTEXTURE9 pTexture,
	const D3DXVECTOR2 Pos,
	const D3DXVECTOR2 Scl,
	const CScene::OBJTYPE ObjType,
	const int TexWidth,
	const int TexHeight)
{
	CScene2D *pScene2D;                            // 変数宣言
	pScene2D = new CScene2D;                       // 動的確保
	pScene2D->SetInfo(pTexture, Pos, Scl, ObjType, TexWidth, TexHeight);
	pScene2D->Init();                            // 初期化
	pScene2D->SetTexID();
	return pScene2D;                             // 値を返す
}

//=======================================================================================
//   情報の代入
//=======================================================================================
void CScene2D::SetInfo(const LPDIRECT3DTEXTURE9 pTexture,
	const D3DXVECTOR2 Pos,
	const D3DXVECTOR2 Scl,
	const CScene::OBJTYPE ObjType,
	const int TexWidth,
	const int TexHeight)
{
	m_pTexture = pTexture;
	m_Pos = D3DXVECTOR3(Pos.x, Pos.y, 0.0f);
	m_Scl = D3DXVECTOR3(Scl.x, Scl.y, 0.0f);
	m_TexWidth = TexWidth;
	m_TexHeight = TexHeight;
	CScene::SetObjType(ObjType);
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CScene2D::Init()
{
	// 頂点設定
	MakeVex();
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CScene2D::Uninit()
{
	CScene::Release();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CScene2D::Update()
{
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CScene2D::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// 頂点のデクラレーションの設定
	CVertexDecl::SetTex2D(pDevice, m_pVB);

	// 描画直前にテクスチャをセット（テクスチャの設定）
	pDevice->SetTexture( 0, m_pTexture );

	// ポリゴンの描画
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,        // プリミティブの種類
							0,                          // オフセット（頂点数）
							NUM_POLYGON );              // プリミティブの数（ポリゴンの数）
}

//=======================================================================================
// ポリゴンの頂点設定
//=======================================================================================
void CScene2D::MakeVex(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer( sizeof( CVertexDecl::VERTEX2D ) * NUM_VERTEX,           // 作成したい頂点バッファのサイズ（一つの頂点*頂点数）
								 D3DUSAGE_WRITEONLY,                         // 書き込むしかしない（チェックしない）
								 0,                              // どんな頂点で書くの（0にしてもOK）
								 D3DPOOL_MANAGED,                            // メモリ管理をお任せにする
								 &m_pVB,
								 NULL );

	// 頂点情報を設定
	// 頂点情報格納用疑似バッファの宣言
	CVertexDecl::VERTEX2D* pVtx;

	// 頂点バッファをロックして、仮想アドレスを取得する（0,0を記入すると全部をロック）
	m_pVB->Lock( 0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定（ 2D座標・右回り ）
	pVtx[0].pos = D3DXVECTOR4( m_Pos.x          , m_Pos.y          , 0.0f, 1.0f);                 // 左上の座標
	pVtx[1].pos = D3DXVECTOR4( m_Pos.x + m_Scl.x, m_Pos.y          , 0.0f, 1.0f);                 // 右上の座標
	pVtx[2].pos = D3DXVECTOR4( m_Pos.x          , m_Pos.y + m_Scl.y, 0.0f, 1.0f);                 // 左下の座標
	pVtx[3].pos = D3DXVECTOR4( m_Pos.x + m_Scl.x, m_Pos.y + m_Scl.y, 0.0f, 1.0f);                 // 右下の座標

	// 頂点カラーの設定（0~255の整数値）
	pVtx[0].color = m_Color;  // 左上の色
	pVtx[1].color = m_Color;  // 右上の色
	pVtx[2].color = m_Color;  // 左下の色
	pVtx[3].color = m_Color;  // 右下の色

	// 頂点データへUVデータの追加
	pVtx[0].tex = m_TexPos;                    // 左上のUV座標
	pVtx[1].tex = D3DXVECTOR2(m_TexPos.x+ m_TexScl.x, m_TexPos.y);                    // 右上のUV座標
	pVtx[2].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y + m_TexScl.y);                    // 左下のUV座標
	pVtx[3].tex = m_TexPos+ m_TexScl;                    // 右下のUV座標

	// 鍵を開ける
	m_pVB->Unlock();
}

//=======================================================================================
// ポリゴンの色更新
//=======================================================================================
void CScene2D::SetVexColor(D3DXCOLOR Color)
{
	m_Color = Color;
	// 頂点情報を設定
	// 頂点情報格納用疑似バッファの宣言
	CVertexDecl::VERTEX2D* pVtx;

	// 頂点バッファをロックして、仮想アドレスを取得する（0,0を記入すると全部をロック）
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定（0~255の整数値）
	pVtx[0].color = m_Color;  // 左上の色
	pVtx[1].color = m_Color;  // 右上の色
	pVtx[2].color = m_Color;  // 左下の色
	pVtx[3].color = m_Color;  // 右下の色

	// 鍵を開ける
	m_pVB->Unlock();
}


//=======================================================================================
// ポリゴンのサイズ更新
//=======================================================================================
void CScene2D::SetVexPos()
{
	// 頂点情報を設定
	// 頂点情報格納用疑似バッファの宣言
	CVertexDecl::VERTEX2D* pVtx;

	// 頂点バッファをロックして、仮想アドレスを取得する（0,0を記入すると全部をロック）
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定（ 2D座標・右回り ）
	pVtx[0].pos = D3DXVECTOR4(m_Pos.x          , m_Pos.y, 0.0f,1.0f);                 // 左上の座標
	pVtx[1].pos = D3DXVECTOR4(m_Pos.x + m_Scl.x, m_Pos.y, 0.0f,1.0f);                 // 右上の座標
	pVtx[2].pos = D3DXVECTOR4(m_Pos.x          , m_Pos.y + m_Scl.y, 0.0f,1.0f);                 // 左下の座標
	pVtx[3].pos = D3DXVECTOR4(m_Pos.x + m_Scl.x, m_Pos.y + m_Scl.y, 0.0f,1.0f);                 // 右下の座標

							// 鍵を開ける
	m_pVB->Unlock();
}


//=======================================================================================
// ポリゴンのUV座標更新
//=======================================================================================
void CScene2D::SetVexUV()
{
	// 頂点情報を設定
	// 頂点情報格納用疑似バッファの宣言
	CVertexDecl::VERTEX2D* pVtx;

	// 頂点バッファをロックして、仮想アドレスを取得する（0,0を記入すると全部をロック）
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点データへUVデータの追加
	pVtx[0].tex = m_TexPos;                    // 左上のUV座標
	pVtx[1].tex = D3DXVECTOR2(m_TexPos.x+ m_TexScl.x, m_TexPos.y);                    // 右上のUV座標
	pVtx[2].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y + m_TexScl.y);                    // 左下のUV座標
	pVtx[3].tex = m_TexPos+ m_TexScl;                    // 右下のUV座標

							// 鍵を開ける
	m_pVB->Unlock();
}
//=======================================================================================
//   テクスチャIDセット
//=======================================================================================
void CScene2D::SetTexID(int nID)
{
	// テクスチャのスケール代入
	m_TexScl.x = 1.0f / m_TexWidth;
	m_TexScl.y = 1.0f / m_TexHeight;

	// テクスチャ座標の代入
	m_TexPos.x = nID % m_TexWidth * m_TexScl.x;		//  X座標
	m_TexPos.y = nID / m_TexWidth * m_TexScl.y;		//  Y座標
	
	// 頂点情報格納用疑似バッファの宣言
	CVertexDecl::VERTEX2D* pVtx;
	// 頂点バッファをロックして、仮想アドレスを取得する（0,0を記入すると全部をロック）
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点データへUVデータの追加
	pVtx[0].tex = D3DXVECTOR2(m_TexPos.x + 0.001f             , m_TexPos.y + 0.001f);                    // 左上のUV座標
	pVtx[1].tex = D3DXVECTOR2(m_TexPos.x - 0.001f + m_TexScl.x, m_TexPos.y + 0.001f);                    // 右上のUV座標
	pVtx[2].tex = D3DXVECTOR2(m_TexPos.x + 0.001f             , m_TexPos.y - 0.001f + m_TexScl.y);                    // 左下のUV座標
	pVtx[3].tex = D3DXVECTOR2(m_TexPos.x - 0.001f + m_TexScl.x, m_TexPos.y - 0.001f + m_TexScl.y);                    // 右下のUV座標

	m_pVB->Unlock();
}

//=======================================================================================
// ゲージ更新処理
//=======================================================================================
void CScene2D::SetVexGage(float Val)
{
	float sclX = m_Scl.x * Val;
	float tex_sclX = m_TexScl.x * Val;
	// 頂点情報を設定
	// 頂点情報格納用疑似バッファの宣言
	CVertexDecl::VERTEX2D* pVtx;

	// 頂点バッファをロックして、仮想アドレスを取得する（0,0を記入すると全部をロック）
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);
	
	// 頂点座標の設定（ 2D座標・右回り ）
	pVtx[0].pos = D3DXVECTOR4(m_Pos.x          , m_Pos.y, 0.0f,1.0f);                 // 左上の座標
	pVtx[1].pos = D3DXVECTOR4(m_Pos.x + sclX, m_Pos.y, 0.0f,1.0f);                 // 右上の座標
	pVtx[2].pos = D3DXVECTOR4(m_Pos.x          , m_Pos.y + m_Scl.y, 0.0f,1.0f);                 // 左下の座標
	pVtx[3].pos = D3DXVECTOR4(m_Pos.x + sclX, m_Pos.y + m_Scl.y, 0.0f,1.0f);                 // 右下の座標

	// 頂点データへUVデータの追加
	pVtx[0].tex = m_TexPos;                    // 左上のUV座標
	pVtx[1].tex = D3DXVECTOR2(m_TexPos.x + tex_sclX, m_TexPos.y);                    // 右上のUV座標
	pVtx[2].tex = D3DXVECTOR2(m_TexPos.x, m_TexPos.y + m_TexScl.y);                    // 左下のUV座標
	pVtx[3].tex = D3DXVECTOR2(m_TexPos.x + tex_sclX, m_TexPos.y + m_TexScl.y);                    // 右下のUV座標

	// 鍵を開ける
	m_pVB->Unlock();
}