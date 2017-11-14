#ifndef _SHADOW_H_
#define _SHADOW_H_

//*****************************************************************************
//   �e�N���X��`
//*****************************************************************************
class CShadow
{
public:
	CShadow();					// �f�t�H���g�R���X�g���N�^
	CShadow(int numBlockX,
			int numBlockY, 
			float radius,
			D3DXVECTOR3 scl,
			D3DXVECTOR3 pos);
	~CShadow();					// �f�X�g���N�^

	static CShadow *Create(int numBlockX,
							int numBlockY,
							float radius,
							D3DXVECTOR3 scl,
							D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f));                  // �쐬

	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(const D3DXVECTOR3 pos);      // �X�V����
	void Update(const D3DXVECTOR3 pos, const D3DXVECTOR3 scl);      // �X�V����
	void Draw(void);        // �`�揈��

private:
	void MakeVex(void);     // ���_�̐ݒ�
	void MakeSphereVex(void);     // ���_�̐ݒ�
	void MakeSphereBuff(void);    // �o�b�t�@�̐ݒ�
	void DrawSphere(void);

	D3DXCOLOR   m_Color;    // �F
	D3DXVECTOR3 m_SpherePos;
	D3DXVECTOR3 m_SphereScl;
	float m_SphereRadius;
	int m_SphereNumX;
	int m_SphereNumY;
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;         // ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_SphereVtxBuff;    // ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9  m_SphereIdxBuff;     // �C���f�b�N�X�o�b�t�@
	int   m_PolygonNum;
	int   m_VexNum;
	int   m_IndexNum;
};

#endif