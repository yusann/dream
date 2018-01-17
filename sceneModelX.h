#ifndef _SCENEMODELX_H_
#define _SCENEMODELX_H_

#include "modelX.h"

//*****************************************************************************
//   Xモデルクラスの定義
//*****************************************************************************
class CSceneModelX : public CScene
{
public:
	CSceneModelX(int Priority = 3);                                   // デフォルトコンストラクタ
	~CSceneModelX();                                  // デストラクタ
	
	void Init(void) override;                              // 初期化処理
	void Uninit(void) override;                            // 終了処理
	void Update(void) override;                            // 更新処理
	void Draw(void) override;                              // 描画処理
	void DrawDepth(void) override;  // 描画処理
	void DrawStencilShadow(void) override;  // 描画処理
	D3DXVECTOR3 GetRot(void) { return m_Rot; }

protected:
	D3DXVECTOR3 m_Rot;      // 回転
	CModelX::MODELX			m_Model;
private:

	LPDIRECT3DVERTEXBUFFER9 m_pCountourVB;
	LPDIRECT3DTEXTURE9 m_pContourTex;
};

#endif