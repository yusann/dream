#ifndef _SKYDOME_H_
#define _SKYDOME_H_

//*****************************************************************************
//   �X�J�C�h�[���N���X��`
//*****************************************************************************
class CSkyDome : public CSceneMesh
{
private:
	void MakeVex(void);     // ���_�̐ݒ�
	void MakeBuff(void);    // �o�b�t�@�̐ݒ�
	float m_Radius;
	int m_NumBlockX;
	int m_NumBlockY;

public:
	CSkyDome();                                   // �f�t�H���g�R���X�g���N�^
	~CSkyDome();                                  // �f�X�g���N�^

	void Init(D3DXVECTOR3 pos, float radius, int numBlockX, int numBlockY, D3DXCOLOR color);                              // ����������
	void Uninit(void);                            // �I������
	void Update(void);                            // �X�V����
	void Draw(void);                              // �`�揈��

	static CSkyDome *Create(D3DXVECTOR3 pos,
		float radius,
		int numBlockX,
		int numBlockY,
		D3DXCOLOR color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));                  // �쐬
};

#endif