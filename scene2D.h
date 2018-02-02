#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//   2D�V�[���N���X�̒�`
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int Priority = 7);             // �f�t�H���g�R���X�g���N�^
	~CScene2D();                             // �f�X�g���N�^
	
	static CScene2D *Create(const LPDIRECT3DTEXTURE9 pTexture,
		const D3DXVECTOR2 Pos,
		const D3DXVECTOR2 Scl,
		const CScene::OBJTYPE ObjType,
		const int TexWidth = 1,
		const int TexHeight = 1);                  // �쐬
	void SetInfo(const LPDIRECT3DTEXTURE9 pTexture,
		const D3DXVECTOR2 Pos,
		const D3DXVECTOR2 Scl,
		const CScene::OBJTYPE ObjType,
		const int TexWidth,
		const int TexHeight);
	void Init(void) override;        // ����������
	void Uninit(void) override;      // �I������
	void Update(void) override;      // �X�V����
	void Draw(void) override;        // �`�揈��
	void DrawDepth(void) override {};  // �`�揈��
	void DrawStencilShadow(void) override {};  // �`�揈��
	void DrawGBuffer(void) override {};  // �`�揈��

	void SetVexColor(D3DXCOLOR Color);
	void SetVexPos();
	void SetVexUV();
	void SetVexGage(float val);
	void SetTexID(int nID = 0);

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;  // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR2 m_TexPos;
	D3DXVECTOR2 m_TexScl;

private:
	void MakeVex(void);     // ���_�̐ݒ�
	int m_TexWidth;
	int m_TexHeight;
};

#endif