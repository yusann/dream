//*****************************************************************************
//   ��d��`�h�~
//*****************************************************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
//   �N���X�̒�`
//*****************************************************************************
// �V�[���N���X
class CLight
{
public:
	CLight();                                   // �f�t�H���g�R���X�g���N�^
	~CLight();                                  // �f�X�g���N�^
	
	void Init(void);                              // ����������
	void Uninit(void);                            // �I������
	void Update(void);
	void Set(void);

	D3DXVECTOR3 GetPos() { return m_Light.Position; }
	D3DXVECTOR3 GetDir() { return m_Light.Direction; }
	// �r���[�s��擾
	D3DXMATRIX	GetMtxView() { return m_MtxView; }
	// �v���W�F�N�V�����s��擾
	D3DXMATRIX	GetMtxProj() { return m_MtxProj; }
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }

private:
	D3DLIGHT9 m_Light;              // ���C�g

	D3DXMATRIX  m_MtxView;		// �r���[�s��
	D3DXMATRIX  m_MtxProj;		// �v���W�F�N�V�����s��
	LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif