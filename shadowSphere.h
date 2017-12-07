#ifndef _SHADOW_SPHERE_H_
#define _SHADOW_SPHERE_H_

//*****************************************************************************
//   �e�N���X��`
//*****************************************************************************
class CShadowSphere
{
public:
	CShadowSphere();					// �f�t�H���g�R���X�g���N�^
	CShadowSphere(int numBlockX, int numBlockY,  float radius, D3DXVECTOR3 scl, D3DXCOLOR color, D3DXVECTOR3 pos);		// �R���X�g���N�^
	~CShadowSphere();					// �f�X�g���N�^

	// ��������
	static CShadowSphere *Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl);
	static CShadowSphere *Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXVECTOR3 pos);
	static CShadowSphere *Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXCOLOR color);

	void Init(void);												// ����������
	void Uninit(void);												// �I������
	void Update(const D3DXVECTOR3 pos);								// �X�V����
	void Update(const D3DXVECTOR3 pos, const D3DXVECTOR3 scl);		// �X�P�[���X�V����
	void Draw(void);												// �`�揈��

private:
	void MakeVex(void);				// �e���_�̐ݒ�
	void MakeSphereVex(void);		// �X�t�B�A���_�̐ݒ�
	void MakeSphereBuff(void);		// �X�t�B�A�o�b�t�@�̐ݒ�
	void DrawSphere(void);			// �X�t�B�A�`�揈��

	// �e
	LPDIRECT3DVERTEXBUFFER9	m_VtxBuff;		// ���_�o�b�t�@
	D3DXCOLOR				m_Color;		// �F

	// �X�t�B�A
	LPDIRECT3DVERTEXBUFFER9	m_SphereVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	m_SphereIdxBuff;	// �C���f�b�N�X�o�b�t�@
	D3DXVECTOR3		m_SpherePos;	// ���W
	D3DXVECTOR3		m_SphereScl;	// �X�P�[��
	float	m_SphereRadius;			// ���a
	int		m_SphereNumX;			// ������X
	int		m_SphereNumY;			// ������Y
	int		m_PolygonNum;			// �|���S����
	int		m_VexNum;				// ���_��
	int		m_IndexNum;				// �C���f�N�X��

	LPDIRECT3DVERTEXBUFFER9	m_pVB_POS;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_NORMAL;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_COLOR;
	LPDIRECT3DVERTEXBUFFER9	m_pVB_TEX;
};

#endif