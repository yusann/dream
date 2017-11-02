#ifndef _SCENEMOTIONPARTSX_H_
#define _SCENEMOTIONPARTSX_H_

#include "motionPartsX.h"

// �O���錾
#ifdef _DEBUG
class CMeshSphere;
#endif

//*****************************************************************************
//   �p�[�c���[�V�����N���X�̒�`
//*****************************************************************************
class CSceneMotionPartsX : public CScene
{
public:
	CSceneMotionPartsX(int Priority = 3);                                   // �f�t�H���g�R���X�g���N�^
	~CSceneMotionPartsX();                                  // �f�X�g���N�^

	// ���̓����蔻����
	struct COLLISION_SPHERE
	{
#ifdef _DEBUG
		CMeshSphere			*Sphere;
#endif
		D3DXVECTOR3			Pos;
		float				Scl;
	};

	// ���f��
	struct MODEL
	{
		MODEL				*pParent;
		D3DXVECTOR3			Pos;
		D3DXVECTOR3			Rot;
		D3DXVECTOR3			Scl;
		D3DXMATRIX			Matrix;
		std::vector<COLLISION_SPHERE*>	Collision;
	};

	void Init(void);                              // ����������
	void Uninit(void);                            // �I������
	void Update(void);                            // �X�V����
	void Draw(void);                              // �`�揈��
	D3DXVECTOR3 GetRot(void) { return m_Rot; }
	void SetMotion(int MotionID);

protected:
	const int GetKey() { return m_Key; }
	const int GetFrame() { return m_Frame; }
	const int GetMotionFrame() { return m_MotionFrame; }
	const std::vector<COLLISION_SPHERE*> GetCollisionSphere() { return m_CollisionSphere; }

	CMotionPartsX::MOTIONPARTSX *m_pMotionPartsX;
	D3DXVECTOR3				m_Rot;      // ��]
	float					m_Speed;
	float					m_Jump;
	bool m_LastKye;

private:
	struct VECTR3
	{
		D3DXVECTOR3			Pos;
		D3DXVECTOR3			Rot;
		D3DXVECTOR3			Scl;
	};

	void UpdateMotion(void);				// �}�g���N�X�Z�b�g����
	void UpdateBlendMotion(void);			// �قȂ郂�[�V�����̃}�g���N�X�Z�b�g����
	void UpdateLastKeyFrame(void);			// �Ō�̃L�[�t���[���X�V����

	std::vector<MODEL*>				m_Model;
	D3DXMATRIX						m_Matrix;
	std::vector<COLLISION_SPHERE*>	m_CollisionSphere;
	int m_MotionID;
	int m_Key;
	int m_Frame;
	int m_MotionFrame;

	// �قȂ郂�[�V�����̕�ԏ����p
	std::vector<VECTR3*>	m_BlendData;
	bool					m_Blend;
};

#endif