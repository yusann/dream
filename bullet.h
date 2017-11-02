#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
//   �e�N���X��`
//*****************************************************************************
class CBullet : public CSceneBillboard
{
public:
	CBullet();             // �f�t�H���g�R���X�g���N�^
	~CBullet();                             // �f�X�g���N�^

	typedef enum
	{
		TYPE_PLAYER = 0,
		TYPE_ENEMY,
		TYPE_MAX
	}TYPE;

	static CBullet *Create( TYPE Type, D3DXVECTOR3 Pos, float Rot);                  // �쐬
	void Init(TYPE Type, D3DXVECTOR3 Pos, float Rot);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

private:
	TYPE m_Type;
	D3DXVECTOR3 m_Move;
	int m_Life;
};

#endif