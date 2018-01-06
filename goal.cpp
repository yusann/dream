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
#include "goal.h"

CGoal::CGoal() :
	CSceneModelX(CScene::OBJTYPE_BLOCK)
{
}

CGoal::CGoal(D3DXVECTOR3 pos, D3DXVECTOR3 scl) :
	CSceneModelX(CScene::OBJTYPE_BLOCK)
{
	m_Scl = scl;
	m_Pos = pos;
}

CGoal::~CGoal()
{
}

//==============================================================================
//  生成処理
//==============================================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl)
{
	CGoal *pSceneMD;                            // 変数宣言
	pSceneMD = new CGoal(pos,scl);                       // 動的確保
	pSceneMD->Init();                            // 初期化
	return pSceneMD;                             // 値を返す
}

//==============================================================================
//  初期化処理
//==============================================================================
void CGoal::Init( void )
{
	m_Model = CModelX::GetModelX(CModelX::TYPE_GOAL);
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// 親の初期化
	CSceneModelX::Init();


	// 変換行列の宣言
	D3DXMATRIX mtxRot;             // ローカル回転
	D3DXMATRIX mtxScl;             // ローカルスケール
	D3DXMATRIX mtxPos;             // ローカル座標
	D3DXMATRIX mtxWorld;           // ワールド情報

								   // ローカル回転の代入
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_Rot.y,
		m_Rot.x,
		m_Rot.z);

	// ローカルスケールの代入
	D3DXMatrixScaling(&mtxScl,
		m_Scl.x,
		m_Scl.y,
		m_Scl.z);

	// ローカル座標の代入
	D3DXMatrixTranslation(&mtxPos,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z);

	// ワールド情報処理
	D3DXMatrixIdentity(&mtxWorld);                       // ワールドの中身を初期化
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);   // ワールド回転の代入
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);   // ワールドスケールの代入
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);   // ワールド座標の代入

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_BLOCK);
}

//==============================================================================
//  終了処理
//==============================================================================
void CGoal::Uninit( void )
{
	CSceneModelX::Uninit();
}

//==============================================================================
//  更新処理
//==============================================================================
void CGoal::Update( void )
{
}

//==============================================================================
//  描画処理
//==============================================================================
void CGoal::Draw( void )
{
	CSceneModelX::Draw();
}