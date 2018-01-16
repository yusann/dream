#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

//*****************************************************************************
//   メッシュ球クラス定義
//*****************************************************************************
class CMeshSphere : public CSceneMesh
{
private:
	void MakeVex(void);     // 頂点の設定
	void MakeBuff(void);    // バッファの設定
	float m_Radius;
	int m_NumBlockX;
	int m_NumBlockY;
	bool m_Use;

public:
	CMeshSphere();                                   // デフォルトコンストラクタ
	~CMeshSphere();                                  // デストラクタ

	void Init(D3DXVECTOR3 pos, float radius, int numBlockX, int numBlockY, D3DXCOLOR color);                              // 初期化処理
	void Uninit(void);                            // 終了処理
	void Update(D3DXVECTOR3 pos, float radius);                     // 更新処理
	void Draw(void);                              // 描画処理
	void DrawDepth(void) {};                              // 描画処理

	static CMeshSphere *Create(D3DXVECTOR3 pos,
		float radius,
		int numBlockX,
		int numBlockY,
		D3DXCOLOR color = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));                  // 作成
};

#endif