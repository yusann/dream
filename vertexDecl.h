#ifndef _VERTEX_DECL_H_
#define _VERTEX_DECL_H_

//*****************************************************************************
//   クラスの定義
//*****************************************************************************
// シーンクラス
class CVertexDecl
{
public:
	typedef enum
	{
		TYPE_3D = 0,
		TYPE_MAX
	}TYPE;
	// 頂点データ構造体
	struct VERTEX3D_POS {
		D3DXVECTOR3	pos;		// 位置
	};
	struct VERTEX3D_NORMAL {
		D3DXVECTOR3	normal;		// ノーマル
	};
	struct VERTEX3D_COLOR {
		D3DCOLOR color;			// 色
	};
	struct VERTEX3D_TEX {
		D3DXVECTOR2 tex;		// テクスチャ座標
	};

	static void Init(LPDIRECT3DDEVICE9 pDevice);
	static void Uninit(void);

	static LPDIRECT3DVERTEXDECLARATION9 *Get(TYPE type) {
		return &m_pVertexDecl[type];
	}

private:
	// 頂点デクラレーションへのポインタ
	static LPDIRECT3DVERTEXDECLARATION9 m_pVertexDecl[TYPE_MAX];
	
};

#endif