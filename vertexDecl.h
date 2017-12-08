#ifndef _VERTEX_DECL_H_
#define _VERTEX_DECL_H_

//*****************************************************************************
//   �N���X�̒�`
//*****************************************************************************
// �V�[���N���X
class CVertexDecl
{
public:
	// �f�N�����[�V�����̎��
	typedef enum
	{
		TYPE_3D = 0,
		TYPE_2D,
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

	// 2D
	struct VERTEX2D {
		D3DXVECTOR4	pos;		// �ʒu
		D3DCOLOR color;			// �F
		D3DXVECTOR2 tex;		// �e�N�X�`�����W
	};

	// ������
	static void Init(LPDIRECT3DDEVICE9 pDevice);
	// �I������
	static void Uninit(void);

	// �f�N�����[�V�����̃Z�b�g
	// 3D
	static void SetTex3D(LPDIRECT3DDEVICE9 pDevice, 
		const LPDIRECT3DVERTEXBUFFER9 vb_pos,
		const LPDIRECT3DVERTEXBUFFER9 vb_normal,
		const LPDIRECT3DVERTEXBUFFER9 vb_color,
		const LPDIRECT3DVERTEXBUFFER9 vb_tex);
	// 2D
	static void SetTex2D(LPDIRECT3DDEVICE9 pDevice, const LPDIRECT3DVERTEXBUFFER9 vb);

private:
	// ���_�f�N�����[�V�����ւ̃|�C���^
	static LPDIRECT3DVERTEXDECLARATION9 m_pVertexDecl[TYPE_MAX];
	
};

#endif