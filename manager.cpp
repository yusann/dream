//=============================================================================
// �}�l�[�W���[����
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "inputKey.h"
#include "sound.h"

#include "mode.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "modelX.h"
#include "motionPartsX.h"

#include "scene.h"
#include "scene2D.h"

#include "scene3D.h"

#include "sceneMesh.h"
#include "meshField.h"
#include "meshCube.h"

#include "sceneBillboard.h"

#include "sceneModelX.h"
#include "sceneMotionPartsX.h"
#include "player.h"
#include "enemy.h"

//*****************************************************************************
//   �ÓI�����o�[�ϐ��錾
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;                      // �����_���[
CSound *CManager::m_pSound = NULL;
CMode *CManager::m_pMode = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;

CManager::CManager()
{
}

CManager::~CManager()
{
}

//==================================================================================================================================================
// ����������
//==================================================================================================================================================
HRESULT CManager::Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	// �����_���[�̐���
	m_pRenderer = new CRenderer;
	m_pRenderer->Init( hWnd, bWindow );

	// �L�[����̐���
	CInputKey::Init(hInstance, hWnd);

	// �T�E���h�̐���
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// �J�����̐���
	m_pCamera = new CCamera;
	m_pCamera->Init();

	// ���C�g�̐���
	m_pLight = new CLight;
	m_pLight->Init();

	// �e�N�X�`����ǂݍ���
	CTexture::Init();

	// ���f����ǂݍ���
	CModelX::Init();

	CMotionPartsX::Init();

	// �I�u�W�F�N�g�̐���
	SetMode(new CModeTitle);

#ifdef _DEBUG
	ImGui_ImplDX9_Init(hWnd, GetRenderer()->GetDevice());
#endif

	return S_OK;

}

//==================================================================================================================================================
// �I������
//==================================================================================================================================================
void CManager::Uninit(void)
{
	SAFE_UNINIT(m_pMode);

	// �I�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	CMotionPartsX::Uninit();

	// ���f����j��
	CModelX::Uninit();

	// �e�N�X�`����j��
	CTexture::Uninit();

	// �J�����̔j��
	SAFE_UNINIT(m_pCamera);

	// ���C�g�̔j��
	SAFE_UNINIT(m_pLight);

	// �T�E���h�̔j��
	SAFE_UNINIT(m_pSound);

	// �L�[����̔j��
	CInputKey::Uninit();

	// �����_���[�̔j��
	SAFE_UNINIT(m_pRenderer);
}

//==================================================================================================================================================
// �X�V����
//==================================================================================================================================================
void CManager::Update(void)
{
#ifdef _DEBUG
	// ImGui���쐬
	ImGui_ImplDX9_NewFrame();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
#endif
	CInputKey::Update();			// �L�[����X�V
	m_pCamera->Update();			// �J�����X�V
	m_pLight->Update();				// ���C�g�X�V

	// �X�V����
	CScene::UpdateAll();        // �V�[��
	m_pMode->Update();
}

//==================================================================================================================================================
// �`�揈��
//==================================================================================================================================================
void CManager::Draw(void)
{
	m_pCamera->Set();		// �J�����Z�b�g
	m_pLight->Set();		// ���C�g�Z�b�g

	// �`��J�n
	if (m_pRenderer->DrawBegin())
	{
		// �`�揈��
		CScene::DrawAll();             // �V�[��
		m_pMode->Draw();

#ifdef _DEBUG
		ImGui::Render();
#endif

		// �`��I��
		m_pRenderer->DrawEnd();
	}
}

//==================================================================================================================================================
// ���[�h�̃Z�b�g����
//==================================================================================================================================================
void CManager::SetMode(CMode *pMode)
{
	if (m_pMode != NULL)
	{
		m_pMode->Uninit();
		delete m_pMode;
	}
	m_pMode = pMode;
	if (m_pMode != NULL)
	{
		m_pMode->Init();
	}
}