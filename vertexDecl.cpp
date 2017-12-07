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
	/*
	// 頂点のフォーマット宣言
	D3DVERTEXELEMENT9 m_vertexElements2D[] =
	{
		//float4 posT ストリーム番号1つしか使えない
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 1, 0,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		{ 2, 0,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(m_vertexElements2D, &m_pVertexDecl[TYPE_2D_NOCOLOR]);
	*/
	// 頂点のフォーマット宣言
	D3DVERTEXELEMENT9 m_vertexElements3D[] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 1, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 2, 0,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 3, 0,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(m_vertexElements3D, &m_pVertexDecl[TYPE_3D]);

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