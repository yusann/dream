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
	/*
	// ���_�̃t�H�[�}�b�g�錾
	D3DVERTEXELEMENT9 m_vertexElements2D[] =
	{
		//float4 posT �X�g���[���ԍ�1�����g���Ȃ�
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 1, 0,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		{ 2, 0,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(m_vertexElements2D, &m_pVertexDecl[TYPE_2D_NOCOLOR]);
	*/
	// ���_�̃t�H�[�}�b�g�錾
	D3DVERTEXELEMENT9 m_vertexElements3D[] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 1, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 2, 0,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 3, 0,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(m_vertexElements3D, &m_pVertexDecl[TYPE_3D]);

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