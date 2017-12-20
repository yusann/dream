#ifndef _SHADER_MANGA_H_
#define _SHADER_MANGA_H_

//*****************************************************************************
//   シェーダマンガ風の定義
//*****************************************************************************
class CShaderManga : public CShaderBase
{
public:

	// デフォルトコンストラクタ
	CShaderManga();
	// デストラクタ
	~CShaderManga();

	// モデル用シェーダの初期化処理
	void Create(void) override;
	// モデル用シェーダの終了処理
	void Delete(void) override;
	// モデル用シェーダのセット
	void Begin(const int pass = 0) override;
	// モデル用シェーダの消去処理
	void End(void) override;

	// 頂点シェーダの情報を代入
	void SetVertexInfo(const D3DXMATRIX mtxW, const float contourScl = 0.2f);
	// ピクセルシェーダーの情報を代入
	void SetPixelInfo(const D3DCOLORVALUE diffColor,const LPDIRECT3DTEXTURE9 texture);

private:
	// シェーダプログラムのグローバル変数へのハンドル
	D3DXHANDLE	m_hMtxWVP;
	D3DXHANDLE	m_hMtxWIT;
	D3DXHANDLE	m_hMtxW;

	D3DXHANDLE	m_hLightDirW;
	D3DXHANDLE	m_hPosEyeW;
	D3DXHANDLE	m_hDiffColor;

	D3DXHANDLE	m_hContourScl;

	D3DXHANDLE	m_hTexture;
	D3DXHANDLE	m_hAnimeDrawTex;

};

#endif