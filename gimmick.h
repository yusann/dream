#ifndef _GIMMICK_H_
#define _GIMMICK_H_

// �O���錾
class CSwitch;
class CBlock;

//*****************************************************************************
//   �u���b�N�N���X��`
//*****************************************************************************
class CGimmick
{
public:
	CGimmick();					// �f�t�H���g�R���X�g���N�^
	~CGimmick();					// �f�X�g���N�^

	static CGimmick *Create(D3DXVECTOR3 BlockPos, D3DXVECTOR3 BlockScl);                  // �쐬

	void Init(D3DXVECTOR3 BlockPos, D3DXVECTOR3 BlockScl);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void SetSwitch(D3DXVECTOR3 Pos);

private:
	std::vector<CSwitch*> m_pSwitch;
	CBlock *m_pBlock;
};

#endif