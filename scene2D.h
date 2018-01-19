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
	
	void Init(void) override;        // ����������
	void Uninit(void) override;      // �I������
	void Update(void) override;      // �X�V����
	void Draw(void) override;        // �`�揈��
	void DrawDepth(void) override {};  // �`�揈��
	void DrawStencilShadow(void) override {};  // �`�揈��
	void DrawGBuffer(void) override {};  // �`�揈��

	void SetVexColor();
	void SetVexPos();
	void SetVexUV(float Percentage);

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;  // ���_�o�b�t�@�ւ̃|�C���^

private:
	void MakeVex(void);     // ���_�̐ݒ�
	

};

#endif