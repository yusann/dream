//=============================================================================
// ブロック
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mode.h"
#include "scene.h"
#include "sceneModelX.h"
#include "sceneMotionPartsX.h"
#include "sceneBillboard.h"
#include "sceneMesh.h"
#include "switch.h"

#include "scene2D.h"
#include "shadowModel.h"
#ifdef _DEBUG
#include "meshCube.h"
#endif

CSwitch::CSwitch() :
	CSceneModelX(CScene::OBJTYPE_BLOCK)
{
#ifdef _DEBUG
	m_Collision = NULL;
#endif
}

CSwitch::CSwitch(D3DXVECTOR3 pos, D3DXVECTOR3 scl) :
	CSceneModelX(CScene::OBJTYPE_BLOCK)
{
	m_Scl = scl;
	m_Pos = pos;
}

CSwitch::~CSwitch()
{
}

//==============================================================================
//  生成処理
//==============================================================================
CSwitch *CSwitch::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl)
{
	CSwitch *pSceneMD;                            // 変数宣言
	pSceneMD = new CSwitch(pos,scl);                       // 動的確保
	pSceneMD->Init();                            // 初期化
	return pSceneMD;                             // 値を返す
}

//==============================================================================
//  初期化処理
//==============================================================================
void CSwitch::Init( void )
{
	m_Model = CModelX::GetModelX(CModelX::TYPE_BLOCK);
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// 親の初期化
	CSceneModelX::Init();
#ifdef _DEBUG
	m_Collision = CMeshCube::Create();
#endif

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_SHADOW);
}

//==============================================================================
//  終了処理
//==============================================================================
void CSwitch::Uninit( void )
{
	CSceneModelX::Uninit();
}

//==============================================================================
//  更新処理
//==============================================================================
void CSwitch::Update( void )
{
#ifdef _DEBUG
	m_Collision->Update(m_Pos, m_Scl);
#endif
}

//==============================================================================
//  描画処理
//==============================================================================
void CSwitch::Draw( void )
{
	CSceneModelX::Draw();
}

#ifdef _DEBUG
//=======================================================================================
//   デバッグ表示
//=======================================================================================
void CSwitch::ImGui()
{
	ImGui::DragFloat3("Switch Pos", &m_Pos[0], 0.01f);
	ImGui::DragFloat3("Switch Scl", &m_Scl[0], 0.01f);
}
#endif