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

	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(DRAWTYPE type);     // �`�揈��
	void SetTexID(int ID = 0);

protected:
	int m_TexWidth;
	int m_TexHeight;
	D3DXVECTOR2 m_TexPos;
	D3DXVECTOR2 m_TexScl;
	D3DXQUATERNION m_Quaternion;
	float m_Angle;
	float m_Length;

private:
	void MakeVex(void);     // ���_�̐ݒ�
};

#endif