//=============================================================================
// 影
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "shadowModel.h"
#include "light.h"

int CShadowModel::m_MaxID = 0;

CShadowModel::CShadowModel() : CScene2D(CScene::OBJTYPE_SHADOW)
{
}

CShadowModel::CShadowModel(const LPD3DXMESH pMesh) :
	CScene2D(CScene::OBJTYPE_SHADOW),
	m_pMesh(pMesh)
{
	m_Shadow.iNumVertex = 0;
	m_Shadow.pVertex = NULL;
	D3DXMatrixIdentity(&m_Matrix);                       // ワールドの中身を初期化
}

CShadowModel::~CShadowModel()
{
	if (m_Shadow.pVertex != NULL)
	{
		delete[] m_Shadow.pVertex;
		m_Shadow.pVertex = NULL;
	}
}

//==============================================================================
//  生成処理
//==============================================================================
CShadowModel *CShadowModel::Create(const LPD3DXMESH pMesh)
{
	CShadowModel *pSceneMD;                            // 変数宣言
	pSceneMD = new CShadowModel(pMesh);
	pSceneMD->Init();                            // 初期化
	return pSceneMD;                             // 値を返す
}

//==============================================================================
//  初期化処理
//==============================================================================
void CShadowModel::Init( void )
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_Color = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	m_pTexture = NULL;
	m_MaxID++;

	CScene2D::Init();

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_SHADOW);
}

//==============================================================================
//  終了処理
//==============================================================================
void CShadowModel::Uninit( void )
{
	if (m_Shadow.pVertex != NULL)
	{
		delete[] m_Shadow.pVertex;
		m_Shadow.pVertex = NULL;
	}
	m_MaxID--;
	CScene2D::Uninit();
}

//==============================================================================
//  更新処理
//==============================================================================
void CShadowModel::Update( void )
{
	D3DXVECTOR3	light;
	D3DXMATRIX	shadow;
	D3DXVECTOR3 lightPos = CManager::GetLight()->GetPos();
	D3DXMatrixInverse(&shadow, NULL, &m_Matrix);
	D3DXVec3TransformCoord(&light, &lightPos, &shadow);
	BuildShadowVolume(m_pMesh, light);
}

//==============================================================================
//  描画処理
//==============================================================================
void CShadowModel::Draw( void )
{
	/*
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// ステンシルの設定
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);			// ステンシル有効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// Zバッファ書き込まない
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);			// カラー書き込まない
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0x000000ff);		// ステンシルマスク

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);	// 比較関数（必ず合格）
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);				// 参照値
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Zバッファで引っかかった時（何もしない）
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// 両方ダメだった時（何もしない）

	// シャドウボリュームの表をステンシルに描画
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);		// 両方に通った時（+1）
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	pDevice->SetFVF(D3DFVF_XYZ);
	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_Shadow.iNumVertex / 3,
		*m_Shadow.pVertex, sizeof(D3DXVECTOR3));

	// シャドウボリュームの裏をステンシルに描画
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);		// 両方に通った時（-1）
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	pDevice->SetFVF(D3DFVF_XYZ);
	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_Shadow.iNumVertex / 3,
		*m_Shadow.pVertex, sizeof(D3DXVECTOR3));

	// 最後描画するオブジェのチェック
	static int ID = 0;
	ID++;
	if (ID == m_MaxID)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);			// カラー書き込む可能
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);				// 参照値
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);	// 比較関数（以下なら）

		CScene2D::Draw();

		ID = 0;

		// ステンシルをクリア
		pDevice->Clear(0, NULL,
			D3DCLEAR_STENCIL,								// ステンシル
			D3DCOLOR_RGBA(0, 0, 0, 0),				// 初期化色
			1.0f,											// 0~1（0は手前、1は遠い）
			0);

	}
	// 描画ステータスの復帰
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	*/
}

