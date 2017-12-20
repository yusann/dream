#ifndef _GOAL_H_
#define _GOAL_H_

//*****************************************************************************
//   �u���b�N�N���X��`
//*****************************************************************************
class CGoal : public CSceneModelX
{
public:
	CGoal();					// �f�t�H���g�R���X�g���N�^
	CGoal(D3DXVECTOR3 pos, D3DXVECTOR3 scl);	// �R���X�g���N�^
	~CGoal();					// �f�X�g���N�^

	static CGoal *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl);                  // �쐬

	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��
};

#endif