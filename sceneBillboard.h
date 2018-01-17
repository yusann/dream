#ifndef _SCENEBILLBOARD_H_
#define _SCENEBILLBOARD_H_

//*****************************************************************************
//   ビルボードシーンクラスの定義
//*****************************************************************************
class CSceneBillboard : public CScene
{
public:
	typedef enum
	{
		NORMAL = 0,
		ADD,
		MAX
	}DRAWTYPE;
	CSceneBillboard(int Priority = 3);             // デフォルトコンストラクタ
	~CSceneBillboard();            // デストラクタ

	void Init(void) override;        // 初期化処理
	void Uninit(void) override;      // 終了処理
	void Update(void) override;      // 更新処理
	void Draw(void) override {};     // 描画処理
	void Draw(DRAWTYPE type);     // 描画処理
	void DrawDepth(void) override {};  // 描画処理
	void DrawStencilShadow(void) override {};  // 描画処理
	void SetTexID(int ID = 0);

protected:
	int m_TexWidth;
	int m_TexHeight;
	D3DXVECTOR2 m_TexPos;
	D3DXVECTOR2 m_TexScl;
	D3DXQUATERNION m_Quaternion;
	float m_Angle;
	float m_Length;

	LPDIRECT3DVERTEXBUFFER9	m_pVB_POS;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_NORMAL;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_COLOR;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_TEX;

private:
	void MakeVex(void);     // 頂点の設定
};

#endif