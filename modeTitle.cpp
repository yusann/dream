//=============================================================================
// タイトルモード
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
//   初期化処理
//==================================================================================
void CModeTitle::Init(void)
{
	// オブジェクトの配置
	CMeshField::Create();
	CSkyDome::Create(D3DXVECTOR3(0.0f, -2000.0f, 0.0f), 5000.0f, 18, 18);
	char aWork[128];
	D3DXVECTOR3 PosWork;
	D3DXVECTOR3 SclWork;
	FILE* pFile = NULL;

	//  ファイルの読み込み
	pFile = fopen("data/objSave01.txt", "r+");
	if (pFile == NULL)
	{
		//  エラーだった場合
		MessageBox(NULL, "ファイルが読み込めませんでした。", "エラーメッセージ", MB_OK | MB_ICONWARNING);
		return;
	}
	else
	{
		while (1)
		{
			// 文字読み込み
			fscanf(pFile, "%s", &aWork);

			// 文字チェック
			//  ロード開始
			if (strcmp(aWork, "LOAD_START") == 0) {
				continue;
			}

			// ブロックセット
			else if (strcmp(aWork, "SET_BLOCK") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// オフセット終了
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
			// 終了
			else if (strcmp(aWork, "END_LOAD") == 0) {
				break;
			}
		}
		//  ファイルを閉じる
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
//   終了処理
//==================================================================================
void CModeTitle::Uninit(void)
{
	CManager::GetSound()->Stop();
	// オブジェクトの破棄
	CScene::ReleaseAll(CScene::OBJTYPE_FADE);
}

//==================================================================================
//   更新処理
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