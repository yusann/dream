//=============================================================================
// ���[�h
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "mode.h"
#include "modeGame.h"
#include "modeResult.h"
#include "manager.h"
#include "input.h"
#include "inputKey.h"
#include "sound.h"

#include "scene.h"
#include "scene2D.h"
#include "fade.h"

#include "sceneMesh.h"
#include "skyDome.h"
#include "meshField.h"

#include "sceneModelX.h"
#include "block.h"
#include "object2D.h"

#include "sceneMotionPartsX.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "goal.h"

//*****************************************************************************
//   �ÓI�����o�ϐ��錾
//*****************************************************************************
CMeshField *CModeGame::m_pMeshField = NULL;
CPlayer *CModeGame::m_pPlayer = NULL;

//==================================================================================
//   ����������
//==================================================================================
void CModeGame::Init(void)
{
	// �I�u�W�F�N�g�̔z�u
	m_pMeshField = CMeshField::Create();
	CSkyDome::Create(D3DXVECTOR3(0.0f, -2000.0f, 0.0f),5000.0f,18,18);

	LoadFile("data/objSave01.txt");

	CObject2D::Create(CObject2D::TYPE_UI_LIFE);
	CManager::GetSound()->Play(CSound::BGM_STAGE000);
	CCamera *pCamera = CManager::GetCamera();
	pCamera->SetRot(D3DXVECTOR3(0.4f,3.0f,0.0f));
	CGoal::Create(D3DXVECTOR3(55.0f, 157.0f, 0.0f), D3DXVECTOR3(4.0f, 4.0f, 4.0f));
}

//==================================================================================
//   �I������
//==================================================================================
void CModeGame::Uninit(void)
{
	CManager::GetSound()->Stop();

	// �ϐ��̔j��
	m_pMeshField = NULL;
	m_pPlayer = NULL;

	// �I�u�W�F�N�g�̔j��
	CScene::ReleaseAll(CScene::OBJTYPE_FADE);
}

//==================================================================================
//   �X�V����
//==================================================================================
void CModeGame::Update(void)
{
#ifdef _DEBUG
	static bool player_window = false;
	static bool enemy_window = false;
	static bool block_window = false;
	if (ImGui::Button("Player Window")) player_window ^= 1;
	if (ImGui::Button("Enemy  Window")) enemy_window ^= 1;
	if (ImGui::Button("Block  Window")) block_window ^= 1;
#endif

	// �N���A����
	// �V�[���̎擾�p�ϐ�
	CScene *pScene;

	if (CInputKey::GetInputKeyboard()->GetKeyTrigger(DIK_F6))
	{
		CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 10.0f));
	}

	// �G�S�Ń`�F�b�N
	pScene = CScene::GetScene(CScene::OBJTYPE_ENEMY);
	if (pScene == NULL)
	{
		CModeResult::SetClear(true);
		CFade::SetFade(new CModeResult);
	}
#ifdef _DEBUG
	else
	{
		if (enemy_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::Begin("Enemy Window", &player_window);
			int Cnt = -1;
			// NULL�`�F�b�N
			while (pScene != NULL)
			{
				// �G�̐錾
				CEnemy *pEnemy;
				pEnemy = (CEnemy*)pScene;

				Cnt++;
				std::string EnemyID = "ID " + std::to_string(Cnt);
				if (ImGui::TreeNode(EnemyID.c_str()))
				{
					pEnemy->ImGui();
					ImGui::TreePop();
				}
				pScene = pScene->SetNextScene();
			}
			ImGui::End();
		}
	}
#endif

	// �v���C���[���S�`�F�b�N
	pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER);
	if (pScene == NULL)
	{
		CModeResult::SetClear(false);
		CFade::SetFade(new CModeResult);
	}
	else
	{
		D3DXVECTOR3 pos = pScene->GetPos();
		if (pos.x >= 40.0f &&
			pos.x <= 60.0f &&
			pos.z >= -10.0f &&
			pos.z <= 20.0f)
		{
			CModeResult::SetClear(true);
			CFade::SetFade(new CModeResult);
		}
#ifdef _DEBUG
		if (player_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::Begin("Player Window", &player_window);
			CPlayer *pPlayer;
			pPlayer = (CPlayer*)pScene;
			pPlayer->ImGui();
			ImGui::End();
		}
#endif
	}

#ifdef _DEBUG
	// �u���b�N�f�o�b�O
	if (block_window)
	{
		pScene = CScene::GetScene(CScene::OBJTYPE_BLOCK);
		while (pScene != NULL)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::Begin("Block Window", &player_window);
			CBlock *pBlock;
			pBlock = (CBlock*)pScene;
			int Cnt = -1;
			Cnt++;
			std::string EnemyID = "ID " + std::to_string(Cnt);
			if (ImGui::TreeNode(EnemyID.c_str()))
			{
				pBlock->ImGui();
				ImGui::TreePop();
			}
			pScene = pScene->SetNextScene();
		}
		ImGui::End();
	}
#endif
}

//==================================================================================
//   ���[�h�t�@�C��
//==================================================================================
void CModeGame::LoadFile(char* FileName)
{
	char aWork[128];
	D3DXVECTOR3 PosWork;
	D3DXVECTOR3 SclWork;
	FILE* pFile = NULL;

	//  �t�@�C���̓ǂݍ���
	pFile = fopen(FileName, "r+");
	if (pFile == NULL)
	{
		//  �G���[�������ꍇ
		MessageBox(NULL, "�t�@�C�����ǂݍ��߂܂���ł����B", "�G���[���b�Z�[�W", MB_OK | MB_ICONWARNING);
		return;
	}
	else
	{
		while (1)
		{
			// �����ǂݍ���
			fscanf(pFile, "%s", &aWork);

			// �����`�F�b�N
			//  ���[�h�J�n
			if (strcmp(aWork, "LOAD_START") == 0) {
				continue;
			}

			// �v���C���[�Z�b�g
			else if (strcmp(aWork, "SET_PLAYER") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// �I�t�Z�b�g�I��
					if (strcmp(aWork, "END_PLAYER") == 0) {
						break;
					}
					else if (strcmp(aWork, "POS") == 0) {

						fscanf(pFile, "%f %f %f",
							&PosWork.x,
							&PosWork.y,
							&PosWork.z);
						m_pPlayer = CPlayer::Create(PosWork);
					}
				}
			}

			// �G�Z�b�g
			else if (strcmp(aWork, "SET_ENEMY") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// �I�t�Z�b�g�I��
					if (strcmp(aWork, "END_ENEMY") == 0) {
						break;
					}
					else if (strcmp(aWork, "POS") == 0) {

						fscanf(pFile, "%f %f %f",
							&PosWork.x,
							&PosWork.y,
							&PosWork.z);
						CEnemy::Create(PosWork);
					}
				}
			}

			// �u���b�N�Z�b�g
			else if (strcmp(aWork, "SET_BLOCK") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// �I�t�Z�b�g�I��
					if (strcmp(aWork, "END_BLOCK") == 0) {
						break;
					}
					else if (strcmp(aWork, "POS") == 0) {

						fscanf(pFile, "%f %f %f",
							&PosWork.x,
							&PosWork.y,
							&PosWork.z);
					}
					else if (strcmp(aWork, "SCL") == 0) {

						fscanf(pFile, "%f %f %f",
							&SclWork.x,
							&SclWork.y,
							&SclWork.z);
						CBlock::Create(PosWork, SclWork);
					}
				}
			}
			// �I��
			else if (strcmp(aWork, "END_LOAD") == 0) {
				break;
			}
		}
		//  �t�@�C�������
		fclose(pFile);
	}
}
