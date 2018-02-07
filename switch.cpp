//=============================================================================
// ブロック
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "scene.h"
#include "sceneModelX.h"
#include "sceneMesh.h"
#include "switch.h"
#ifdef _DEBUG
#include "meshCube.h"
#endif

CSwitch::CSwitch() :
	CSceneModelX(CScene::OBJTYPE_SWITCH)
{
#ifdef _DEBUG
	m_Collision = NULL;
#endif
}

CSwitch::CSwitch(D3DXVECTOR3 pos) :
	CSceneModelX(CScene::OBJTYPE_SWITCH)
{
	m_Pos = pos;
	m_isOn = false;
	m_Frame = 0;
}

CSwitch::~CSwitch()
{
}

//==============================================================================
//  生成処理
//==============================================================================
CSwitch *CSwitch::Create(D3DXVECTOR3 pos)
{
	CSwitch *pSceneMD;                            // 変数宣言
	pSceneMD = new CSwitch(pos);                       // 動的確保
	pSceneMD->Init();                            // 初期化
	return pSceneMD;                             // 値を返す
}

//==============================================================================
//  初期化処理
//==============================================================================
void CSwitch::Init( void )
{
	m_Model = CModelX::GetModelX(CModelX::TYPE_SWITCH);
	m_Color = D3DXCOLOR(1.0f, 0.1f, 0.2f, 1.0f);
	m_Scl = D3DXVECTOR3(8.0f,8.0f,8.0f);
	// 親の初期化
	CSceneModelX::Init();
#ifdef _DEBUG
	m_Collision = CMeshCube::Create();
#endif

	// タイプの代入
	CScene::SetObjType(CScene::OBJTYPE_SWITCH);
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

	if (m_State == STATE_MOVE)
	{
		float moveY = 0.0f;
		if (m_isOn)
		{
			moveY = m_Scl.y *0.1f;
			if (m_Frame >= 5)
			{
				m_State = STATE_NONE;
				m_Frame = 0;
				return;
			}
		}
		else
		{
			moveY = m_Scl.y *-0.05f;
			if (m_Frame >= 10)
			{
				m_State = STATE_NONE;
				m_Frame = 0;
				return;
			}
		}
		m_Pos.y -= moveY;
		m_Frame++;
	}
}

//==============================================================================
//  描画処理
//==============================================================================
void CSwitch::Draw( void )
{
	CSceneModelX::Draw();
}

void CSwitch::SetisOn(const bool isOn) {
	if (m_State == STATE_MOVE)
		return;
	if (m_isOn == isOn)
		return;
	m_isOn = isOn;
	m_State = STATE_MOVE;
}

bool CSwitch::GetisOn(void) 
{
	if (m_State == STATE_MOVE)
	{
		return false;
	}
	return m_isOn;
}