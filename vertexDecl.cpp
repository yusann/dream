//=============================================================================
// �V�F�[�_�̃x�[�X
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "vertexDecl.h"

LPDIRECT3DVERTEXDECLARATION9 CVertexDecl::m_pVertexDecl[TYPE_MAX];

void CVertexDecl::Init(LPDIRECT3DDEVICE9 pDevice)
{
	if (pDevice == NULL) {
		return;
	}
	// ������
	for (int i = 0; i < TYPE_MAX; ++i) {
		m_pVertexDecl[i] = NULL;
	}

	// 3D���_�̃t�H�[�}�b�g�錾
	D3DVERTEXELEMENT9 m_vertexElements3D[] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 1, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 2, 0,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 3, 0,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(m_vertexElements3D, &m_pVertexDecl[TYPE_3D]);

	// 2D���_�̃t�H�[�}�b�g�錾
	D3DVERTEXELEMENT9 m_vertexElements2D[] =
	{
		//float4 posT �X�g���[���ԍ�1�����g���Ȃ�
		{ 0, 0,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
		{ 0, 16,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 0, 20,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(m_vertexElements2D, &m_pVertexDecl[TYPE_2D]);

	// �G���[�`�F�b�N
	for (int i = 0; i < TYPE_MAX; ++i) {
		if (m_pVertexDecl[i] == NULL) {
			MessageBox(NULL, "���_�f�N�����[�V���������G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		}
	}
}

void CVertexDecl::Uninit()
{
	for (int i = 0; i < TYPE_MAX; ++i) {
		SAFE_RELEASE(m_pVertexDecl[i]);
	}
}

void CVertexDecl::SetTex3D(LPDIRECT3DDEVICE9 pDevice,
	const LPDIRECT3DVERTEXBUFFER9 vb_pos,
	const LPDIRECT3DVERTEXBUFFER9 vb_normal,
	const LPDIRECT3DVERTEXBUFFER9 vb_color,
	const LPDIRECT3DVERTEXBUFFER9 vb_tex)
{
	// ���_�̃f�N�����[�V�����̐ݒ�
	pDevice->SetVertexDeclaration(m_pVertexDecl[TYPE_3D]);

	// �X�g���[���Ƃ��Ē��_�o�b�t�@��ݒ�
	pDevice->SetStreamSource(0, vb_pos, 0, sizeof(VERTEX3D_POS));
	pDevice->SetStreamSource(1, vb_normal, 0, sizeof(VERTEX3D_NORMAL));
	pDevice->SetStreamSource(2, vb_color, 0, sizeof(VERTEX3D_COLOR));
	pDevice->SetStreamSource(3, vb_tex, 0, sizeof(VERTEX3D_TEX));
}
void CVertexDecl::SetTex2D(LPDIRECT3DDEVICE9 pDevice, const LPDIRECT3DVERTEXBUFFER9 vb)
{
	// ���_�̃f�N�����[�V�����̐ݒ�
	pDevice->SetVertexDeclaration(m_pVertexDecl[TYPE_2D]);

	// �X�g���[���Ƃ��Ē��_�o�b�t�@��ݒ�
	pDevice->SetStreamSource(0, vb, 0, sizeof(VERTEX2D));
}