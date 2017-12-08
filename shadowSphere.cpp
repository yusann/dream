//=============================================================================
// 影
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "shadowSphere.h"

//*************
// メイン処理
//*************
CShadowSphere::CShadowSphere() :
m_pVB_POS(NULL),
m_pVB_NORMAL(NULL),
m_pVB_COLOR(NULL),
m_pVB_TEX(NULL) {}
CShadowSphere::~CShadowSphere() {}

// 変数初期化
CShadowSphere::CShadowSphere(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXCOLOR color, D3DXVECTOR3 pos)
	: m_SpherePos(pos),
	m_SphereScl(scl),
	m_SphereRadius(radius),
	m_Color(color),
	m_SphereNumX(numBlockX),
	m_SphereNumY(numBlockY),
	m_pVB_POS(NULL),
	m_pVB_NORMAL(NULL),
	m_pVB_COLOR(NULL),
	m_pVB_TEX(NULL)
{
	m_VtxBuff = NULL;
	m_SphereIdxBuff = NULL;
	m_SphereVtxBuff = NULL;
	m_IndexNum = numBlockY * numBlockX * 2 + ((numBlockY - 1) * 4) + 2;
	m_PolygonNum = m_IndexNum - 2;
	m_VexNum = m_SphereNumX * (m_SphereNumY - 1) + 2;
}

//==============================================================================
//  生成処理
//==============================================================================
CShadowSphere *CShadowSphere::Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl)
{	// デフォルト
	CShadowSphere *pSceneMD;
	pSceneMD = new CShadowSphere(numBlockX, numBlockY, radius, scl, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pSceneMD->Init();
	return pSceneMD;
}
CShadowSphere *CShadowSphere::Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXVECTOR3 pos)
{	// 座標指定
	CShadowSphere *pSceneMD;
	pSceneMD = new CShadowSphere(numBlockX, numBlockY, radius, scl, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f),pos);
	pSceneMD->Init();
	return pSceneMD;
}
CShadowSphere *CShadowSphere::Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXCOLOR color)
{	// 色指定
	CShadowSphere *pSceneMD;
	pSceneMD = new CShadowSphere(numBlockX, numBlockY, radius, scl, color, D3DXVECTOR3(0.0f,0.0f,0.0f));
	pSceneMD->Init();
	return pSceneMD;
}

//==============================================================================
//  初期化処理
//==============================================================================
void CShadowSphere::Init( void )
{
	MakeVex();				// 影頂点
	MakeSphereVex();		// スフィア頂点
	MakeSphereBuff();		// スフィアインデクス
}

//==============================================================================
//  終了処理
//==============================================================================
void CShadowSphere::Uninit( void )
{
	SAFE_RELEASE(m_pVB_POS);      // 頂点バッファの破棄
	SAFE_RELEASE(m_pVB_NORMAL);      // 頂点バッファの破棄
	SAFE_RELEASE(m_pVB_COLOR);      // 頂点バッファの破棄
	SAFE_RELEASE(m_pVB_TEX);      // 頂点バッファの破棄
	SAFE_RELEASE( m_VtxBuff);
	SAFE_RELEASE( m_SphereIdxBuff);
	SAFE_RELEASE( m_SphereVtxBuff);
}

//==============================================================================
//  更新処理
//==============================================================================
void CShadowSphere::Update(const D3DXVECTOR3 pos, const D3DXVECTOR3 scl)
{	// スケール更新
	m_SpherePos = pos;
	m_SphereScl = scl;
}
void CShadowSphere::Update(const D3DXVECTOR3 pos)
{	// 座標更新
	m_SpherePos = pos;
}

//==============================================================================
//  描画処理
//==============================================================================
void CShadowSphere::Draw( void )
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "shadow.cpp => Draw => pDeviceがNULL！！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}
	// ステンシルの設定

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);			// ステンシル有効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// Zバッファ書き込まない
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);			// カラー書き込まない

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);		// 比較関数（必ず合格）
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);					// 参照値

	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Zバッファで引っかかった時（何もしない）
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// 両方ダメだった時（何もしない）
	// 表描画
	//pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_DECR);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);		// 両方に通った時（+1）
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	DrawSphere();
	// 裏描画
	//pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);		// 両方に通った時（-1）
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	DrawSphere();

	// 影の切り取り設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);			// カラー書き込む
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		// 比較関数（等しければ）

	// 影の描画
	// 頂点のデクラレーションの設定
	CVertexDecl::SetTex2D(pDevice, m_VtxBuff);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ステンシル設定のクリア
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// ステンシルをクリア
	pDevice->Clear(0, NULL,
		D3DCLEAR_STENCIL,								// ステンシル
		D3DCOLOR_RGBA(0, 0, 0, 0),				// 初期化色
		1.0f,											// 0~1（0は手前、1は遠い）
		0);

}

