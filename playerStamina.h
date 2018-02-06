#ifndef _PLAYER_STAMINA_H_
#define _PLAYER_STAMINA_H_

//*****************************************************************************
//   2D�I�u�W�F�N�g�N���X��`
//*****************************************************************************
class CPlayerStamina : public CScene2D
{
public:
	CPlayerStamina();             // �f�t�H���g�R���X�g���N�^
	~CPlayerStamina();                             // �f�X�g���N�^

	static CPlayerStamina *Create(	const LPDIRECT3DTEXTURE9 pTexture,
								const D3DXVECTOR2 Pos,
								const D3DXVECTOR2 Scl);                  // �쐬
	void Init(	const LPDIRECT3DTEXTURE9 pTexture,
				const D3DXVECTOR2 Pos,
				const D3DXVECTOR2 Scl);
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��
	void SetValue(float Value) { m_Value = Value; }

private:
	CScene2D *m_pBG;
	float m_Value;
	bool  m_isDraw;
};

#endif