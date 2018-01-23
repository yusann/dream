//=============================================================================
// 2Dオブジェクト
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "GBuffer.h"
#include "UIBase.h"
#include "UITitle.h"
#include "texture.h"
#include "equation.h"

//=======================================================================================
// 作成処理
//=======================================================================================
CUITitle *CUITitle::Create(){
	CUITitle *pScene2D;                            // 変数宣言
	pScene2D = new CUITitle;                       // 動的確保
	pScene2D->Init();                            // 初期化
	return pScene2D;                             // 値を返す
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CUITitle::Init()
{
	m_TexID = 0;
	MakeVex();
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CUITitle::Uninit()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pTexture);
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CUITitle::Update()
{
	ImGui::DragFloat2("UI Pos", &m_Pos[0]);
	ImGui::DragFloat2("UI Scl", &m_Scl[0]);
	ImGui::DragFloat("UI Rot", &m_Rot, 0.01f);

	ImGui::DragFloat2("UI Pos Point RT", &m_PosPoint[0][0]);
	ImGui::DragFloat2("UI Pos Point RB", &m_PosPoint[1][0]);
	ImGui::DragFloat2("UI Pos Point LT", &m_PosPoint[2][0]);
	ImGui::DragFloat2("UI Pos Point LB", &m_PosPoint[3][0]);

	ImGui::InputInt("TexID", &m_TexID);
	CEquation::Min(0.0f, m_TexID, 0.0f);
	m_pTexture = CTexture::GetTexture(m_TexID);
	SetVex();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CUITitle::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// 頂点のデクラレーションの設定
	CVertexDecl::SetTex2D(pDevice, m_pVB);

	// 描画直前にテクスチャをセット（テクスチャの設定）
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,        // プリミティブの種類
		0,                          // オフセット（頂点数）
		NUM_POLYGON);              // プリミティブの数（ポリゴンの数）
}
