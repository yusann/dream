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
	m_Rot = D3DXVECTOR2(1.0f, 0.0f);
	m_PosAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Direction = D3DXVECTOR3(1.0f, -1.0f, 1.0f);               // ����
	m_Length = 1000.0f;
	SetPos(&m_PosEye,m_PosAt, m_Length, m_Rot);

	m_Far = 3000.0f;
	m_DepthEpsilon = 5.0f;
	m_DepthEpsilonScl = 0.000001f;
	// �P�ʃx�N�g���̎Z�o
	D3DXVECTOR3	vecDir = -1.0f *m_PosEye;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Direction, &vecDir);

	m_pTexture = NULL;
	D3DXCreateTexture(pDevice, 2048, 2048, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &m_pTexture);
	m_pZBufferSurface = NULL;
	pDevice->CreateDepthStencilSurface(2048, 2048, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, FALSE,
		&m_pZBufferSurface, NULL);
	m_viewPort.Height = 2048;
	m_viewPort.Width = 2048;
	m_viewPort.MaxZ = 1.0f;
	m_viewPort.MinZ = 0.0f;
	m_viewPort.X = 0.0f;
	m_viewPort.Y = 0.0f;
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
	static float posX = 1.0f;
	static float posY = 0.0f;
	static float len = 1000.0f;
	ImGui::DragFloat("LightFar", &m_Far, 10.0f);
	ImGui::DragFloat("LightposX", &posX, 0.001f);
	ImGui::DragFloat("LightposY", &posY, 0.001f);
	ImGui::DragFloat("LightLen", &len, 1.0f);
	ImGui::DragFloat("Depth Epsilon", &m_DepthEpsilon, 0.01f);
	ImGui::InputFloat("Depth Epsilon Scl", &m_DepthEpsilonScl);
	m_Rot = D3DXVECTOR2(posX, posY);
	m_Length = len;
	SetPos(&m_PosEye, m_PosAt, m_Length, m_Rot);

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
		1.0f,			// �A�X�y�N�g��ifloat�Ōv�Z����Afloat>int�Ȃ̂ŕЕ���OK�j
		1.0f,											// near �K��0.0f���傫������  �ǂ�����`�悷�邩
		m_Far);										// far �ǂ��܂ŕ`�悷�邩

	//static float fNear = 2000.0f;
	//ImGui::DragFloat("Near", &fNear, 10.0f);
	//float nearH = fNear * tan(1.0f / 2.0f) * 2.0f;
	//float nearW = nearH * SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	//D3DXMatrixOrthoLH(&m_MtxProj, nearW, nearH, 1.0f, m_Far);

	// �r���[�s��̍쐬 LH������W�n
	D3DXMatrixLookAtLH(&m_MtxView, &m_PosEye, &m_PosAt, &m_VecUp);    // Eye,At,Up�̏�񂩂�r���[�s��(mtxView)�����֐�
}

void CLight::Set(D3DXVECTOR3 posAt, float len)
{
	D3DXVECTOR3 PosEye,PosAt;
	PosAt = posAt;
	SetPos(&PosEye, PosAt, len, m_Rot);

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
		1.0f,			// �A�X�y�N�g��ifloat�Ōv�Z����Afloat>int�Ȃ̂ŕЕ���OK�j
		1.0f,											// near �K��0.0f���傫������  �ǂ�����`�悷�邩
		m_Far);										// far �ǂ��܂ŕ`�悷�邩

	// �r���[�s��̍쐬 LH������W�n
	D3DXMatrixLookAtLH(&m_MtxView, &PosEye, &PosAt, &m_VecUp);    // Eye,At,Up�̏�񂩂�r���[�s��(mtxView)�����֐�
}

void CLight::SetPos(D3DXVECTOR3* posEye, const D3DXVECTOR3 posAt, const float len, const D3DXVECTOR2 rot)
{
	posEye->x = (float)cos(rot.y) * (float)cos(rot.x) * len;
	posEye->z = (float)sin(rot.y) * (float)cos(rot.x) * len;
	posEye->y = (float)sin(rot.x) * len;
	*posEye += posAt;
}