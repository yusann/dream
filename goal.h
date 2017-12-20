#ifndef _GOAL_H_
#define _GOAL_H_

//*****************************************************************************
//   ブロッククラス定義
//*****************************************************************************
class CGoal : public CSceneModelX
{
public:
	CGoal();					// デフォルトコンストラクタ
	CGoal(D3DXVECTOR3 pos, D3DXVECTOR3 scl);	// コンストラクタ
	~CGoal();					// デストラクタ

	static CGoal *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl);                  // 作成

	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理
};

#endif