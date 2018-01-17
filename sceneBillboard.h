#ifndef _SCENEBILLBOARD_H_
#define _SCENEBILLBOARD_H_

//*****************************************************************************
//   �r���{�[�h�V�[���N���X�̒�`
//*****************************************************************************
class CSceneBillboard : public CScene
{
public:
	typedef enum
	{
		NORMAL = 0,
		ADD,
		MAX
	}DRAWTYPE;
	CSceneBillboard(int Priority = 3);             // �f�t�H���g�R���X�g���N�^
	~CSceneBillboard();            // �f�X�g���N�^

	void Init(void) override;        // ����������
	void Uninit(void) override;      // �I������
	void Update(void) override;      // �X�V����
	void Draw(void) override {};     // �`�揈��
	void Draw(DRAWTYPE type);     // �`�揈��
	void DrawDepth(void) override {};  // �`�揈��
	void DrawStencilShadow(void) override {};  // �`�揈��
	void SetTexID(int ID = 0);

protected:
	int m_TexWidth;
	int m_TexHeight;
	D3DXVECTOR2 m_TexPos;
	D3DXVECTOR2 m_TexScl;
	D3DXQUATERNION m_Quaternion;
	float m_Angle;
	float m_Length;

	LPDIRECT3DVERTEXBUFFER9	m_pVB_POS;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_NORMAL;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_COLOR;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_TEX;

private:
	void MakeVex(void);     // ���_�̐ݒ�
};

#endif