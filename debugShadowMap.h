#ifndef _DEBUG_SHADOW_MAP_H_
#define _DEBUG_SHADOW_MAP_H_

//*****************************************************************************
//   2D�I�u�W�F�N�g�N���X��`
//*****************************************************************************
class CDebugShadowMap : public CScene2D
{
public:
	CDebugShadowMap();             // �f�t�H���g�R���X�g���N�^
	~CDebugShadowMap();                             // �f�X�g���N�^

	static CDebugShadowMap *Create();                  // �쐬
	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��
};

#endif