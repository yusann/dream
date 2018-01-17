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
	m_PosEye = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	m_PosAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Direction = D3DXVECTOR3(1.0f, -1.0f, 1.0f);               // ����

	m_Far = 3000.0f;
	m_DepthEpsilon = 5.0f;
	m_DepthEpsilonScl = 1.0f;
	// �P�ʃx�N�g���̎Z�o
	D3DXVECTOR3	vecDir = -1.0f *m_PosEye;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Direction, &vecDir);

	m_pTexture = NULL;
	D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &m_pTexture);
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
	static float posX = 500.0f;
	static float posY = 1000.0f;
	static float posZ = 500.0f;
	ImGui::DragFloat("LightFar", &m_Far, 10.0f);
	ImGui::DragFloat("LightposX", &posX, 1.0f);
	ImGui::DragFloat("LightposY", &posY, 1.0f);
	ImGui::DragFloat("LightposZ", &posZ, 1.0f);
	ImGui::DragFloat("Depth Epsilon", &m_DepthEpsilon, 0.01f);
	ImGui::InputFloat("Depth Epsilon Scl", &m_DepthEpsilonScl);
	m_PosEye = D3DXVECTOR3(posX, posY, posZ);

	// �P�ʃx�N�g���̎Z�o
	D3DXVECTOR3	vecDir = -1.0f *m_PosEye;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Direction, &vecDir);

	ImGui::Text("Light Direction(%.3f,%.3f,%.3f)", m_Direction.x, m_Direction.y, m_Direction.z);
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
		m_Far);										// far �ǂ��܂ŕ`�悷�邩

	// �r���[�s��̍쐬 LH������W�n
	D3DXMatrixLookAtLH(&m_MtxView, &m_PosEye, &m_PosAt, &m_VecUp);    // Eye,At,Up�̏�񂩂�r���[�s��(mtxView)�����֐�
}