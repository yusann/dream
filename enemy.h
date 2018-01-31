#ifndef _ENEMY_H_
#define _ENEMY_H_

// �O���錾
class CEnemyState;
#ifdef _DEBUG
class CMeshSphere;
#endif

//*****************************************************************************
//   �G�N���X�̒�`
//*****************************************************************************
class CEnemy : public CSceneMotionPartsX
{
public:
	// ���
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_MOVE,
		STATE_CHASE,
		STATE_MAX
	}STATE;

	CEnemy();             // �f�t�H���g�R���X�g���N�^
	~CEnemy();                             // �f�X�g���N�^

	static CEnemy *Create(D3DXVECTOR3 pos);                  // �쐬
	void Init(D3DXVECTOR3 pos);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

	D3DXVECTOR3 GetCollisionPos(void) { return m_CollisionPos; }
	float GetCollisionScl(void) { return m_CollisionScl; }
	bool Hit(int damage = 1);

	void ChangeState(CEnemyState* pState);
	D3DXVECTOR3& Position(void) { return m_Pos; }
	D3DXVECTOR3& Rotate(void) { return m_Rot; }
	float GetFloorHeight(void);
	bool isPlayer(void);
#ifdef _DEBUG
	void ImGui(void);
#endif

private:
	void ModeAttack(void);

	void CollisionBlock(void);

	CEnemyState* m_pState;

	D3DXVECTOR3 m_Move;
	int m_life;
	float m_FloorPosY;

	D3DXVECTOR3 m_CollisionPos;
	float m_CollisionScl;
	D3DXVECTOR3 m_DetectionPos;
	float m_DetectionScl;

#ifdef _DEBUG
	CMeshSphere* m_CollisionDebug;
	CMeshSphere* m_DetectionDebug;
#endif
};

#endif