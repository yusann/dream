#ifndef _SHADOW_H_
#define _SHADOW_H_

//*****************************************************************************
//   丸影クラス定義
//*****************************************************************************
class CShadow : public CScene
{
public:
	CShadow(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl);             // デフォルトコンストラクタ
	~CShadow();                             // デストラクタ

	static CShadow* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl);
	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);      // 更新処理
	void Draw(void);        // 描画処理
	void SetPos(D3DXVECTOR3 Pos) { m_Pos = Pos; }
	void SetScl(float Scl) { m_Scl.z = Scl;}

private:
	void MakeVex(void);     // 頂点の設定
};

#endif