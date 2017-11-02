#ifndef _MODE_H_
#define _MODE_H_

//   �O���錾
class CPlayer;
class CMeshField;
class CSkyBox;

//*****************************************************************************
//   ���[�h�N���X��`
//*****************************************************************************
class CMode
{
public:
	virtual void Init(void) = 0;      // ����������
	virtual void Uninit(void) = 0;      // �I������
	virtual void Update(void) = 0;      // �X�V����
	virtual void Draw(void) = 0;      // �`�揈��
};

// �^�C�g��
class CModeTitle : public CMode
{
private:

public:
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

// �Q�[��
class CModeGame : public CMode
{
private:
	static CPlayer *m_pPlayer;
	CSkyBox *m_pSkyBox;
	static CMeshField *m_pMeshField;
	void LoadFile(char* FileName);

public:
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshField *GetMeshField() { return m_pMeshField; }
	static CPlayer *GetPlayer() { return m_pPlayer; }
};

// ���U���g
class CModeResult : public CMode
{
private:
	static bool m_Clear;
public:
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetClear(bool Clear);
};

#endif