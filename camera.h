#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
//   �J�����N���X��`
//*****************************************************************************
class CCamera
{
public:
	// �f�t�H���g�R���X�g���N�^
	CCamera();
	// �f�X�g���N�^
	~CCamera();
	
	// ������
	void Init(void);
	// �I������
	void Uninit(void);
	// �X�V����
	void Update(void);
	// �^�C�g���X�V����
	void Update(float RotY);
	// �J�����Z�b�g
	void Set(void);

	// ���W���
	void SetPosEye(D3DXVECTOR3 pos)	{ m_PosEye = pos; }
	// �����_���
	void SetPosAt(D3DXVECTOR3 pos)	{ m_PosAt = pos; }
	// �������
	void SetLen(float Len)			{ m_Length = Len; }
	// �p�x���
	void SetRot(D3DXVECTOR3 Rot)	{ m_Rot = Rot; }

	// �p�x�擾
	D3DXVECTOR3 GetRot()		{ return m_Rot; }
	// �r���[�s��擾
	D3DXMATRIX	GetMtxView()	{ return m_MtxView; }
	// �v���W�F�N�V�����s��擾
	D3DXMATRIX	GetMtxProj()	{ return m_MtxProj; }
	// ���W�擾
	D3DXVECTOR3	GetPosEye()		{ return m_PosEye; }

private:
	void ModeGame(void);
	void ModeDebug(void);

	D3DXMATRIX  m_MtxView;		// �r���[�s��
	D3DXMATRIX  m_MtxProj;		// �v���W�F�N�V�����s��
	D3DXVECTOR3 m_PosEye;		// ���W
	D3DXVECTOR3 m_PosAt;		// �����_
	D3DXVECTOR3 m_VecUp;		// �����
	D3DXVECTOR3     m_Move;		// �ړ���
	D3DXVECTOR3     m_Rot;		// �p�x
	float       m_Length;		// ���W�ƒ����_�̋���
	float       m_fZoom;		// ����p
	bool		m_Mode;			// �J�������[�h
};

#endif