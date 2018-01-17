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
	CBlock();					// �f�t�H���g�R���X�g���N�^
	CBlock(D3DXVECTOR3 pos, D3DXVECTOR3 scl);	// �R���X�g���N�^
	~CBlock();					// �f�X�g���N�^

	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl);                  // �쐬

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