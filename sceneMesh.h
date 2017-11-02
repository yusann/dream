#ifndef _SCENEMESH_H_
#define _SCENEMESH_H_

//*****************************************************************************
//   ���b�V���V�[���N���X�̒�`
//*****************************************************************************
class CSceneMesh : public CScene
{
public:
	CSceneMesh(int Priority = 1);                                   // �f�t�H���g�R���X�g���N�^
	~CSceneMesh();                                  // �f�X�g���N�^

	void Init(void);                              // ����������
	void Uninit(void);                            // �I������
	void Update(void);                            // �X�V����
	void Draw(void);                              // �`�揈��
	
protected:
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;     // �C���f�b�N�X�o�b�t�@
	D3DXVECTOR3 m_Rot;
	int   m_PolygonNum;
	int   m_VexNum;

};

#endif