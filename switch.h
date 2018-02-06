#ifndef _SWITCH_H_
#define _SWITCH_H_

// �O���錾
#ifdef _DEBUG
class CMeshCube;
#endif
class CShadowModel;

//*****************************************************************************
//   �u���b�N�N���X��`
//*****************************************************************************
class CSwitch : public CSceneModelX
{
public:
	CSwitch();					// �f�t�H���g�R���X�g���N�^
	CSwitch(D3DXVECTOR3 pos, D3DXVECTOR3 scl);	// �R���X�g���N�^
	~CSwitch();					// �f�X�g���N�^

	static CSwitch *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl);                  // �쐬

	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

#ifdef _DEBUG
	void ImGui(void);
#endif

private:
#ifdef _DEBUG
	CMeshCube* m_Collision;
#endif
};

#endif