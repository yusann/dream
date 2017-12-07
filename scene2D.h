#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//   2D�V�[���N���X�̒�`
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int Priority = 7);             // �f�t�H���g�R���X�g���N�^
	~CScene2D();                             // �f�X�g���N�^
	
	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

	void SetVexColor();
	void SetVexPos();
	void SetVexUV(float Percentage);

private:
	void MakeVex(void);     // ���_�̐ݒ�
	

};

#endif