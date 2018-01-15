//*****************************************************************************
//   �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "light.h"
#include "camera.h"

//=======================================================================================
//   �R���X�g���N�^
//=======================================================================================
CLight::CLight()
{
	D3DXMatrixIdentity(&m_MtxView);
	D3DXMatrixIdentity(&m_MtxProj);
}

//=======================================================================================
//   �f�X�g���N�^
//=======================================================================================
CLight::~CLight()
{
}

//=======================================================================================
//   ����������
//=======================================================================================
void CLight::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));              // ������  ={0}����
	m_Light.Type = D3DLIGHT_DIRECTIONAL;             // �^�C�v
	m_Light.Position = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);       // ���s�����i���C�g�̐F�j
	m_Light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);       // ����
	m_Light.Direction = D3DXVECTOR3(1.0f, -1.0f, 1.0f);               // ����
	// �P�ʃx�N�g���̎Z�o
	D3DXVECTOR3	vecDir = -1.0f * m_Light.Position;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &vecDir);

	m_pTexture = NULL;
	D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &m_pTexture);
}

//=======================================================================================
//   �I������
//=======================================================================================
void CLight::Uninit()
{
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CLight::Update()
{
}

//=======================================================================================
//   �Z�b�g����
//=======================================================================================
void CLight::Set()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �v���W�F�N�V�����s��
	D3DXMatrixPerspectiveFovLH(&m_MtxProj,				// Fov�͉�p
		D3DX_PI / 3.0f,										// ��p�i����p�j60�x�ɂ��邽�߃΁��R
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,			// �A�X�y�N�g��ifloat�Ōv�Z����Afloat>int�Ȃ̂ŕЕ���OK�j
		1.0f,											// near �K��0.0f���傫������  �ǂ�����`�悷�邩
		10000.0f);										// far �ǂ��܂ŕ`�悷�邩
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProj);

	// �r���[�s��̍쐬 LH������W�n
	D3DXVECTOR3	pos = m_Light.Position;
	D3DXMatrixLookAtLH(&m_MtxView, &pos, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // Eye,At,Up�̏�񂩂�r���[�s��(mtxView)�����֐�

																	  // �r���[�s��Z�b�g
	pDevice->SetTransform(D3DTS_VIEW, &m_MtxView);
}