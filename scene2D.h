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
	
	static CScene2D *Create(const LPDIRECT3DTEXTURE9 pTexture,
		const D3DXVECTOR2 Pos,
		const D3DXVECTOR2 Scl,
		const CScene::OBJTYPE ObjType,
		const int TexWidth = 1,
		const int TexHeight = 1);                  // 作成
	void SetInfo(const LPDIRECT3DTEXTURE9 pTexture,
		const D3DXVECTOR2 Pos,
		const D3DXVECTOR2 Scl,
		const CScene::OBJTYPE ObjType,
		const int TexWidth,
		const int TexHeight);
	void Init(void) override;        // 初期化処理
	void Uninit(void) override;      // 終了処理
	void Update(void) override;      // 更新処理
	void Draw(void) override;        // 描画処理
	void DrawDepth(void) override {};  // 描画処理
	void DrawStencilShadow(void) override {};  // 描画処理
	void DrawGBuffer(void) override {};  // 描画処理

	void SetVexColor(D3DXCOLOR Color);
	void SetVexPos();
	void SetVexUV();
	void SetVexGage(float val);
	void SetTexID(int nID = 0);

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;  // 頂点バッファへのポインタ
	D3DXVECTOR2 m_TexPos;
	D3DXVECTOR2 m_TexScl;

private:
	void MakeVex(void);     // 頂点の設定
	int m_TexWidth;
	int m_TexHeight;
};

#endif