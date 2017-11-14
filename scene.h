#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
//   �V�[���N���X�̒�`
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BACKGROUND,

		OBJTYPE_FIELD,
		OBJTYPE_BLOCK,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_PARTICLE,

		OBJTYPE_UI,
		OBJTYPE_DEBUG_MESH,
		OBJTYPE_FADE,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 3);                        // �f�t�H���g�R���X�g���N�^
	virtual ~CScene();                       // �f�X�g���N�^
	
	virtual void Init(void)   =0;      // ����������
	virtual void Uninit(void) =0;      // �I������
	virtual void Update(void) =0;      // �X�V����
	virtual void Draw(void)   =0;      // �`�揈��

	static void UpdateAll(void);                // ���ׂĂ̍X�V
	static void DrawAll(void);                  // ���ׂĂ̕`��
	static void ReleaseAll(int CntMax = OBJTYPE_MAX);               // ���ׂẴ����[�X

	static CScene *GetScene(int Priority) { return m_Top[Priority]; }			// �V�[���̎擾����
	void SetObjType(OBJTYPE ObjType) { m_ObjType = ObjType; }					// �V�[���^�C�v�̑������
	OBJTYPE GetObjType(void) { return m_ObjType; }								// �V�[���^�C�v�̎擾����

	CScene *SetNextScene(void) { return m_Next; }
	D3DXVECTOR3 GetPos(void) { return m_Pos; }
	D3DXVECTOR3 GetScl(void) { return m_Scl; }

protected:
	void Release(void);                         // �����[�X�����i�q�N���X�������Ă���e�N���X���������ߗp�j
	D3DXVECTOR3             m_Pos;       // ���W
	D3DXVECTOR3             m_Scl;      // �T�C�Y
	D3DXCOLOR               m_Color;    // �F
	LPDIRECT3DTEXTURE9      m_pTexture;  // �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;  // ���_�o�b�t�@�ւ̃|�C���^

private:
	static CScene *m_Top[OBJTYPE_MAX];      // �V�[���̐錾
	CScene *m_Prev;
	CScene *m_Next;
	static int m_NumScene;                     // �V�[���̑���
	int m_Priority;
	OBJTYPE m_ObjType;
	bool m_Delete;

};

#endif