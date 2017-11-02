#ifndef _SKYDOME_H_
#define _SKYDOME_H_

//*****************************************************************************
//   スカイドームクラス定義
//*****************************************************************************
class CSkyDome : public CSceneMesh
{
private:
	void MakeVex(void);     // 頂点の設定
	void MakeBuff(void);    // バッファの設定
	float m_Radius;
	int m_NumBlockX;
	int m_NumBlockY;

public:
	CSkyDome();                                   // デフォルトコンストラクタ
	~CSkyDome();                                  // デストラクタ

	void Init(D3DXVECTOR3 pos, float radius, int numBlockX, int numBlockY, D3DXCOLOR color);                              // 初期化処理
	void Uninit(void);                            // 終了処理
	void Update(void);                            // 更新処理
	void Draw(void);                              // 描画処理

	static CSkyDome *Create(D3DXVECTOR3 pos,
		float radius,
		int numBlockX,
		int numBlockY,
		D3DXCOLOR color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));                  // 作成
};

#endif