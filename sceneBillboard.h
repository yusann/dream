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

	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(DRAWTYPE type);     // 描画処理
	void SetTexID(int ID = 0);

protected:
	int m_TexWidth;
	int m_TexHeight;
	D3DXVECTOR2 m_TexPos;
	D3DXVECTOR2 m_TexScl;
	D3DXQUATERNION m_Quaternion;
	float m_Angle;
	float m_Length;

private:
	void MakeVex(void);     // 頂点の設定
};

#endif