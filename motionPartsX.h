#ifndef _MOTIONPARTSX_H_
#define _MOTIONPARTSX_H_

//*****************************************************************************
//   X���[�V�����p�[�c���\�[�X�N���X�̒�`
//*****************************************************************************
class CMotionPartsX
{
public:

	// ���f�����
	typedef enum
	{
		TYPE_PLAYER = 0,
		TYPE_ENEMY,
		TYPE_MAX
	}TYPE;

	// �p�[�c�������
	struct PART
	{
		std::string			FilePath;
		DWORD				NumMat;
		LPD3DXMESH			pMesh;
		LPD3DXBUFFER		pBuffMat;
		LPDIRECT3DTEXTURE9  *pTexture;
		D3DXVECTOR3			OffSetPos;
		D3DXVECTOR3			OffSetRot;
		D3DXVECTOR3			OffSetScl;
		int					Parent;
	};
	// ���ʉ�
	struct SOUND
	{
		int					ID;
		int					Frame;
	};

	// �����蔻��
	struct COLLISION
	{
		int					PartID;
		D3DXVECTOR3			Pos;
		float				Scl;
		int					StartFrame;
		int					EndFrame;
	};

	// �L�[���
	struct KEY
	{
		D3DXVECTOR3			Pos;
		D3DXVECTOR3			Rot;
		D3DXVECTOR3			Scl;
	};

	// �L�[�t���[�����
	struct KEY_FRAME
	{
		int Frame;
		std::vector<KEY*> Key;
	};

	// ���[�V�������
	struct MOTION
	{
		std::vector<KEY_FRAME*>	KeyFrame;
		std::vector<COLLISION*>	Collision;
		std::vector<SOUND*>		Sound;
	};

	struct  MOTIONPARTSX
	{
		std::vector<PART*>		Part;
		std::vector<MOTION*>	Motion;
	};

	static void Init(void);                              // ����������
	static void Uninit(void);                            // �I������
	static MOTIONPARTSX *GetMotionPartsX(TYPE type) { return &m_MotionPartsX[m_FileName[type]]; }					// ���f���擾

private:
	static MOTIONPARTSX LoadFile(char *FileName);
	static void LoadModel(PART *pPart);

	static std::unordered_map<char*, MOTIONPARTSX>	m_MotionPartsX;
	static char					m_FileName[][128];		// ���f���p�X
};

#endif