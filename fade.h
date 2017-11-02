#ifndef _FADE_H_
#define _FADE_H_

//   �O���錾
class CMode;

//*****************************************************************************
//   �t�F�[�h�N���X��`
//*****************************************************************************
class CFade : public CScene2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX,
	}FADE;

	CFade();             // �f�t�H���g�R���X�g���N�^
	~CFade();                             // �f�X�g���N�^
	
	void Init(D3DXCOLOR color);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

	static void SetFade(CMode *modeNext, D3DXCOLOR color = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f), FADE fade = FADE_OUT);  // �ǉ��ŃJ���[�w��A�e�N�X�`���w��A�t�F�[�h�X�s�[�g
	static FADE GetFade(void);                      // �t�F�[�h��Ԏ擾

	static CFade *Create(D3DXCOLOR color);                  // �쐬
private:
	static FADE m_fade;
	static CMode *m_pModeNext;
};

#endif