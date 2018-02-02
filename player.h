#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PLAYER_STAMINA_MAX (0.98f)

// �O���錾
class CPlayerState;
class CPlayerUIManager;
#ifdef _DEBUG
class CMeshSphere;
#endif

//*****************************************************************************
//   �v���C���[�N���X��`
//*****************************************************************************
class CPlayer : public CSceneMotionPartsX
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_MOVE,
		STATE_JUMPUP,
		STATE_JUMPDOWN,
		STATE_DAMAGE,
		STATE_LOADING,
		STATE_JUMPATTACK,
		STATE_ATTACK,
		STATE_DASH,
		STATE_MAX
	}STATE;
	CPlayer();             // �f�t�H���g�R���X�g���N�^
	~CPlayer();                             // �f�X�g���N�^

	static CPlayer *Create(D3DXVECTOR3 pos);                  // �쐬
	void Init(D3DXVECTOR3 pos);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

	void Hit(D3DXVECTOR2 damageVector);
	const CCollision::SPHERE GetCollision(void) { return m_Collision; }

	D3DXVECTOR3& Position(void) { return m_Pos; }
	D3DXVECTOR3& Rotate(void) { return m_Rot; }
	float& Stamina(void) { return m_Stamina; }
	float GetJumpHeight(void) { return m_Jump; }
	bool OnBlock(void) { return m_onBlock; }
	bool InputKeyMove(D3DXVECTOR3 *Move, const float speed = 0.5f);
	bool EndMotionKey(void) { return m_LastKye; }

	float GetFloorHeight(void);
	void CollisionEnemy(void);
	void CollisionBlock(void);
	void HitEnemy(int Damage = 1);
	void DamageMove(const D3DXVECTOR2 Move);

	void ChangeState(CPlayerState* pState);

#ifdef _DEBUG
	void ImGui(void);
#endif

private:
	CPlayerState* m_pState;
	CPlayerUIManager* m_pUI;

	D3DXVECTOR3 m_Move;
	D3DXVECTOR3 m_PosOld;
	bool m_onBlock;
	int m_Level;
	int m_LifeMax;
	int m_Life;
	float m_Stamina;
	float m_FloorPosY;
	CCollision::SPHERE m_Collision;
	bool m_isDamage;
};

#endif