#ifndef _PLAYER_H_
#define _PLAYER_H_

// �O���錾
class CPlayerState;
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
		STATE_MAX
	}STATE;
	CPlayer();             // �f�t�H���g�R���X�g���N�^
	~CPlayer();                             // �f�X�g���N�^

	static CPlayer *Create(D3DXVECTOR3 pos);                  // �쐬
	void Init(D3DXVECTOR3 pos);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

	void Hit(int Damage) { m_Life -= Damage; }
	const CCollision::SPHERE GetCollision(void) { return m_Collision; }

	D3DXVECTOR3& Position(void) { return m_Pos; }
	D3DXVECTOR3& Rotate(void) { return m_Rot; }
	float GetJumpHeight(void) { return m_Jump; }
	float GetFloorHeight(void) { return m_FloorPosY; }
	bool OnBlock(void) { return m_onBlock; }
	bool InputKeyMove(D3DXVECTOR3 *Move);
	bool EndMotionKey(void) { return m_LastKye; }

	void CollisionEnemy(void);
	void CollisionBlock(void);
	void HitEnemy(int Damage = 1);

	void ChangeState(CPlayerState* pState);

#ifdef _DEBUG
	void ImGui(void);
#endif

protected:
	void ModeAttack(void);
	void ModeJumpAttack(void);

private:
	CPlayerState* m_pState;

	D3DXVECTOR3 m_Move;
	D3DXVECTOR3 m_PosOld;
	bool m_onBlock;
	int m_Level;
	int m_LifeMax;
	int m_MagicMax;
	int m_Life;
	int m_Magic;
	float m_FloorPosY;
	CCollision::SPHERE m_Collision;

};

#endif