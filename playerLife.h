#ifndef _PLAYER_LIFE_H_
#define _PLAYER_LIFE_H_

//*****************************************************************************
//   2D�I�u�W�F�N�g�N���X��`
//*****************************************************************************
class CPlayerLife : public CScene2D
{
public:
	CPlayerLife();             // �f�t�H���g�R���X�g���N�^
	~CPlayerLife();                             // �f�X�g���N�^

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_IN,
		TYPE_OUT,
		TYPE_MAX
	}TYPE;

	static CPlayerLife *Create(	const LPDIRECT3DTEXTURE9 pTexture,
								const D3DXVECTOR2 Pos,
								const D3DXVECTOR2 Scl,
								const int Num);                  // �쐬
	void Init(	const LPDIRECT3DTEXTURE9 pTexture,
				const D3DXVECTOR2 Pos,
				const D3DXVECTOR2 Scl,
				const int Num);
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��
	void ChangeNum(int NextNum);

private:
	CScene2D *m_pLifeIcon;
	TYPE m_Type;
	int m_Num;
	D3DXVECTOR3 m_PosOld;
};

#endif