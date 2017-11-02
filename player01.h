//*****************************************************************************
//   ��d��`�h�~
//*****************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
//   �N���X�̒�`
//*****************************************************************************
// �V�[���N���X
class CPlayer : public CSceneModelX
{
public:
	CPlayer();             // �f�t�H���g�R���X�g���N�^
	~CPlayer();                             // �f�X�g���N�^
	
	// �X�e�[�^�X���
	typedef struct
	{
		int LifeMax;
		int MagicMax;
		int Life;
		int Magic;
	}STATUS;

	static CPlayer *Create(VECTOR3 pos);                  // �쐬
	void Init(VECTOR3 pos);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

	void Hit(int Damage);
	STATUS GetStatus(void);

private:
	VECTOR3 m_Move;
	int m_Level;
	int m_LifeMax;
	int m_MagicMax;
	int m_Life;
	int m_Magic;
};

#endif