#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
//   �J�����N���X��`
//*****************************************************************************
class CCamera
{
public:
	typedef struct
	{
		D3DXMATRIX  mtxView;     // �r���[�s��
		D3DXVECTOR3 posEye;      // ���W
		D3DXVECTOR3 posAt;       // �����_
		D3DXVECTOR3 vecUp;       // �����
	}CAMERA;

	CCamera();                                   // �f�t�H���g�R���X�g���N�^
	~CCamera();                                  // �f�X�g���N�^
	
	void Init(void);                              // ����������
	void Uninit(void);                            // �I������
	void Update(void);		// �X�V����
	void Update(float RotY);		// �X�V����
	void Set(void);			// �Z�b�g����

	// �J�����̎擾
	static CAMERA GetCamera() {
		return m_pCamera;
	}
	D3DXVECTOR3 GetCameraY() {
		return m_Rot;
	}
	void SetPosEye(D3DXVECTOR3 pos) { m_pCamera.posEye = pos; }
	void SetPosAt(D3DXVECTOR3 pos) { m_pCamera.posAt = pos; }
	void SetLen(float Len) { m_length = Len; }
	void SetRot(D3DXVECTOR3 Rot) { m_Rot = Rot; }

private:
	void ModeGame(void);
	void ModeDebug(void);

	static CAMERA m_pCamera;
	D3DXVECTOR3     m_posMove;     // �ړ���
	D3DXVECTOR3     m_Rot;         // �p�x
	D3DXVECTOR3		m_LookAtTarget;
	D3DXVECTOR3		m_PosTarget;
	float		m_RotYTarget;
	float       m_length;
	float       m_fZoom;       // �Y�[��
	bool		m_Mode;
};

#endif