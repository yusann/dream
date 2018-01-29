#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//*****************************************************************************
//   �p�[�e�B�N���N���X��`
//*****************************************************************************
class CParticle : public CSceneBillboard
{
public:
	// �p�[�e�B�N���^�C�v
	typedef enum
	{
		TYPE_ENEMY_DEATH = 0,		// �G���S
		TYPE_ENEMY_DASH,			// �G�_�b�V��
		TYPE_PLAYER_HIT,			// �q�b�g
		TYPE_PLAYER_DISCOVERY,		// �q�b�g
		TYPE_RUN,					// ����
		TYPE_SWITCH_OFF,			// �X�C�b�`OFF
		TYPE_MAX					// �ő吔
	}TYPE;

	// �I�u�W�F�N�g�^�C�v
	typedef enum
	{
		OBJTYPE_NORMAL,			// ��
		OBJTYPE_STAR,			// ��
		OBJTYPE_SMOKE,			// 
		OBJTYPE_SURPRISED,		// �r�b�N���}�[�N
		OBJTYPE_MAX				// �ő吔
	}OBJTYPE;

	CParticle();             // �f�t�H���g�R���X�g���N�^
	~CParticle();            // �f�X�g���N�^

	// �p�[�e�B�N���̃Z�b�g
	static void SetParticl(TYPE type, D3DXVECTOR3 pos);

	// ����������
	void Init(TYPE type, 
			OBJTYPE objType,
			D3DXVECTOR3 pos,
			D3DXVECTOR3 size,
			int nLife,
			float fSpeed,
			float fAngle,
			D3DXVECTOR3 sizeMove,
			float fRot,
			int nTime,
			int nChangeTime);
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

private:
	// �`��^�C�v
	typedef enum
	{
		DRAW_TYPE_NORMAL = 0,		// �ʏ�
		DRAW_TYPE_BLENDADD,			// ���Z����
		DRAW_TYPE_MAX				// �ő吔
	}DRAW_TYPE;

	// �쐬
	static CParticle *Create(TYPE type,
							OBJTYPE objType,
							D3DXVECTOR3 pos,
							D3DXVECTOR3 size, 
							int nLife,
							float fSpeed = 0.0f,
							float fAngle = 0.0f,
							D3DXVECTOR3 sizeMove =D3DXVECTOR3(0.0f,0.0f,0.0f),
							float fRot = 0.0f,
							int nTime = 0,
							int nChangeTime = 0);

	// �p�[�e�B�N���^�C�v
	static void EnemyDeath(TYPE type, D3DXVECTOR3 pos);
	static void Run(TYPE type, D3DXVECTOR3 pos);

	TYPE					m_type;
	DRAW_TYPE				m_drawType;					// �`��^�C�v
	float					m_fAngle;					// ��΂��p�x
	float					m_fSpeed;					// ���x
	float					m_Rot;
	D3DXVECTOR3				m_sizeMove;					// �T�C�Y�ω���
	float					m_TexID;
	float					m_fRotMove;					// ��]��
	int						m_nLife;					// ���C�t
	int						m_nVector;					// ����
	int						m_nTime;					// �X�^�[�g�^�C��
	int						m_nChangeTime;				// �X�^�[�g�^�C��
};

#endif