#ifndef _MODELX_H_
#define _MODELX_H_

#define MODEL_MATERIAL_MAX (100)

//*****************************************************************************
//   X���f�����\�[�X�N���X�̒�`
//*****************************************************************************
class CModelX
{
public:

	// ���f�����
	typedef enum
	{
		TYPE_PLAYER = 0,
		TYPE_ENEMY,
		TYPE_BLOCK,
		TYPE_SWITCH,
		TYPE_GOAL,
		TYPE_MAX
	}TYPE;

	// ���f�����
	typedef struct
	{
		LPD3DXMESH			pMesh;              // ���C�g
		LPD3DXBUFFER		pBuffMat;           // ����
		DWORD				NumMat;
		LPDIRECT3DTEXTURE9	pTexture[MODEL_MATERIAL_MAX];
	}MODELX;
	CModelX();						// �f�t�H���g�R���X�g���N�^
	~CModelX();						// �f�X�g���N�^
	
	static void Init(void);                              // ����������
	static void Uninit(void);                            // �I������
	static MODELX GetModelX(TYPE type);					// ���f���擾

private:
	static MODELX	m_modelX[TYPE_MAX];					// ���f�����
	static char m_TexName[TYPE_MAX][128];				// ���f���p�X
};

#endif