//=============================================================================
// シェーダのベース
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "vertexDecl.h"

LPDIRECT3DVERTEXDECLARATION9 CVertexDecl::m_pVertexDecl[TYPE_MAX];

void CVertexDecl::Init(LPDIRECT3DDEVICE9 pDevice)
{
	if (pDevice == NULL) {
		return;
	}
	// 初期化
	for (int i = 0; i < TYPE_MAX; ++i) {
		m_pVertexDecl[i] = NULL;
	}

	// 3D頂点のフォーマット宣言
	D3DVERTEXELEMENT9 m_vertexElements3D[] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 1, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 2, 0,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 3, 0,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(m_vertexElements3D, &m_pVertexDecl[TYPE_3D]);

	// 2D頂点のフォーマット宣言
	D3DVERTEXELEMENT9 m_vertexElements2D[] =
	{
		//float4 posT ストリーム番号1つしか使えない
		{ 0, 0,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
		{ 0, 16,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 0, 20,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(m_vertexElements2D, &m_pVertexDecl[TYPE_2D]);

	// エラーチェック
	for (int i = 0; i < TYPE_MAX; ++i) {
		if (m_pVertexDecl[i] == NULL) {
			MessageBox(NULL, "頂点デクラレーション生成エラー！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		}
	}
}

void CVertexDecl::Uninit()
{
	for (int i = 0; i < TYPE_MAX; ++i) {
		SAFE_RELEASE(m_pVertexDecl[i]);
	}
}

void CVertexDecl::SetTex3D(LPDIRECT3DDEVICE9 pDevice,
	const LPDIRECT3DVERTEXBUFFER9 vb_pos,
	const LPDIRECT3DVERTEXBUFFER9 vb_normal,
	const LPDIRECT3DVERTEXBUFFER9 vb_color,
	const LPDIRECT3DVERTEXBUFFER9 vb_tex)
{
	// 頂点のデクラレーションの設定
	pDevice->SetVertexDeclaration(m_pVertexDecl[TYPE_3D]);

	// ストリームとして頂点バッファを設定
	pDevice->SetStreamSource(0, vb_pos, 0, sizeof(VERTEX3D_POS));
	pDevice->SetStreamSource(1, vb_normal, 0, sizeof(VERTEX3D_NORMAL));
	pDevice->SetStreamSource(2, vb_color, 0, sizeof(VERTEX3D_COLOR));
	pDevice->SetStreamSource(3, vb_tex, 0, sizeof(VERTEX3D_TEX));
}
void CVertexDecl::SetTex2D(LPDIRECT3DDEVICE9 pDevice, const LPDIRECT3DVERTEXBUFFER9 vb)
{
	// 頂点のデクラレーションの設定
	pDevice->SetVertexDeclaration(m_pVertexDecl[TYPE_2D]);

	// ストリームとして頂点バッファを設定
	pDevice->SetStreamSource(0, vb, 0, sizeof(VERTEX2D));
}