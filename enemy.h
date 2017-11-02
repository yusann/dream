#ifndef _ENEMY_H_
#define _ENEMY_H_

// �O���錾
class CShadow;
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
		MODE_NORMAL = 0,
		MODE_MOVE,
		MODE_ATTACK,
		MODE_MAX
	}MODE;

	CEnemy();             // �f�t�H���g�R���X�g���N�^
	~CEnemy();                             // �f�X�g���N�^
	
	void Init(D3DXVECTOR3 pos);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

	static CEnemy *Create(D3DXVECTOR3 pos);                  // �쐬
	D3DXVECTOR3 GetCollisionPos(void) { return m_CollisionPos; }
	float GetCollisionScl(void) { return m_CollisionScl; }
	bool Hit(int damage = 1);
#ifdef _DEBUG
	void ImGui(void);
#endif

private:
	void ModeNormal(void);
	void ModeMove(void);
	void ModeAttack(void);

	void CollisionBlock(void);
	bool isPlayer(void);

	MODE m_Mode;
	D3DXVECTOR3 m_Move;
	int m_life;
	int m_CheckMode;
	int m_CntFrameNormal;
	int m_CntFrameMove;
	int m_CntFrameAttack;

	CShadow* m_Shadow;

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