//=======================================================================================
// 影頂点設定
//=======================================================================================
void CShadowSphere::MakeVex(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX2D) * NUM_VERTEX,           // 作成したい頂点バッファのサイズ（一つの頂点*頂点数）
		D3DUSAGE_WRITEONLY,                         // 書き込むしかしない（チェックしない）
		0,                              // どんな頂点で書くの（0にしてもOK）
		D3DPOOL_MANAGED,                            // メモリ管理をお任せにする
		&m_VtxBuff,
		NULL);

	// 頂点情報を設定
	// 頂点情報格納用疑似バッファの宣言
	CVertexDecl::VERTEX2D* pVtx;

	// 頂点バッファをロックして、仮想アドレスを取得する（0,0を記入すると全部をロック）
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定（ 2D座標・右回り ）
	pVtx[0].pos = D3DXVECTOR4(        0.0f,          0.0f, 0.0f,1.0f);                 // 左上の座標
	pVtx[1].pos = D3DXVECTOR4(SCREEN_WIDTH,          0.0f, 0.0f,1.0f);                 // 右上の座標
	pVtx[2].pos = D3DXVECTOR4(        0.0f, SCREEN_HEIGHT, 0.0f,1.0f);                 // 左下の座標
	pVtx[3].pos = D3DXVECTOR4(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f,1.0f);                 // 右下の座標

	// 頂点カラーの設定（0~255の整数値）
	pVtx[0].color = m_Color;  // 左上の色
	pVtx[1].color = m_Color;  // 右上の色
	pVtx[2].color = m_Color;  // 左下の色
	pVtx[3].color = m_Color;  // 右下の色

	// 頂点データへUVデータの追加
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);                    // 左上のUV座標
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);                    // 右上のUV座標
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);                    // 左下のUV座標
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);                    // 右下のUV座標

 // 鍵を開ける
	m_VtxBuff->Unlock();
}

