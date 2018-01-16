#ifndef _SHADER_SHADOW_MAP_H_
#define _SHADER_SHADOW_MAP_H_

//*****************************************************************************
//   シェーダマンガ風の定義
//*****************************************************************************
class CShaderShadowMap : public CShaderBase
{
public:

	// デフォルトコンストラクタ
	CShaderShadowMap();
	// デストラクタ
	~CShaderShadowMap();

	// モデル用シェーダの初期化処理
	void Create(void) override;
	// モデル用シェーダの終了処理
	void Delete(void) override;
	// モデル用シェーダのセット
	void Begin(const int pass = 0) override;
	// モデル用シェーダの消去処理
	void End(void) override;

	// 頂点シェーダの情報を代入
	void SetVertexInfo(const D3DXMATRIX mtxW);

private:
	// シェーダプログラムのグローバル変数へのハンドル
	D3DXHANDLE	m_hMtxLightWVP;
	D3DXHANDLE	m_hMtxLightWV;
	D3DXHANDLE	m_hFar;

};

#endif