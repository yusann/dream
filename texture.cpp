//=============================================================================
// �e�N�X�`�����\�[�X
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//   �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CTexture::m_pTexture[CTexture::TEXTYPE_MAX] = {};
char CTexture::m_TexName[TEXTYPE_MAX][128] =
{
	"data/TEXTURE/bg.jpg",
	"data/TEXTURE/field000.jpg",
	"data/TEXTURE/kobeni0.png",
	"data/TEXTURE/bullet000.jpg",

	"data/TEXTURE/sky000.jpg",
	"data/TEXTURE/title000.jpg",
	"data/TEXTURE/title001.png",
	"data/TEXTURE/tutorial000.jpg",
	"data/TEXTURE/result000.jpg",
	"data/TEXTURE/result001.jpg",
	"data/TEXTURE/push000.png",

	"data/TEXTURE/particle001.png",
	"data/TEXTURE/particle001.png",
	"data/TEXTURE/particle001.png",

	"data/TEXTURE/life000.jpg",
	"data/TEXTURE/magic000.jpg",
	"data/TEXTURE/gageBG000.png",
	"data/TEXTURE/number000.png"
};

//*************
// ���C������
//*************
CTexture::CTexture()
{
}

CTexture::~CTexture()
{
}

//=======================================================================================
//   ����������
//=======================================================================================
void CTexture::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �e�N�X�`���̃G���[�`�F�b�N
	for (int i = 0; i < TEXTYPE_MAX; i++) {
		if( FAILED( D3DXCreateTextureFromFile( pDevice, m_TexName[i], &m_pTexture[i]))) {
			MessageBox( NULL , "�摜������܂���I" , "�G���[" , MB_OK | MB_ICONASTERISK );         // �I�����郁�b�Z�[�W
		}
	}
}

//=======================================================================================
//   �I������
//=======================================================================================
void CTexture::Uninit()
{
	// �e�N�X�`���̔j��
	for (int i = 0; i < TEXTYPE_MAX; i++) {
		SAFE_RELEASE(m_pTexture[i]);
	}
}

//=======================================================================================
//   �擾����
//=======================================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(int nNo) {
	return m_pTexture[nNo];
}