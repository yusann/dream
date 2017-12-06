#ifndef _SHADOW_H_
#define _SHADOW_H_

//*****************************************************************************
//   �e�N���X��`
//*****************************************************************************
class CShadow : public CScene2D
{
public:
	CShadow();					// �f�t�H���g�R���X�g���N�^
	~CShadow();					// �f�X�g���N�^

	static CShadow* Clear();

	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(void);
	void Draw(void);        // �`�揈��
private:
	static CShadow* m_pShadow;

};

#endif