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
	CBlock(D3DXVECTOR3 pos, D3DXVECTOR3 scl);	// コンストラクタ
	~CBlock();					// デストラクタ

	typedef enum
	{
		STATE_NONE = 0,
		STATE_SWITCH,
		STATE_MAX
	}STATE;
	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl);                  // 作成

	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理

	void onSwitch(void) { m_State = STATE_SWITCH; }
#ifdef _DEBUG
	void ImGui(void);
#endif

private:
	CBlock() : CSceneModelX(CScene::OBJTYPE_BLOCK) {};					// デフォルトコンストラクタ
	STATE m_State;
	int m_Frame;
#ifdef _DEBUG
	CMeshCube* m_Collision;
#endif
};

#endif