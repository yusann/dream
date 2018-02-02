#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//*****************************************************************************
//   2D�I�u�W�F�N�g�N���X��`
//*****************************************************************************
class CObject2D : public CScene2D
{
public:
	CObject2D();             // �f�t�H���g�R���X�g���N�^
	~CObject2D();                             // �f�X�g���N�^

	typedef enum
	{
		TYPE_BG_TITLE = 0,
		TYPE_BG_TITLE_SIBA,
		TYPE_BG_TUTORIAL,
		TYPE_BG_RESULTLOSE,
		TYPE_BG_RESULTWIN,
		TYPE_UI_PUSH,
		TYPE_UI_NUM,
		TYPE_MAX
	}TYPE;

	static CObject2D *Create(TYPE Type);                  // �쐬
	void Init(TYPE Type);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

private:
	TYPE m_Type;
	D3DXVECTOR3 m_SclOld;
};

#endif