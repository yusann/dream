#ifndef _VERTEX_DECL_H_
#define _VERTEX_DECL_H_

//*****************************************************************************
//   クラスの定義
//*****************************************************************************
// シーンクラス
class CVertexDecl
{
public:
	// デクラレーションの種類
	typedef enum
	{
		TYPE_3D = 0,
		TYPE_2D,
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

	// 2D
	struct VERTEX2D {
		D3DXVECTOR4	pos;		// 位置
		D3DCOLOR color;			// 色
		D3DXVECTOR2 tex;		// テクスチャ座標
	};

	// 初期化
	static void Init(LPDIRECT3DDEVICE9 pDevice);
	// 終了処理
	static void Uninit(void);

	// デクラレーションのセット
	// 3D
	static void SetTex3D(LPDIRECT3DDEVICE9 pDevice, 
		const LPDIRECT3DVERTEXBUFFER9 vb_pos,
		const LPDIRECT3DVERTEXBUFFER9 vb_normal,
		const LPDIRECT3DVERTEXBUFFER9 vb_color,
		const LPDIRECT3DVERTEXBUFFER9 vb_tex);
	// 2D
	static void SetTex2D(LPDIRECT3DDEVICE9 pDevice, const LPDIRECT3DVERTEXBUFFER9 vb);

private:
	// 頂点デクラレーションへのポインタ
	static LPDIRECT3DVERTEXDECLARATION9 m_pVertexDecl[TYPE_MAX];
	
};

#endif