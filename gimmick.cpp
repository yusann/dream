//=============================================================================
// �u���b�N
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
//  ��������
//==============================================================================
CGimmick *CGimmick::Create(D3DXVECTOR3 BlockPos, D3DXVECTOR3 BlockScl)
{
	CGimmick *pSceneMD;                            // �ϐ��錾
	pSceneMD = new CGimmick();                       // ���I�m��
	pSceneMD->Init(BlockPos, BlockScl);                            // ������
	return pSceneMD;                             // �l��Ԃ�
}

//==============================================================================
//  ����������
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
//  �I������
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
//  �X�V����
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
