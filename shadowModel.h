#ifndef _SHADOW_MODEL_H_
#define _SHADOW_MODEL_H_

//*****************************************************************************
//   �e�N���X��`
//*****************************************************************************
class CShadowModel : public CScene2D
{
public:
	CShadowModel();					// �f�t�H���g�R���X�g���N�^
	CShadowModel(const LPD3DXMESH pMesh);
	~CShadowModel();					// �f�X�g���N�^

	static CShadowModel *Create(const LPD3DXMESH pMesh);                  // �쐬

	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(void);
	void Draw(void);        // �`�揈��
	void SetMatrix(const D3DXMATRIX matrix) {
		m_Matrix = matrix;
	}

private:
	struct SHADOWVOLUME {						//----- �V���h�E�{�����[��
		D3DXVECTOR3		*pVertex;				// ���W
		int				iNumVertex;				// ���_��
	};

	HRESULT BuildShadowVolume( LPD3DXMESH pMesh, D3DXVECTOR3 vLight);
	void AddEdge(WORD* pEdge, DWORD* pdwNumEdge, WORD v0, WORD v1);

	SHADOWVOLUME	m_Shadow;						// �V���h�E�{�����[��
	LPD3DXMESH		m_pMesh;
	D3DXMATRIX		m_Matrix;

	static int m_MaxID;
};

#endif