//=======================================================================================
// スフィア頂点設定
//=======================================================================================
void CShadowSphere::MakeSphereVex(void)
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

	// 半径を記憶
	float Radius = m_SphereRadius;

	for (int i = 0; i < m_SphereNumY + 1; i++)
	{
		m_SphereRadius = cos(D3DXToRadian((180 / (float)m_SphereNumY) * i - 90)) * Radius;
		if (i == 0 || i == m_SphereNumY)
		{
			// 頂点情報の設定
			v0[0].pos = D3DXVECTOR3(0.0f,
				sin(D3DXToRadian(((-180 / (float)m_SphereNumY) * i - 90))) * Radius,                                                                            // Y座標の設定
				0.0f);
			v0++;
		}
		else
		{
			for (int nCntWidth = 0; nCntWidth < m_SphereNumX; nCntWidth++, v0++)
			{
				// 頂点情報の設定
				v0[0].pos = D3DXVECTOR3(cos(D3DXToRadian((360 / (float)m_SphereNumX) * nCntWidth)) * m_SphereRadius,      // X座標の設定（ 3D座標・右回り ）
					sin(D3DXToRadian(((-180 / (float)m_SphereNumY) * i - 90))) * Radius,                                                                            // Y座標の設定
					sin(D3DXToRadian((360 / (float)m_SphereNumX) * nCntWidth)) * m_SphereRadius);    // Z座標の設定
			}
		}
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
	for (int i = 0; i < m_SphereNumY + 1; i++)
	{
		m_SphereRadius = cos(D3DXToRadian((180 / (float)m_SphereNumY) * i - 90)) * Radius;
		if (i == 0 || i == m_SphereNumY)
		{
			v1[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // 法線の設定
			v1++;
		}
		else
		{
			for (int nCntWidth = 0; nCntWidth < m_SphereNumX; nCntWidth++, v1++)
			{
				v1[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // 法線の設定
			}
		}
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

	for (int i = 0; i < m_SphereNumY + 1; i++)
	{
		m_SphereRadius = cos(D3DXToRadian((180 / (float)m_SphereNumY) * i - 90)) * Radius;
		if (i == 0 || i == m_SphereNumY)
		{
			v2[0].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			v2++;
		}
		else
		{
			for (int nCntWidth = 0; nCntWidth < m_SphereNumX; nCntWidth++, v2++)
			{
				v2[0].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			}
		}
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

	for (int i = 0; i < m_SphereNumY + 1; i++)
	{
		m_SphereRadius = cos(D3DXToRadian((180 / (float)m_SphereNumY) * i - 90)) * Radius;
		if (i == 0 || i == m_SphereNumY)
		{
			v3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			v3++;
		}
		else
		{
			for (int nCntWidth = 0; nCntWidth < m_SphereNumX; nCntWidth++, v3++)
			{
				v3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			}
		}
	}
	m_pVB_TEX->Unlock();
}

//=======================================================================================
// スフィアインデクスバッファ設定
//=======================================================================================
void CShadowSphere::MakeSphereBuff(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "shadow.cpp => MakeSphereBuff => pDeviceがNULL！！", "エラー", MB_OK | MB_ICONASTERISK);
		return;
	}

	// インデックスバッファの作成
	HRESULT hr;
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * m_IndexNum,        // 頂点数（WORDは16Bid）
		D3DUSAGE_WRITEONLY,              // 使用用途フラグ（書き込むのみ）
		D3DFMT_INDEX16,                  // データのフォーマット（32Bid設定した時16を32に変更）
		D3DPOOL_MANAGED,                 // メモリの管理方法（お任せ）
		&m_SphereIdxBuff,              // バッファ―インターフェイスポインタのアドレス
		NULL);

	// インデックス情報格納用疑似バッファの宣言
	WORD* pIdx;

	// ロック
	m_SphereIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int i = 0; i < m_SphereNumY; i++)
	{
		// 下蓋
		if (i == 0)
		{
			for (int j = 0; j < m_SphereNumX; j++)
			{
				pIdx[0] = 0;
				pIdx++;
				pIdx[0] = (WORD)(j+1);
				pIdx++;
				if (j == m_SphereNumX - 1)
				{
					pIdx[0] = 0;
					pIdx++;
					pIdx[0] = 1;
					pIdx++;
					pIdx[0] = 1;
					pIdx++;
				}
			}
		}
		// 胴体
		else if (i < m_SphereNumY - 1)
		{
			pIdx[0] = (WORD)((i - 1) * m_SphereNumX + 1);
			pIdx++;
			for (int j = 0; j < m_SphereNumX; j++)
			{
				pIdx[0] = (WORD)((i - 1) * m_SphereNumX + 1 + j);
				pIdx++;
				pIdx[0] = (WORD)(i * m_SphereNumX + 1 + j);
				pIdx++;
				if (j == m_SphereNumX - 1)
				{
					pIdx[0] = (WORD)((i - 1) * m_SphereNumX + 1);
					pIdx++;
					pIdx[0] = (WORD)(i * m_SphereNumX + 1);
					pIdx++;
				}
			}
			pIdx[0] = (WORD)(i * m_SphereNumX + 1);
			pIdx++;
		}
		// 上蓋
		else
		{
			for (int j = 0; j < m_SphereNumX + 1; j++)
			{
				pIdx[0] = (WORD)(m_VexNum - 1 - j);
				pIdx++;
				pIdx[0] = (WORD)(m_VexNum - 1);
				pIdx++;
				if (j == m_SphereNumX)
				{
					pIdx[0] = (WORD)(m_VexNum - 2);
					pIdx++;
				}
			}
		}
	}
	// ロック解放
	m_SphereIdxBuff->Unlock();
}

//=======================================================================================
// スフィアの描画
//=======================================================================================
void CShadowSphere::DrawSphere()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "shadow.cpp => DrawSphere => pDeviceがNULL！！", "エラー", MB_OK | MB_ICONASTERISK);
		return;
	}

	// 変換行列の宣言
	D3DXMATRIX mtxScl;             // ローカルスケール
	D3DXMATRIX mtxPos;             // ローカル座標
	D3DXMATRIX mtxWorld;           // ワールド情報

	// ローカルスケールの代入
	D3DXMatrixScaling(&mtxScl,
		m_SphereScl.x,
		m_SphereScl.y,
		m_SphereScl.z);

	// ローカル座標の代入
	D3DXMatrixTranslation(&mtxPos,
		m_SpherePos.x,
		m_SpherePos.y,
		m_SpherePos.z);

	// ワールド情報処理
	D3DXMatrixIdentity(&mtxWorld);                       // ワールドの中身を初期化
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);   // ワールドスケールの代入
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);   // ワールド座標の代入
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);       // ワールド情報セット
	
	// 頂点のデクラレーションの設定
	CVertexDecl::SetTex3D(pDevice, m_pVB_POS, m_pVB_NORMAL, m_pVB_COLOR, m_pVB_TEX);

	// デバイスにインデックスバッファの設定
	pDevice->SetIndices(m_SphereIdxBuff); 

	// 描画直前にテクスチャをセット（テクスチャの設定）
	pDevice->SetTexture(0, NULL);

	// インデックスプリミティブの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,                 // プリミティブの種類
		0,
		0,
		m_VexNum,   // 頂点数
		0,
		m_PolygonNum);                       // プリミティブの数（ポリゴンの数）
}