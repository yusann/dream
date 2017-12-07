#ifndef _VERTEX_DECL_H_
#define _VERTEX_DECL_H_

//*****************************************************************************
//   �N���X�̒�`
//*****************************************************************************
// �V�[���N���X
class CVertexDecl
{
public:
	typedef enum
	{
		TYPE_3D = 0,
		TYPE_MAX
	}TYPE;
	// ���_�f�[�^�\����
	struct VERTEX3D_POS {
		D3DXVECTOR3	pos;		// �ʒu
	};
	struct VERTEX3D_NORMAL {
		D3DXVECTOR3	normal;		// �m�[�}��
	};
	struct VERTEX3D_COLOR {
		D3DCOLOR color;			// �F
	};
	struct VERTEX3D_TEX {
		D3DXVECTOR2 tex;		// �e�N�X�`�����W
	};

	static void Init(LPDIRECT3DDEVICE9 pDevice);
	static void Uninit(void);

	static LPDIRECT3DVERTEXDECLARATION9 *Get(TYPE type) {
		return &m_pVertexDecl[type];
	}

private:
	// ���_�f�N�����[�V�����ւ̃|�C���^
	static LPDIRECT3DVERTEXDECLARATION9 m_pVertexDecl[TYPE_MAX];
	
};

#endif