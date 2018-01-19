#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//   2Dシーンクラスの定義
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int Priority = 7);             // デフォルトコンストラクタ
	~CScene2D();                             // デストラクタ
	
	void Init(void) override;        // 初期化処理
	void Uninit(void) override;      // 終了処理
	void Update(void) override;      // 更新処理
	void Draw(void) override;        // 描画処理
	void DrawDepth(void) override {};  // 描画処理
	void DrawStencilShadow(void) override {};  // 描画処理
	void DrawGBuffer(void) override {};  // 描画処理

	void SetVexColor();
	void SetVexPos();
	void SetVexUV(float Percentage);

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;  // 頂点バッファへのポインタ

private:
	void MakeVex(void);     // 頂点の設定
	

};

#endif