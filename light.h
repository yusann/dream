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

	D3DXVECTOR3 GetPos() {
		return m_Light.Position;
	}
	D3DXVECTOR3 GetDir() {
		return m_Light.Direction;
	}

private:
	D3DLIGHT9 m_Light;              // ���C�g
};

#endif