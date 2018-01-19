//=============================================================================
// �V�[������
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"

#include "manager.h"
#include "light.h"

//   �ÓI�����o�ϐ�
CScene *CScene::m_Top[OBJTYPE_MAX] = {};        // �V�[��
int CScene::m_NumScene = 0;                        // ����

//*************
// ���C������
//*************
CScene::CScene( int Priority ) :
	m_Prev(NULL),
	m_Next(NULL),
	m_Priority(NULL),
	m_ObjType(OBJTYPE_MAX),
	m_Pos(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_Scl(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_Color(D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f)),
	m_pTexture(NULL)
{
	if( m_Top[ Priority ] == NULL )      // NULL��������
	{
		m_Top[ Priority ] = this;        // ��������
		m_Priority = Priority;
		m_NumScene++;                        // �������J�E���g
	}
	else
	{
		CScene *scene = m_Top[ Priority ];
		while (scene->m_Next != NULL)
		{
			scene = scene->m_Next;
		}
		scene->m_Next = this;
		scene->m_Next->m_Priority = Priority;
		scene->m_Next->m_Prev = scene;
		m_NumScene++;                        // �������J�E���g
	}
}

CScene::~CScene()
{
}

//==================================================================================================================================================
//   �X�V����
//==================================================================================================================================================
void CScene::UpdateAll(void)
{
	// �ő吔�����[�v
	for( int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++ )
	{
		CScene *scene = m_Top[nCntPriority];
		while (scene != NULL)      // NULL��������
		{
			CScene *NextScene = scene->m_Next;
			scene->Update();
			scene = NextScene;
		}
	}
}

//==================================================================================================================================================
//   �`�揈��
//==================================================================================================================================================
void CScene::DrawAll(void)
{
	// �ő吔�����[�v
	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		CScene *scene = m_Top[nCntPriority];
		while (scene != NULL)      // NULL��������
		{
			CScene *NextScene = scene->m_Next;
			scene->Draw();
			scene = NextScene;
		}
	}
}
//==================================================================================================================================================
//   �`�揈��
//==================================================================================================================================================
void CScene::DrawDepthAll(void)
{
	// �ő吔�����[�v
	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		CScene *scene = m_Top[nCntPriority];
		while (scene != NULL)      // NULL��������
		{
			CScene *NextScene = scene->m_Next;
			scene->DrawDepth();
			scene = NextScene;
		}
	}
}
//==================================================================================================================================================
//   �`�揈��
//==================================================================================================================================================
void CScene::DrawStencilShadowAll(void)
{
	// �ő吔�����[�v
	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		CScene *scene = m_Top[nCntPriority];
		while (scene != NULL)      // NULL��������
		{
			CScene *NextScene = scene->m_Next;
			scene->DrawStencilShadow();
			scene = NextScene;
		}
	}
}

//==================================================================================================================================================
//   �`�揈��
//==================================================================================================================================================
void CScene::DrawGBufferAll(void)
{
	// �ő吔�����[�v
	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		CScene *scene = m_Top[nCntPriority];
		while (scene != NULL)      // NULL��������
		{
			CScene *NextScene = scene->m_Next;
			scene->DrawGBuffer();
			scene = NextScene;
		}
	}
}

//==================================================================================================================================================
//   �����[�X����
//==================================================================================================================================================
void CScene::ReleaseAll(int CntMax)
{
	// �ő吔�����[�v
	for( int nCntPriority = 0; nCntPriority < CntMax; nCntPriority++ )
	{
		CScene *scene = m_Top[nCntPriority];
		CScene *sceneNext;
		while (scene != NULL)      // NULL��������
		{
			sceneNext = scene->m_Next;
			scene->Uninit();
			scene = sceneNext;
		}
		m_Top[nCntPriority] = NULL;
	}
}

//==================================================================================================================================================
//   scene�̃����[�X����
//==================================================================================================================================================
void CScene::Release(void)
{
	CScene *scene = this;
	if (scene != NULL)      // NULL��������
	{
		if (scene->m_Prev != NULL)
		{
			// �O�̃V�[����NEXT�A�h���X�̑��
			scene->m_Prev->m_Next = scene->m_Next;
			// ��̃V�[����PREV�A�h���X�̑��
			if (scene->m_Next != NULL)
			{
				scene->m_Next->m_Prev = scene->m_Prev;
			}
		}
		else
		{
			// this�̓g�b�v�V�[���̏ꍇ�g�b�v�V�[����������
			if (scene->m_Next != NULL)
			{
				m_Top[m_Priority] = scene->m_Next;
				m_Top[m_Priority]->m_Prev = NULL;
			}
			else
			{
				m_Top[m_Priority] = NULL;
			}
		}
		delete scene;			// scene������
		m_NumScene--;			// �������J�E���g
	}
}
