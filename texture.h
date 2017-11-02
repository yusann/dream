#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
//   �e�N�X�`�����\�[�X�N���X�̒�`
//*****************************************************************************
class CTexture
{
public:

	typedef enum
	{
		TEXTYPE_WHITE = 0,
		TEXTYPE_FIELD,
		TEXTYPE_PLAYER,
		TEXTYPE_BULLET,

		TEXTYPE_SKY000,
		TEXTYPE_TITLEBG,
		TEXTYPE_TITLELOGO,
		TEXTYPE_TUTORIALBG,
		TEXTYPE_RESULTWINBG,
		TEXTYPE_RESULTLOSTBG,
		TEXTYPE_PUSHSTART,

		TEXTYPE_PARTICLE00,
		TEXTYPE_PARTICLE01,
		TEXTYPE_PARTICLE02,

		TEXTYPE_UI_LIFE,
		TEXTYPE_UI_MAGIC,
		TEXTYPE_UI_GAGEBG,
		TEXTYPE_UI_NUM,

		TEXTYPE_MAX
	}TEXTYPE;
	CTexture();                                   // �f�t�H���g�R���X�g���N�^
	~CTexture();                                  // �f�X�g���N�^
	
	static void Init(void);                              // ����������
	static void Uninit(void);                            // �I������

	static LPDIRECT3DTEXTURE9 GetTexture(int nNo);		// �e�N�X�`���̎擾

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEXTYPE_MAX];		// �e�N�X�`��
	static char m_TexName[TEXTYPE_MAX][128];				// �e�N�X�`���p�X
};

#endif