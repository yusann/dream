#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
//   3Dシーンクラスの定義
//*****************************************************************************
class CScene3D : public CScene
{
public:
	CScene3D(int Priority = 3);                                   // デフォルトコンストラクタ
	~CScene3D();                                  // デストラクタ
	
	void Init(void) override;                              // 初期化処理
	void Uninit(void) override;                            // 終了処理
	void Update(void) override;                            // 更新処理
	void Draw(void) override;                              // 描画処理
	void DrawDepth(void) override {};  // 描画処理
	void DrawStencilShadow(void) override {};  // 描画処理
	void DrawGBuffer(void) override {};  // 描画処理
	void SetTexID(int ID = 0);
	
protected:
	D3DXVECTOR3 m_Rot;
	int m_TexWidth;
	int m_TexHeight;

	LPDIRECT3DVERTEXBUFFER9	m_pVB_POS;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_NORMAL;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_COLOR;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_TEX;

private:
	void MakeVex(void);     // 頂点の設定
	D3DXVECTOR2 m_TexPos;
	D3DXVECTOR2 m_TexScl;
};

#endif