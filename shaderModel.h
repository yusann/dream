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
	// モデル用シェーダのセット
	void Set(void) override;
	// モデル用シェーダの消去処理
	void Clear(void) override;

	// 頂点シェーダの情報を代入
	void SetVertexInfo(const D3DXMATRIX mtxW);
	// ピクセルシェーダーの情報を代入
	void SetPixelInfo(const D3DXVECTOR3 modelPos, const D3DCOLORVALUE diffColor, const float specularPower = 60.0f);
	// テクスチャIDの取得
	UINT GetSamplerIndex(void);
};

#endif