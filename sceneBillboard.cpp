//=============================================================================
// ビルボード処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sceneBillboard.h"
#include "camera.h"
#include "equation.h"

//*************
// メイン処理
//*************
CSceneBillboard::CSceneBillboard(int Priority) :CScene(Priority),
m_pVB_POS(NULL),
m_pVB_NORMAL(NULL),
m_pVB_COLOR(NULL),
m_pVB_TEX(NULL)
{
	m_TexWidth = 1;
	m_TexHeight = 1;
	m_TexPos = D3DXVECTOR2(0.0f, 0.0f);
	m_TexScl = D3DXVECTOR2(1.0f, 1.0f);
	D3DXQuaternionIdentity(&m_Quaternion);
}

CSceneBillboard::~CSceneBillboard()
{
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CSceneBillboard::Init()
{
	m_Angle = CEquation::Angle(m_Scl.x, m_Scl.y);
	m_Length = CEquation::Length(m_Scl.x, m_Scl.y);
	// 頂点設定
	MakeVex();
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CSceneBillboard::Uninit()
{
	SAFE_RELEASE(m_pVB_POS);      // 頂点バッファの破棄
	SAFE_RELEASE(m_pVB_NORMAL);      // 頂点バッファの破棄
	SAFE_RELEASE(m_pVB_COLOR);      // 頂点バッファの破棄
	SAFE_RELEASE(m_pVB_TEX);      // 頂点バッファの破棄
	SAFE_RELEASE( m_pVtxBuff );      // 頂点バッファの破棄
	CScene::Release();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CSceneBillboard::Update()
{
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CSceneBillboard::Draw(DRAWTYPE type)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// 頂点のデクラレーションの設定
	LPDIRECT3DVERTEXDECLARATION9 pDecl = *CVertexDecl::Get(CVertexDecl::TYPE_3D);
	pDevice->SetVertexDeclaration(pDecl);

	// ストリームとして頂点バッファを設定
	pDevice->SetStreamSource(0, m_pVB_POS, 0, sizeof(CVertexDecl::VERTEX3D_POS));
	pDevice->SetStreamSource(1, m_pVB_NORMAL, 0, sizeof(CVertexDecl::VERTEX3D_NORMAL));
	pDevice->SetStreamSource(2, m_pVB_COLOR, 0, sizeof(CVertexDecl::VERTEX3D_COLOR));
	pDevice->SetStreamSource(3, m_pVB_TEX, 0, sizeof(CVertexDecl::VERTEX3D_TEX));

	// 描画直前にテクスチャをセット（テクスチャの設定）
	pDevice->SetTexture(0, m_pTexture);

	// カメラの取得
	CCamera* pCamera;
	pCamera = CManager::GetCamera();

	// 変換行列の宣言
	D3DXMATRIX mtxPos;             // ローカル座標
	D3DXMATRIX mtxWorld;           // ワールド情報
	D3DXMATRIX mtxViewInverse;     // 転置行列
	D3DXMATRIX mtxViewCamera = pCamera->GetMtxView();      // カメラ行列の取得
	
	// ローカル座標の代入
	D3DXMatrixTranslation(&mtxPos,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z);

	// 逆行列の作成
	D3DXMatrixTranspose(&mtxViewInverse, &mtxViewCamera);

	// 平行移動成分を除去（転置前）
	mtxViewInverse._14 = 0.0f;
	mtxViewInverse._24 = 0.0f;
	mtxViewInverse._34 = 0.0f;

	// ワールド情報処理
	D3DXMatrixIdentity(&mtxWorld);                       // ワールドの中身を初期化
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);   // ワールド座標の代入
	mtxWorld = mtxViewInverse * mtxWorld;

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);       // ワールド情報セット
	
	 // アルファテスト（ON）
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);         // アルファテストを可能に
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);                   // 参照値の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);     // 参照値 < α

	// ライトの設定（OFF）
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	switch (type)
	{
	case NORMAL:
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,        // プリミティブの種類
			0,                          // オフセット（頂点数）
			NUM_POLYGON);              // プリミティブの数（ポリゴンの数）
		break;
	case ADD:
		// 加算合成（ON）
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,        // プリミティブの種類
			0,                          // オフセット（頂点数）
			NUM_POLYGON);              // プリミティブの数（ポリゴンの数）

		// 加算合成（OFF）
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	default:
		assert(!"タイプ不正sceneBillboard::Draw()");
		break;
	}

	// ライトの設定（ON）
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// アルファテスト（OFF）
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=======================================================================================
// ポリゴンの頂点設定
//=======================================================================================
void CSceneBillboard::MakeVex(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_POS) * NUM_VERTEX,           // 作成したい頂点バッファのサイズ（一つの頂点*頂点数）
		D3DUSAGE_WRITEONLY,                         // 書き込むしかしない（チェックしない）
		0,                              // どんな頂点で書くの（0にしてもOK）
		D3DPOOL_MANAGED,                            // メモリ管理をお任せにする
		&m_pVB_POS,
		NULL);

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_POS* v0;
	m_pVB_POS->Lock(0, 0, (void**)&v0, 0);
	// スケールを設定
	v0[0].pos = D3DXVECTOR3(cosf(-m_Angle + D3DX_PI) * m_Length,      // X座標の設定
		sinf(-m_Angle + D3DX_PI) * m_Length,      // Y座標の設定
		0.0f);                                   // Z座標の設定
	v0[1].pos = D3DXVECTOR3(cosf(m_Angle) * m_Length,             // X座標の設定
		sinf(m_Angle) * m_Length,             // Y座標の設定
		0.0f);                               // Z座標の設定
	v0[2].pos = D3DXVECTOR3(cosf(m_Angle + D3DX_PI) * m_Length,      // X座標の設定
		sinf(m_Angle + D3DX_PI) * m_Length,      // Y座標の設定
		0.0f);                                  // Z座標の設定
	v0[3].pos = D3DXVECTOR3(cosf(-m_Angle) * m_Length,          // X座標の設定
		sinf(-m_Angle) * m_Length,          // Y座標の設定
		0.0f);                             // Z座標の設定
	m_pVB_POS->Unlock();

	// オブジェクトの頂点バッファ(ノーマル座標)を生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_NORMAL) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_NORMAL, NULL))) {
		MessageBox(NULL, "ノーマル座標生成エラー！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_NORMAL* v1;
	m_pVB_NORMAL->Lock(0, 0, (void**)&v1, 0);

	v1[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v1[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v1[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	v1[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_pVB_NORMAL->Unlock();

	// オブジェクトの頂点バッファ(色)を生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_COLOR) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_COLOR, NULL))) {
		MessageBox(NULL, "頂点色生成エラー！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_COLOR* v2;
	m_pVB_COLOR->Lock(0, 0, (void**)&v2, 0);

	v2[0].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 左上の色
	v2[1].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 右上の色
	v2[2].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 左下の色
	v2[3].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 右下の色
	m_pVB_COLOR->Unlock();

	// オブジェクトの頂点バッファ(テクスチャ座標)を生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_TEX) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_TEX, NULL))) {
		MessageBox(NULL, "テクスチャ座標生成エラー！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	//頂点バッファの中身を埋める
	CVertexDecl::VERTEX3D_TEX* v3;
	m_pVB_TEX->Lock(0, 0, (void**)&v3, 0);
	v3[0].tex = D3DXVECTOR2(0.0f, 0.0f);                    // 左上のUV座標
	v3[1].tex = D3DXVECTOR2(1.0f, 0.0f);                    // 右上のUV座標
	v3[2].tex = D3DXVECTOR2(0.0f, 1.0f);                    // 左下のUV座標
	v3[3].tex = D3DXVECTOR2(1.0f, 1.0f);                    // 右下のUV座標
	m_pVB_TEX->Unlock();
}

//=======================================================================================
//   テクスチャIDセット
//=======================================================================================
void CSceneBillboard::SetTexID(int nID)
{
	// テクスチャのスケール代入
	m_TexScl.x = 1.0f / m_TexWidth;
	m_TexScl.y = 1.0f / m_TexHeight;

	// テクスチャ座標の代入
	m_TexPos.x = nID % m_TexWidth * m_TexScl.x;		//  X座標
	m_TexPos.y = nID / m_TexWidth * m_TexScl.y;		//  Y座標

	// 頂点情報格納用疑似バッファの宣言
	CVertexDecl::VERTEX3D_TEX* pVtx;
	m_pVB_TEX->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点データへUVデータの追加
	pVtx[0].tex = D3DXVECTOR2(m_TexPos.x + 0.001f, m_TexPos.y + 0.001f);                    // 左上のUV座標
	pVtx[1].tex = D3DXVECTOR2(m_TexPos.x - 0.001f + m_TexScl.x, m_TexPos.y + 0.001f);                    // 右上のUV座標
	pVtx[2].tex = D3DXVECTOR2(m_TexPos.x + 0.001f, m_TexPos.y - 0.001f + m_TexScl.y);                    // 左下のUV座標
	pVtx[3].tex = D3DXVECTOR2(m_TexPos.x - 0.001f + m_TexScl.x, m_TexPos.y - 0.001f + m_TexScl.y);                    // 右下のUV座標

	// 鍵を開ける
	m_pVB_TEX->Unlock();
}
