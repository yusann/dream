//=============================================================================
// プレイヤー
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "enemyStateNormal.h"
#include "enemyStateMove.h"
#include "enemyStateChase.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "enemy.h"
#include "equation.h"

CEnemyStateNormal::CEnemyStateNormal(float FloorPosY):
	m_MoveY (0.0f),
	m_Frame(0)
{
	m_FloorPosY = FloorPosY;
	m_toNextStateFrame = CEquation::Random(120, 250);
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CEnemyStateNormal::Update(CEnemy* pEnemy)
{
	// モーションの代入　更新
	pEnemy->SetMotion(CEnemy::STATE_NORMAL);

	m_Frame++;
	m_MoveY -= ENEMY_GRAVITY;
	pEnemy->Position().y += m_MoveY;

	if (pEnemy->Position().y < m_FloorPosY)
	{
		m_MoveY = 0.0f;
		pEnemy->Position().y = m_FloorPosY;
	}

	// 状態判定
	if (pEnemy->isPlayer())
	{
		pEnemy->ChangeState(new CEnemyStateChase());
		return;
	}
	if (m_Frame >= m_toNextStateFrame)
	{
		pEnemy->ChangeState(new CEnemyStateMove());
		return;
	}
}
