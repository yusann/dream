//=============================================================================
// ブロック
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "scene.h"
#include "sceneModelX.h"
#include "gimmick.h"
#include "switch.h"
#include "block.h"

CGimmick::CGimmick():
	m_pSwitch(NULL),
	m_pBlock(NULL)
{
}

CGimmick::~CGimmick()
{
}

//==============================================================================
//  生成処理
//==============================================================================
CGimmick *CGimmick::Create(D3DXVECTOR3 BlockPos, D3DXVECTOR3 BlockScl)
{
	CGimmick *pSceneMD;                            // 変数宣言
	pSceneMD = new CGimmick();                       // 動的確保
	pSceneMD->Init(BlockPos, BlockScl);                            // 初期化
	return pSceneMD;                             // 値を返す
}

//==============================================================================
//  初期化処理
//==============================================================================
void CGimmick::Init(D3DXVECTOR3 BlockPos, D3DXVECTOR3 BlockScl)
{
	m_pBlock = CBlock::Create(BlockPos, BlockScl);
}

void CGimmick::SetSwitch(D3DXVECTOR3 Pos)
{
	m_pSwitch.push_back(CSwitch::Create(Pos));
}
//==============================================================================
//  終了処理
//==============================================================================
void CGimmick::Uninit( void )
{
	for (int i = 0; i < (signed)m_pSwitch.size(); i++)
	{
		m_pSwitch[i]->Uninit();
	}
	m_pSwitch.clear();
	SAFE_UNINIT(m_pBlock);
}

//==============================================================================
//  更新処理
//==============================================================================
void CGimmick::Update( void )
{
	if (m_pSwitch.empty()) return;
	for (int i = 1; i < (signed)m_pSwitch.size(); i++)
	{
		if (!m_pSwitch[i - 1]->GetisOn())
		{
			m_pSwitch[i]->SetisOn(false);
		}
	}
	if (m_pSwitch.back()->GetisOn())
	{
		m_pBlock->onSwitch();
		for (auto itr = m_pSwitch.begin(); itr != m_pSwitch.end(); ++itr) {
			(*itr)->SetisOn(false);
		}
	}
}
