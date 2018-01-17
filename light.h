//*****************************************************************************
//   ��d��`�h�~
//*****************************************************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
//   �N���X�̒�`
//*****************************************************************************
// �V�[���N���X
class CLight
{
public:
	CLight();                                   // �f�t�H���g�R���X�g���N�^
	~CLight();                                  // �f�X�g���N�^
	
	void Init(void);                              // ����������
	void Uninit(void);                            // �I������
	void Update(void);
	void Set(void);

	D3DXVECTOR3 GetPos() { return m_PosEye; }
	D3DXVECTOR3 GetDir() { return m_Direction; }
	// �r���[�s��擾
	D3DXMATRIX	GetMtxView() { return m_MtxView; }
	// �v���W�F�N�V�����s��擾
	D3DXMATRIX	GetMtxProj() { return m_MtxProj; }
	float		GetFar() { return m_Far; }
	float		GetDepthEpsilon() { return m_DepthEpsilon; }
	float		GetDepthEpsilonScl() { return m_DepthEpsilonScl; }
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }

private:
	D3DXVECTOR3 m_PosEye;		// ���W
	D3DXVECTOR3 m_PosAt;		// �����_
	D3DXVECTOR3 m_VecUp;		// �����
	D3DXVECTOR3 m_Direction;		// ���W

	D3DXMATRIX  m_MtxView;		// �r���[�s��
	D3DXMATRIX  m_MtxProj;		// �v���W�F�N�V�����s��
	float       m_Far;
	float		m_DepthEpsilon;
	float		m_DepthEpsilonScl;
	LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif