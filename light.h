//*****************************************************************************
//   二重定義防止
//*****************************************************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
//   クラスの定義
//*****************************************************************************
// シーンクラス
class CLight
{
public:
	CLight();                                   // デフォルトコンストラクタ
	~CLight();                                  // デストラクタ
	
	void Init(void);                              // 初期化処理
	void Uninit(void);                            // 終了処理
	void Update(void);
	void Set(void);

	D3DXVECTOR3 GetPos() {
		return m_Light.Position;
	}
	D3DXVECTOR3 GetDir() {
		return m_Light.Direction;
	}

private:
	D3DLIGHT9 m_Light;              // ライト
};

#endif