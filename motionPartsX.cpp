//=============================================================================
// X���f���o�[�c��񃊃\�[�X
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "motionPartsX.h"

//   �ÓI�����o�ϐ��錾
std::unordered_map<char*, CMotionPartsX::MOTIONPARTSX>	CMotionPartsX::m_MotionPartsX;

// �e�N�X�`���p�X
char CMotionPartsX::m_FileName[][128] =
{
	"data/text100.txt",
	"data/text101.txt"
};

//*************
// ���C������
//*************
//=======================================================================================
//   ������
//=======================================================================================
void CMotionPartsX::Init()
{
	// �t�@�C���ǂݍ���
	for (int i = 0; i < TYPE_MAX; i++)
	{
		m_MotionPartsX[m_FileName[i]] = LoadFile(m_FileName[i]);
	}
}

//=======================================================================================
//   �I������
//=======================================================================================
void CMotionPartsX::Uninit()
{
	for (auto CntPartsX = m_MotionPartsX.begin(); CntPartsX != m_MotionPartsX.end(); CntPartsX++)
	{
		// ���[�V�����j��
		for (auto CntMotion = (*CntPartsX).second.Motion.begin(); CntMotion != (*CntPartsX).second.Motion.end(); CntMotion++)
		{
			for (auto CntFrame = (*CntMotion)->KeyFrame.begin(); CntFrame != (*CntMotion)->KeyFrame.end(); CntFrame++)
			{
				(*CntFrame)->Key.clear();
			}
			(*CntMotion)->KeyFrame.clear();
			(*CntMotion)->Collision.clear();
			(*CntMotion)->Sound.clear();
		}
		(*CntPartsX).second.Motion.clear();

		// �p�[�c�j��
		(*CntPartsX).second.Part.clear();

		// �e�j��
		delete (*CntPartsX).second.pShadow;
		(*CntPartsX).second.pShadow = NULL;
	}
	m_MotionPartsX.clear();
}

//=======================================================================================
//   �t�@�C���ǂݍ��ݏ���
//=======================================================================================
CMotionPartsX::MOTIONPARTSX CMotionPartsX::LoadFile(char *FileName)
{
	MOTIONPARTSX MotionParts;
	char aWork[128];
	int CntParts = -1;
	int CntMotion = -1;
	int CntKeyFrame = -1;
	int CntKey = -1;
	int CntCollision = -1;
	int CntSound = -1;
	FILE* pFile = NULL;
	MotionParts.pShadow = new SHADOW;

	//  �t�@�C���̓ǂݍ���
	pFile = fopen(FileName, "r+");
	if (pFile == NULL)
	{
		//  �G���[�������ꍇ
		MessageBox(NULL, "�t�@�C�����ǂݍ��߂܂���ł����B", "�G���[���b�Z�[�W", MB_OK | MB_ICONWARNING);
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

			// �e���
			else if (strcmp(aWork, "SET_SHADOW") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// �I�t�Z�b�g�I��
					if (strcmp(aWork, "END_SHADOW") == 0) {
						break;
					}
					else if (strcmp(aWork, "NUM_X") == 0) {
						fscanf(pFile, "%d", &MotionParts.pShadow->NumX);
					}
					else if (strcmp(aWork, "NUM_Y") == 0) {
						fscanf(pFile, "%d", &MotionParts.pShadow->NumY);
					}
					else if (strcmp(aWork, "RADIUS") == 0) {
						fscanf(pFile, "%f", &MotionParts.pShadow->Radius);
					}
					// �X�P�[��
					else if (strcmp(aWork, "SCL") == 0) {
						fscanf(pFile, "%f %f %f",
							&MotionParts.pShadow->Scl.x,
							&MotionParts.pShadow->Scl.y,
							&MotionParts.pShadow->Scl.z);
					}
				}
			}

			// �I�t�Z�b�g���
			else if (strcmp(aWork, "SET_OFFSET") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// �I�t�Z�b�g�I��
					if (strcmp(aWork, "END_OFFSET") == 0) {
						break;
					}
					else if (strcmp(aWork, "FILENAME") == 0) {
						// ���I�m��
						MotionParts.Part.push_back(new PART);
						CntParts++;

						char Path[64];
						fscanf(pFile, "%s", &Path[0]);
						MotionParts.Part[CntParts]->FilePath = Path;
					}
					else if (strcmp(aWork, "PARENT") == 0) {
						fscanf(pFile, "%d", &MotionParts.Part[CntParts]->Parent);
					}
					// ���W
					else if (strcmp(aWork, "POS") == 0) {
						fscanf(pFile, "%f %f %f",
							&MotionParts.Part[CntParts]->OffSetPos.x,
							&MotionParts.Part[CntParts]->OffSetPos.y,
							&MotionParts.Part[CntParts]->OffSetPos.z);
					}
					// ��]
					else if (strcmp(aWork, "ROT") == 0) {
						fscanf(pFile, "%f %f %f",
							&MotionParts.Part[CntParts]->OffSetRot.x,
							&MotionParts.Part[CntParts]->OffSetRot.y,
							&MotionParts.Part[CntParts]->OffSetRot.z);
					}
					// �X�P�[��
					else if (strcmp(aWork, "SCL") == 0) {
						fscanf(pFile, "%f %f %f",
							&MotionParts.Part[CntParts]->OffSetScl.x,
							&MotionParts.Part[CntParts]->OffSetScl.y,
							&MotionParts.Part[CntParts]->OffSetScl.z);

						//  x�t�@�C���̓ǂݍ���
						LoadModel(MotionParts.Part[CntParts]);
					}
				}
			}
			// ���[�V�������
			else if (strcmp(aWork, "SET_MOTION") == 0) {

				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// ���[�v�t���O
					if (strcmp(aWork, "SET_KEY_FRAME") == 0) {

						MotionParts.Motion.push_back(new MOTION);
						CntMotion++;
						CntKeyFrame = -1;
					}
					// �T�E���h
					else if (strcmp(aWork, "SET_SOUND") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aWork);
							if (strcmp(aWork, "ID") == 0) {
								MotionParts.Motion[CntMotion]->Sound.push_back(new SOUND);
								CntSound++;
								fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->Sound[CntSound]->ID);
							}
							else if (strcmp(aWork, "FRAME") == 0) {
								fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->Sound[CntSound]->Frame);
							}
							else if (strcmp(aWork, "END_SOUND") == 0) {
								CntSound = -1;
								break;
							}
						}
					}
					// �����蔻��
					else if (strcmp(aWork, "SET_COLLISION") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aWork);
							// 1�̃��[�V�����ǂݍ��ݏI��
							if (strcmp(aWork, "PARTS") == 0) {
								
								MotionParts.Motion[CntMotion]->Collision.push_back(new COLLISION);
								CntCollision++;
								fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->Collision[CntCollision]->PartID);
							}
							else if (strcmp(aWork, "POS") == 0) {
								fscanf(pFile, "%f %f %f\n", &MotionParts.Motion[CntMotion]->Collision[CntCollision]->Pos.x,
									&MotionParts.Motion[CntMotion]->Collision[CntCollision]->Pos.y,
									&MotionParts.Motion[CntMotion]->Collision[CntCollision]->Pos.z);
							}
							else if (strcmp(aWork, "SCL") == 0) {
								fscanf(pFile, "%f", &MotionParts.Motion[CntMotion]->Collision[CntCollision]->Scl);
							}
							else if (strcmp(aWork, "START") == 0) {
								fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->Collision[CntCollision]->StartFrame);
							}
							else if (strcmp(aWork, "END") == 0) {
								fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->Collision[CntCollision]->EndFrame);
							}
							else if (strcmp(aWork, "END_COLLISION") == 0) {
								CntCollision = -1;
								break;
							}
						}
					}
					// �t���[����
					else if (strcmp(aWork, "FRAME") == 0)
					{
						// �L�[�t���[���J�E���g
						CntKeyFrame++;
						// �L�[�J�E���^�̏�����
						CntKey = -1;

						// �m��
						MotionParts.Motion[CntMotion]->KeyFrame.push_back(new KEY_FRAME);
						fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Frame);
					}
					// ���W
					else if (strcmp(aWork, "POS") == 0)
					{
						// �m��
						MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key.push_back(new KEY);
						// �L�[�J�E���g
						CntKey++;

						fscanf(pFile, "%f %f %f\n", &MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Pos.x,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Pos.y,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Pos.z);
					}
					// ��]
					else if (strcmp(aWork, "ROT") == 0)
					{
						fscanf(pFile, "%f %f %f\n", &MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Rot.x,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Rot.y,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Rot.z);
					}
					// �X�P�[��
					else if (strcmp(aWork, "SCL") == 0)
					{
						fscanf(pFile, "%f %f %f\n", &MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Scl.x,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Scl.y,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Scl.z);
					}
					// 1�̃��[�V�����ǂݍ��ݏI��
					else if (strcmp(aWork, "END_MOTION") == 0) {
						break;
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
	return MotionParts;
}

