#ifndef _PLAYER_H_
#define _PLAYER_H_

// �O���錾
#ifdef _DEBUG
class CMeshSphere;
#endif

//*****************************************************************************
//   �v���C���[�N���X��`
//*****************************************************************************
class CPlayer : public CSceneMotionPartsX
{
public:

	// ���
	typedef enum
	{
		MODE_NORMAL = 0,
		MODE_MOVE,
		MODE_ATTACK,
		MODE_JUMP,
		MODE_JUMPATTACK,
		MODE_MAX
	}MODE;

	// �X�e�[�^�X���
	typedef struct
	{
		int LifeMax;
		int MagicMax;
		int Life;
		int Magic;
	}STATUS;

	CPlayer();             // �f�t�H���g�R���X�g���N�^
	~CPlayer();                             // �f�X�g���N�^

	static CPlayer *Create(D3DXVECTOR3 pos);                  // �쐬
	void Init(D3DXVECTOR3 pos);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

	STATUS GetStatus(void);
	void Hit(int Damage) { m_Life -= Damage; }
	const COLLISION_SPHERE GetCollision(void) { return m_Collision; }

#ifdef _DEBUG
	void ImGui(void);
#endif

private:
	void InputKey(void);
	void ModeNormal(void);
	void ModeMove(void);
	void ModeAttack(void);
	void ModeJump(void);
	void ModeJumpAttack(void);

	void CollisionEnemy(void);
	void CollisionBlock(void);
	void HitEnemy(int Damage = 1);

	MODE m_Mode;
	D3DXVECTOR3 m_Move;
	D3DXVECTOR3 m_PosOld;
	bool m_isBlock;
	int m_Level;
	int m_LifeMax;
	int m_MagicMax;
	int m_Life;
	int m_Magic;
	float m_FloorPosY;
	COLLISION_SPHERE m_Collision;
};

#endif