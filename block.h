#ifndef _BLOCK_H_
#define _BLOCK_H_

// 前方宣言
#ifdef _DEBUG
class CMeshCube;
#endif
class CShadowModel;

//*****************************************************************************
//   ブロッククラス定義
//*****************************************************************************
class CBlock : public CSceneModelX
{
public:
	CBlock();					// デフォルトコンストラクタ
	CBlock(D3DXVECTOR3 pos, D3DXVECTOR3 scl);	// コンストラクタ
	~CBlock();					// デストラクタ

	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl);                  // 作成

	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理

#ifdef _DEBUG
	void ImGui(void);
#endif

private:
#ifdef _DEBUG
	CMeshCube* m_Collision;
#endif
};

#endif