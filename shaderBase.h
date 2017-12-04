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
	void CreateVertex(const char* hlslFile);
	void CreatePixel(const char* hlslFile);

	LPDIRECT3DVERTEXSHADER9	m_pVertex;		// 頂点シェーダー
	LPD3DXCONSTANTTABLE		m_pVertexTable;	// 頂点シェーダーのテーブル
	LPDIRECT3DPIXELSHADER9	m_pPixel;		// ピクセルシェーダー
	LPD3DXCONSTANTTABLE		m_pPixelTable;	// ピクセルシェーダーのテーブル

};

#endif