//=======================================================================================
//   ���f���ǂݍ��ݏ���
//=======================================================================================
void CMotionPartsX::LoadModel(PART *pPart)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;                // �G���[�`�F�b�N�̂���NULL������
	pDevice = CManager::GetRenderer()->GetDevice();                           // �f�o�C�X�̃|�C���^
	if (pDevice == NULL)                            // �G���[�`�F�b�N
	{
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}
	//  x�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(pPart->FilePath.c_str(),				//  �t�@�C����
		D3DXMESH_MANAGED,															//  �I�v�V����
		pDevice,																	//  �f�o�C�X
		NULL,
		&pPart->pBuffMat,		//  �}�e���A�����
		NULL,
		&pPart->NumMat,			//  �}�e���A����
		&pPart->pMesh)))			//  ���b�V�����
	{
		MessageBox(NULL, "x�t�@�C������肭�擾�o���܂���ł����B", "�G���[���b�Z�[�W", MB_OK);
		return;
	}

	//  �e�N�X�`�����擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pPart->pBuffMat->GetBufferPointer();
	pPart->pTexture = new LPDIRECT3DTEXTURE9[(int)pPart->NumMat];

	//  �}�e���A���̐����̃��[�v
	for (int j = 0; j < (int)pPart->NumMat; ++j)
	{
		//  �e�N�X�`���|�C���^������ꍇ
		if (pMat[j].pTextureFilename != NULL)
		{
			//  �e�N�X�`���̓ǂݍ���( �n�[�h�f�B�X�N���� )	
			if (FAILED(D3DXCreateTextureFromFile(pDevice,	//  �f�o�C�X
				pMat[j].pTextureFilename,					//  �e�N�X�`����
				&pPart->pTexture[j])))		//  �Ăэ��ޏꏊ
			{
				//  �G���[�������ꍇ
				MessageBox(NULL, "�e�N�X�`���C���^�t�F�[�X�̃|�C���^������܂���B", "�G���[���b�Z�[�W", MB_OK | MB_ICONWARNING);
				// �Ȃ����ɔ����e�N�X�`������
				pPart->pTexture[j] = CTexture::GetTexture((int)CTexture::TEXTYPE_WHITE);
			}
		}
		else
		{
			// �Ȃ����ɔ����e�N�X�`������
			pPart->pTexture[j] = CTexture::GetTexture((int)CTexture::TEXTYPE_WHITE);
		}
	}
}