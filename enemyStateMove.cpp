//=============================================================================
// プレイヤー
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "enemyStateMove.h"
#include "enemyStateNormal.h"
#include "enemyStateChase.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "enemy.h"
#include "equation.h"

#define ENEMY_MOVE_SPEED (0.2f)

CEnemyStateMove::CEnemyStateMove():
	m_Move (D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_FloorPosY(0.0f),
	m_Frame(0)
{
	m_RotY = CEquation::Random(-314, 314)* 0.01f;
	m_toNextStateFrame = CEquation::Random(240, 400);
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CEnemyStateMove::Update(CEnemy* pEnemy)
{
	// モーションの代入　更新
	pEnemy->SetMotion(CEnemy::STATE_MOVE);

	m_Frame++;
	float rotY = pEnemy->GetRot().y;
	m_Move.y -= ENEMY_GRAVITY;
	m_Move.x = (float)cos(-rotY + D3DXToRadian(-90))*ENEMY_MOVE_SPEED;
	m_Move.z = (float)sin(-rotY + D3DXToRadian(-90))*ENEMY_MOVE_SPEED;
	pEnemy->Position() += m_Move;

	m_FloorPosY = pEnemy->GetFloorHeight();
	if (pEnemy->Position().y < m_FloorPosY)
	{
		m_Move.y = 0.0f;
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
		pEnemy->ChangeState(new CEnemyStateNormal(m_FloorPosY));
		return;
	}
}
