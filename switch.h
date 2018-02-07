#ifndef _SWITCH_H_
#define _SWITCH_H_

// �O���錾
#ifdef _DEBUG
class CMeshCube;
#endif
class CShadowModel;
class CBlock;

//*****************************************************************************
//   �u���b�N�N���X��`
//*****************************************************************************
class CSwitch : public CSceneModelX
{
public:
	CSwitch();					// �f�t�H���g�R���X�g���N�^
	CSwitch(D3DXVECTOR3 pos);	// �R���X�g���N�^
	~CSwitch();					// �f�X�g���N�^

	typedef enum
	{
		STATE_NONE = 0,
		STATE_MOVE,
		STATE_MAX
	}STATE;
	static CSwitch *Create(D3DXVECTOR3 pos);                  // �쐬

	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��
	void SetisOn(const bool isOn);
	bool GetisOn(void);
	D3DXVECTOR3& Position(void) { return m_Pos; }
	D3DXVECTOR3& Scale(void) { return m_Scl; }

private:
	STATE m_State;
	bool m_isOn;
	int m_Frame;
#ifdef _DEBUG
	CMeshCube* m_Collision;
#endif
};

#endif