//-----------------------------------------------------------------------------
// メッシュと光源へのベクトルよりシャドウボリュームを生成
//-----------------------------------------------------------------------------
HRESULT CShadowModel::BuildShadowVolume( LPD3DXMESH pMesh, D3DXVECTOR3 vLight)
{
	BYTE*	pVertex;
	WORD*	pIndex;

	// 頂点バッファ、インデックスバッファの取得
	pMesh->LockVertexBuffer(0, (LPVOID*)&pVertex);
	pMesh->LockIndexBuffer(0, (LPVOID*)&pIndex);
	DWORD	dwNumFace = pMesh->GetNumFaces();
	DWORD	dwStride = pMesh->GetNumBytesPerVertex();

	// ワーク用エッジリスト確保
	WORD*	pEdge = new WORD[dwNumFace * 6];
	if (pEdge == NULL) {
		pMesh->UnlockIndexBuffer();
		pMesh->UnlockVertexBuffer();
		return E_OUTOFMEMORY;
	}

	DWORD	dwNumEdge = 0;
	DWORD	i;

	// 光源を向いている面を検索
	for (i = 0; i < dwNumFace; i++) {
		WORD	wFace0 = pIndex[i * 3 + 0];
		WORD	wFace1 = pIndex[i * 3 + 1];
		WORD	wFace2 = pIndex[i * 3 + 2];
		D3DXVECTOR3&	v0 = *(D3DXVECTOR3*)&pVertex[wFace0 * dwStride];
		D3DXVECTOR3&	v1 = *(D3DXVECTOR3*)&pVertex[wFace1 * dwStride];
		D3DXVECTOR3&	v2 = *(D3DXVECTOR3*)&pVertex[wFace2 * dwStride];
		// 光源を向いている面か?
		D3DXVECTOR3	vCross1(v1 - v0);
		D3DXVECTOR3	vCross2(v2 - v0);
		D3DXVECTOR3	vNormal;
		D3DXVec3Cross(&vNormal, &vCross1, &vCross2);
		if (D3DXVec3Dot(&vNormal, &vLight) <= 0.0f) {
			// エッジリストに3辺を追加
			AddEdge(pEdge, &dwNumEdge, wFace0, wFace1);
			AddEdge(pEdge, &dwNumEdge, wFace1, wFace2);
			AddEdge(pEdge, &dwNumEdge, wFace2, wFace0);
		}
	}

	// シャドウボリュームの側面を追加
	if (m_Shadow.pVertex != NULL)
	{
		delete[] m_Shadow.pVertex;
		m_Shadow.pVertex = NULL;
	}
	m_Shadow.pVertex = new D3DXVECTOR3[dwNumEdge * 6];
	m_Shadow.iNumVertex = 0;
	for (i = 0; i < dwNumEdge; i++) {
		D3DXVECTOR3&	v1 = *(D3DXVECTOR3*)&pVertex[pEdge[i * 2 + 0] * dwStride];
		D3DXVECTOR3&	v2 = *(D3DXVECTOR3*)&pVertex[pEdge[i * 2 + 1] * dwStride];
		D3DXVECTOR3		v3 = v1 - vLight;
		D3DXVECTOR3		v4 = v2 - vLight;

		// 矩形の追加
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v1;
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v2;
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v3;
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v2;
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v4;
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v3;
	}

	// ワーク用エッジリスト解放
	delete[] pEdge;

	// 頂点バッファ、インデックスバッファの解放
	pMesh->UnlockIndexBuffer();
	pMesh->UnlockVertexBuffer();

	return S_OK;
}

//-----------------------------------------------------------------------------
// エッジリストへの追加
//-----------------------------------------------------------------------------
void CShadowModel::AddEdge(WORD* pEdge, DWORD* pdwNumEdge, WORD v0, WORD v1)
{
	// 三角形間の共有エッジの削除（2度目の登録時）
	for (DWORD i = 0; i < *pdwNumEdge; ++i) {
		if ((pEdge[i * 2 + 0] == v0 && pEdge[i * 2 + 1] == v1) ||
			(pEdge[i * 2 + 0] == v1 && pEdge[i * 2 + 1] == v0)) {
			// 末尾のエッジで上書きして消去
			if (*pdwNumEdge > 1) {
				pEdge[i * 2 + 0] = pEdge[(*pdwNumEdge - 1) * 2 + 0];
				pEdge[i * 2 + 1] = pEdge[(*pdwNumEdge - 1) * 2 + 1];
			}
			--*pdwNumEdge;
			return;
		}
	}
	// エッジリストへ追加
	pEdge[*pdwNumEdge * 2 + 0] = v0;
	pEdge[*pdwNumEdge * 2 + 1] = v1;
	++*pdwNumEdge;
}