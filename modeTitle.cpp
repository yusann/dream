//=============================================================================
// �^�C�g�����[�h
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "mode.h"
#include "modeTitle.h"
#include "modeGame.h"
#include "manager.h"
#include "input.h"
#include "inputKey.h"
#include "sound.h"
#include "camera.h"

#include "scene.h"
#include "scene2D.h"
#include "fade.h"
#include "object2D.h"
#include "shadowModel.h"

#include "sceneMesh.h"
#include "meshField.h"
#include "skyDome.h"

#include "sceneModelX.h"
#include "block.h"

//==================================================================================
//   ����������
//==================================================================================
void CModeTitle::Init(void)
{
	// �I�u�W�F�N�g�̔z�u
	CMeshField::Create();
	CSkyDome::Create(D3DXVECTOR3(0.0f, -2000.0f, 0.0f), 5000.0f, 18, 18);
	char aWork[128];
	D3DXVECTOR3 PosWork;
	D3DXVECTOR3 SclWork;
	FILE* pFile = NULL;

	//  �t�@�C���̓ǂݍ���
	pFile = fopen("data/objSave01.txt", "r+");
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
	CManager::GetSound()->Play(CSound::BGM_TITLE000);

	CCamera *pCamera = CManager::GetCamera();
	pCamera->SetLen(320.0f);
	pCamera->SetPosAt(D3DXVECTOR3(55.0f,55.0f,0.0f));

	CObject2D::Create(CObject2D::TYPE_BG_TITLE);
	CObject2D::Create(CObject2D::TYPE_BG_TITLE_SIBA);
	CObject2D::Create(CObject2D::TYPE_UI_PUSH);

	CShadowModel::Create();
}

//==================================================================================
//   �I������
//==================================================================================
void CModeTitle::Uninit(void)
{
	CManager::GetSound()->Stop();
	// �I�u�W�F�N�g�̔j��
	CScene::ReleaseAll(CScene::OBJTYPE_FADE);
}

//==================================================================================
//   �X�V����
//==================================================================================
void CModeTitle::Update(void)
{
	static float cameraRot = 0.0f;
	cameraRot += 0.002f;
	if (cameraRot >= 3.1415926f)
	{
		cameraRot = -3.1415926f;
	}
	CCamera *pCamera = CManager::GetCamera();
	pCamera->Update(cameraRot);
	if (CFade::GetFade() != CFade::FADE_NONE) return;
	if (CInputKey::InputGameStart())
	{
		CFade::SetFade(new CModeGame);
	}
}