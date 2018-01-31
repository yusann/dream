//=============================================================================
// �v���C���[
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "enemyStateChase.h"
#include "enemyStateNormal.h"

#include "mode.h"
#include "modeGame.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "enemy.h"
#include "player.h"
#include "equation.h"

#define ENEMY_CHASE_SPEED (0.4f)

CEnemyStateChase::CEnemyStateChase():
	m_Move (D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_FloorPosY(0.0f),
	m_Frame(0)
{
	m_RotY = CEquation::Random(-314, 314)* 0.01f;
	m_toNextStateFrame = CEquation::Random(240, 400);
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CEnemyStateChase::Update(CEnemy* pEnemy)
{
	// ���[�V�����̑���@�X�V
	pEnemy->SetMotion(CEnemy::STATE_CHASE);

	m_Frame++;

	// �v���C���[�̓����蔻��擾
	CPlayer* pPlayer = CModeGame::GetPlayer();
	if (pPlayer == NULL) { return; }
	CCollision::SPHERE collision = pPlayer->GetCollision();

	// �����̍��W�̎擾
	D3DXVECTOR3 my_pos = pEnemy->Position();

	// �v���C���[�Ƃ̌���
	D3DXVECTOR3 Vector;
	Vector.x = collision.Pos.x - my_pos.x;
	Vector.z = collision.Pos.z - my_pos.z;
	Vector.y = 0.0f;

	// �v���C���[�Ƃ̊p�x
	float rotY = atan2(Vector.x, Vector.z) + 3.14f;
	if ( pEnemy->Rotate().y - rotY >  D3DX_PI) {  pEnemy->Rotate().y -= D3DX_PI * 2; }
	if ( pEnemy->Rotate().y - rotY < -D3DX_PI) {  pEnemy->Rotate().y += D3DX_PI * 2; }

	// ���񂾂����
	pEnemy->Rotate().y += (rotY - pEnemy->Rotate().y) * 0.1f;

	// �ړ�
	m_Move.y -= ENEMY_GRAVITY;
	m_Move.x = (float)cos(- pEnemy->Rotate().y + D3DXToRadian(-90))*ENEMY_CHASE_SPEED;
	m_Move.z = (float)sin(- pEnemy->Rotate().y + D3DXToRadian(-90))*ENEMY_CHASE_SPEED;
	pEnemy->Position() += m_Move;

	m_FloorPosY = pEnemy->GetFloorHeight();
	if (pEnemy->Position().y < m_FloorPosY)
	{
		m_Move.y = 0.0f;
		pEnemy->Position().y = m_FloorPosY;
	}
	// ��Ԕ���
	if (!pEnemy->isPlayer())
	{
		pEnemy->ChangeState(new CEnemyStateNormal(m_FloorPosY));
		return;
	}
}
