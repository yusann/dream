//=============================================================================
// ���C�g
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "light.h"
#include "camera.h"

//*****************************************************************************
//   �ÓI�����o�ϐ�
//*****************************************************************************
CLight::LIGHT CLight::m_light;

CLight::CLight()
{
}

CLight::~CLight()
{
}

//=======================================================================================
//   ����������
//=======================================================================================
void CLight::Init()
{
	int nCntLight;
	for (nCntLight = 0; nCntLight < 1; nCntLight++) {
		ZeroMemory(&m_light.light, sizeof(D3DLIGHT9));              // ������  ={0}����
		m_light.light.Type = D3DLIGHT_DIRECTIONAL;             // �^�C�v
		m_light.light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);       // ���s�����i���C�g�̐F�j
		m_light.light.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);       // ����
		m_light.vecDir = D3DXVECTOR3(10.0f, -10.0f, 1.0f);               // ����
	}

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
	int nCntLight;
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}
	// ���C�g�̍ő吔�����[�v
	for (nCntLight = 0; nCntLight < 1; nCntLight++) {

		// �P�ʃx�N�g���̎Z�o
		D3DXVec3Normalize((D3DXVECTOR3*)&m_light.light.Direction, &m_light.vecDir);

		// �f�o�C�X�Ƀ��C�g��ݒ�
		pDevice->SetLight(nCntLight, &m_light.light);                   // nCntLight�Ԗڂ̃��C�g�̐ݒ�
		pDevice->LightEnable(nCntLight, TRUE);                  // nCntLight�Ԗڂ̃��C�g��ON�ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}