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
	void Begin(const int pass = 0) override;
	// モデル用シェーダの消去処理
	void End(void) override;

	// 頂点シェーダの情報を代入
	void SetVertexInfo(const D3DXMATRIX mtxW);
	// ピクセルシェーダーの情報を代入
	void SetPixelInfo(const LPDIRECT3DTEXTURE9 texture);

private:
	// シェーダプログラムのグローバル変数へのハンドル
	D3DXHANDLE	m_hMtxWVP;
	D3DXHANDLE	m_hTexture;

};

#endif