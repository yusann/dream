#ifndef _BLOCK_H_
#define _BLOCK_H_

// �O���錾
#ifdef _DEBUG
class CMeshCube;
#endif
class CShadowModel;

//*****************************************************************************
//   �u���b�N�N���X��`
//*****************************************************************************
class CBlock : public CSceneModelX
{
public:
	CBlock(D3DXVECTOR3 pos, D3DXVECTOR3 scl);	// �R���X�g���N�^
	~CBlock();					// �f�X�g���N�^

	typedef enum
	{
		STATE_NONE = 0,
		STATE_SWITCH,
		STATE_MAX
	}STATE;
	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl);                  // �쐬

	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��

	void onSwitch(void) { m_State = STATE_SWITCH; }
#ifdef _DEBUG
	void ImGui(void);
#endif

private:
	CBlock() : CSceneModelX(CScene::OBJTYPE_BLOCK) {};					// �f�t�H���g�R���X�g���N�^
	STATE m_State;
	int m_Frame;
#ifdef _DEBUG
	CMeshCube* m_Collision;
#endif
};

#endif