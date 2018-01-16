#ifndef _MESHCUBE_H_
#define _MESHCUBE_H_

//*****************************************************************************
//   メッシュ立方体クラス定義
//*****************************************************************************
class CMeshCube : public CSceneMesh
{
public:
	CMeshCube();                                   // デフォルトコンストラクタ
	~CMeshCube();                                  // デストラクタ

	void Init(void);                              // 初期化処理
	void Uninit(void);                            // 終了処理
	void Update(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl);                            // 更新処理
	void Draw(void);                              // 描画処理
	void DrawDepth(void) {};                              // 描画処理

	static CMeshCube *Create(void);                  // 作成
	
private:
	void MakeVex(void);     // 頂点の設定
	void MakeBuff(void);    // バッファの設定

};

#endif