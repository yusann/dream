#ifndef _SHADOW_MODEL_H_
#define _SHADOW_MODEL_H_

//*****************************************************************************
//   �e�N���X��`
//*****************************************************************************
class CShadowModel : public CScene2D
{
public:
	CShadowModel();					// �f�t�H���g�R���X�g���N�^
	~CShadowModel();					// �f�X�g���N�^

	static CShadowModel *Create();                  // �쐬

	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(void);
	void Draw(void);        // �`�揈��
};

#endif