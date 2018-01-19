#ifndef _DEBUG_SHADOW_MAP_H_
#define _DEBUG_SHADOW_MAP_H_

//*****************************************************************************
//   2D�I�u�W�F�N�g�N���X��`
//*****************************************************************************
class CDebugShadowMap
{
public:
	CDebugShadowMap();             // �f�t�H���g�R���X�g���N�^
	~CDebugShadowMap() {}                             // �f�X�g���N�^

	static CDebugShadowMap *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scl);                  // �쐬
	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 scl);        // ����������
	void Uninit(void);      // �I������
	void Update(LPDIRECT3DTEXTURE9 pTexture);      // �X�V����
	void Draw(void);        // �`�揈��

	static void DrawAll(void);
	static void UninitAll(void);

private:
	void MakeVex(void);     // ���_�̐ݒ�

	LPDIRECT3DVERTEXBUFFER9 m_pVB;  // ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Scl;
	static std::vector<CDebugShadowMap*> m_Debug;
};

#endif