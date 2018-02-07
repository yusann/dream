#ifndef _GIMMICK_H_
#define _GIMMICK_H_

// 前方宣言
class CSwitch;
class CBlock;

//*****************************************************************************
//   ブロッククラス定義
//*****************************************************************************
class CGimmick
{
public:
	CGimmick();					// デフォルトコンストラクタ
	~CGimmick();					// デストラクタ

	static CGimmick *Create(D3DXVECTOR3 BlockPos, D3DXVECTOR3 BlockScl);                  // 作成

	void Init(D3DXVECTOR3 BlockPos, D3DXVECTOR3 BlockScl);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void SetSwitch(D3DXVECTOR3 Pos);

private:
	std::vector<CSwitch*> m_pSwitch;
	CBlock *m_pBlock;
};

#endif