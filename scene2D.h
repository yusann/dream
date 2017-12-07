#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//   2Dシーンクラスの定義
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int Priority = 7);             // デフォルトコンストラクタ
	~CScene2D();                             // デストラクタ
	
	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理

	void SetVexColor();
	void SetVexPos();
	void SetVexUV(float Percentage);

private:
	void MakeVex(void);     // 頂点の設定
	

};

#endif