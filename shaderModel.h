#ifndef _SHADER_MODEL_H_
#define _SHADER_MODEL_H_

//*****************************************************************************
//   シェーダモデルの定義
//*****************************************************************************
class CShaderModel : public CShaderBase
{
public:

	// デフォルトコンストラクタ
	CShaderModel();
	// デストラクタ
	~CShaderModel();

	// モデル用シェーダの初期化処理
	void Create(void) override;
	// モデル用シェーダの終了処理
	void Delete(void) override;
	// テクニックの設定
	void SetTech(void) override;
	// モデル用シェーダのセット
	void Begin(const int pass = 0) override;
	// モデル用シェーダの消去処理
	void End(void) override;

	// 頂点シェーダの情報を代入
	void SetVertexInfo(const D3DXMATRIX mtxW);
	// ピクセルシェーダーの情報を代入
	void SetPixelInfo(const D3DCOLORVALUE diffColor,const LPDIRECT3DTEXTURE9 texture, const float specularPower = 60.0f);

private:
	// テクニックへのハンドル
	D3DXHANDLE	m_hTech;

	// シェーダプログラムのグローバル変数へのハンドル
	D3DXHANDLE	m_hMtxWVP;
	D3DXHANDLE	m_hMtxW;

	D3DXHANDLE	m_hLightDirW;
	D3DXHANDLE	m_hPosEyeW;
	D3DXHANDLE	m_hDiffColor;
	D3DXHANDLE	m_hSpecularPower;

	D3DXHANDLE	m_hTexture;

};

#endif