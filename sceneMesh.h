#ifndef _SCENEMESH_H_
#define _SCENEMESH_H_

//*****************************************************************************
//   メッシュシーンクラスの定義
//*****************************************************************************
class CSceneMesh : public CScene
{
public:
	CSceneMesh(int Priority = 1);                                   // デフォルトコンストラクタ
	~CSceneMesh();                                  // デストラクタ

	void Init(void);                              // 初期化処理
	void Uninit(void);                            // 終了処理
	void Update(void);                            // 更新処理
	void Draw(void);                              // 描画処理
	
protected:
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;     // インデックスバッファ
	D3DXVECTOR3 m_Rot;
	int   m_PolygonNum;
	int   m_VexNum;

};

#endif