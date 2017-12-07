#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
//   3D�V�[���N���X�̒�`
//*****************************************************************************
class CScene3D : public CScene
{
public:
	CScene3D(int Priority = 3);                                   // �f�t�H���g�R���X�g���N�^
	~CScene3D();                                  // �f�X�g���N�^
	
	void Init(void);                              // ����������
	void Uninit(void);                            // �I������
	void Update(void);                            // �X�V����
	void Draw(void);                              // �`�揈��
	void SetTexID(int ID = 0);
	
protected:
	D3DXVECTOR3 m_Rot;
	int m_TexWidth;
	int m_TexHeight;

	LPDIRECT3DVERTEXBUFFER9	m_pVB_POS;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_NORMAL;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_COLOR;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_TEX;

private:
	void MakeVex(void);     // ���_�̐ݒ�
	D3DXVECTOR2 m_TexPos;
	D3DXVECTOR2 m_TexScl;
};

#endif