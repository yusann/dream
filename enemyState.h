#ifndef _ENEMYSTATE_H_
#define _ENEMYSTATE_H_

// 前方宣言
class CEnemy;

#define ENEMY_GRAVITY				(0.08f)       // 重力

//*****************************************************************************
//   プレイヤー状態定義
//*****************************************************************************
class CEnemyState
{
public:
	virtual ~CEnemyState() {}
	virtual void Update(CEnemy* pEnemy) = 0;
};
class CEnemyStateNone : public CEnemyState
{
public:
	virtual ~CEnemyStateNone() {}
	virtual void Update(CEnemy* pEnemy) override {}
};

#endif