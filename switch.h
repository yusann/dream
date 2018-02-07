#ifndef _SWITCH_H_
#define _SWITCH_H_

// 前方宣言
#ifdef _DEBUG
class CMeshCube;
#endif
class CShadowModel;
class CBlock;

//*****************************************************************************
//   ブロッククラス定義
//*****************************************************************************
class CSwitch : public CSceneModelX
{
public:
	CSwitch();					// デフォルトコンストラクタ
	CSwitch(D3DXVECTOR3 pos);	// コンストラクタ
	~CSwitch();					// デストラクタ

	typedef enum
	{
		STATE_NONE = 0,
		STATE_MOVE,
		STATE_MAX
	}STATE;
	static CSwitch *Create(D3DXVECTOR3 pos);                  // 作成

	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理
	void SetisOn(const bool isOn);
	bool GetisOn(void);
	D3DXVECTOR3& Position(void) { return m_Pos; }
	D3DXVECTOR3& Scale(void) { return m_Scl; }

private:
	STATE m_State;
	bool m_isOn;
	int m_Frame;
#ifdef _DEBUG
	CMeshCube* m_Collision;
#endif
};

#endif