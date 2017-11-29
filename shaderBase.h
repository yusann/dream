#ifndef _SHADER_BASE_H_
#define _SHADER_BASE_H_

//*****************************************************************************
//   クラスの定義
//*****************************************************************************
// シーンクラス
class CShaderBase
{
public:

	CShaderBase();
	~CShaderBase();

	virtual void Create(void) =0;
	virtual void Delete(void) =0;
	virtual void Set(void) = 0;
	virtual void Clear(void) = 0;

protected:
	LPDIRECT3DPIXELSHADER9	m_Pixel;		// ピクセルシェーダー
	LPD3DXCONSTANTTABLE		m_PixelTable;	// ピクセルシェーダーのテーブル
	LPDIRECT3DVERTEXSHADER9	m_Vertex;		// 頂点シェーダー
	LPD3DXCONSTANTTABLE		m_VertexTable;	// 頂点シェーダーのテーブル

private:

};

#endif