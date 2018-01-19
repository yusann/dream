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
	
	void Init(void) override;                              // ����������
	void Uninit(void) override;                            // �I������
	void Update(void) override;                            // �X�V����
	void Draw(void) override;                              // �`�揈��
	void DrawDepth(void) override {};  // �`�揈��
	void DrawStencilShadow(void) override {};  // �`�揈��
	void DrawGBuffer(void) override {};  // �`�揈��
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