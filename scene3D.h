#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
//   3Dシーンクラスの定義
//*****************************************************************************
class CScene3D : public CScene
{
public:
	CScene3D(int Priority = 3);                                   // デフォルトコンストラクタ
	~CScene3D();                                  // デストラクタ
	
	void Init(void);                              // 初期化処理
	void Uninit(void);                            // 終了処理
	void Update(void);                            // 更新処理
	void Draw(void);                              // 描画処理
	void SetTexID(int ID = 0);
	
protected:
	D3DXVECTOR3 m_Rot;
	int m_TexWidth;
	int m_TexHeight;

private:
	void MakeVex(void);     // 頂点の設定
	D3DXVECTOR2 m_TexPos;
	D3DXVECTOR2 m_TexScl;
};

#endif