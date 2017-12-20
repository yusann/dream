//=============================================================================
// �p�[�c���f������
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "shadowSphere.h"
#include "meshSphere.h"
#include "sound.h"
#include "equation.h"
#include "shaderManager.h"

//*************
// ���C������
//*************
CSceneMotionPartsX::CSceneMotionPartsX(int Priority) :CScene(Priority),
m_MotionID(0),
m_Frame(0),
m_Key(0),
m_MotionFrame(0),
m_Blend(false),
m_LastKye(false),
m_pShadow(NULL)
{
	// �����o�ϐ��̏�����
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

CSceneMotionPartsX::~CSceneMotionPartsX()
{
}

//=======================================================================================
//   ����������
//=======================================================================================
void CSceneMotionPartsX::Init()
{
	// �f�[�^���
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++)
	{
		m_Model.push_back(new MODEL);
		m_BlendData.push_back(new VECTR3);
		// �K�w����
		if (i == 0)
		{
			m_Model[i]->pParent = NULL;
		}
		else
		{
			m_Model[i]->pParent = m_Model[m_pMotionPartsX->Part[i]->Parent];
		}

		// �f�[�^���
		m_Model[i]->Pos = m_pMotionPartsX->Part[i]->OffSetPos + m_pMotionPartsX->Motion[0]->KeyFrame[0]->Key[i]->Pos;
		m_Model[i]->Rot = m_pMotionPartsX->Part[i]->OffSetRot + m_pMotionPartsX->Motion[0]->KeyFrame[0]->Key[i]->Rot;
		m_Model[i]->Scl = m_pMotionPartsX->Part[i]->OffSetScl + m_pMotionPartsX->Motion[0]->KeyFrame[0]->Key[i]->Scl;

		m_BlendData[i]->Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_BlendData[i]->Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_BlendData[i]->Scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// �����蔻��Z�b�g
	for (int i = 0; i < (signed)m_pMotionPartsX->Motion.size(); i++)
	{
		for (int j = 0; j < (signed)m_pMotionPartsX->Motion[i]->Collision.size(); j++)
		{
			m_Model[i]->Collision.push_back(new COLLISION_SPHERE);
			m_Model[i]->Collision[j]->Pos = m_pMotionPartsX->Motion[i]->Collision[j]->Pos;
			m_Model[i]->Collision[j]->Scl = m_pMotionPartsX->Motion[i]->Collision[j]->Scl;
#ifdef _DEBUG
			m_Model[i]->Collision[j]->Sphere = CMeshSphere::Create(m_Model[i]->Collision[j]->Pos, m_Model[i]->Collision[j]->Scl, 10, 10, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f));
#endif
		}
	}

	// �e�Z�b�g
	m_pShadow = CShadowSphere::Create(m_pMotionPartsX->pShadow->NumX,
								m_pMotionPartsX->pShadow->NumY,
								m_pMotionPartsX->pShadow->Radius,
								m_pMotionPartsX->pShadow->Scl);
}

//=======================================================================================
//   �I������
//=======================================================================================
void CSceneMotionPartsX::Uninit()
{
	// �e�j��
	SAFE_UNINIT(m_pShadow);

	// ���f���j��
	m_Model.clear();
	m_BlendData.clear();
	CScene::Release();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CSceneMotionPartsX::Update()
{
	CEquation::SetMatrix(&m_Matrix, m_Pos, m_Rot, m_Scl);

	// �e�X�V
	m_pShadow->Update(m_Pos);

	// ���[�v���Ȃ����[�V��������
	if (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame <= 0)
	{
		UpdateLastKeyFrame();
		return;
	}

	// �t���[���X�V
	m_Frame++;

	if (!m_Blend) { UpdateMotion(); }
	else { UpdateBlendMotion(); }
}
// �}�g���N�X�Z�b�g����
void CSceneMotionPartsX::UpdateMotion()
{
	// ���̃L�[�t���[��
	int NextKey = m_Key + 1;

	// ���̃L�[�t���[���̃N���A
	if (NextKey >= (signed)m_pMotionPartsX->Motion[m_MotionID]->KeyFrame.size())
		NextKey = 0;

	// �p�[�c�������[�v���ĕ�ԏ���
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++)
	{
		float Frame = (float)m_Frame / (float)m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame;

		// ��ԗʂōX�V
		m_Model[i]->Pos = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Pos * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[NextKey]->Key[i]->Pos * Frame) +
			m_pMotionPartsX->Part[i]->OffSetPos;
		m_Model[i]->Rot = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Rot * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[NextKey]->Key[i]->Rot * Frame) +
			m_pMotionPartsX->Part[i]->OffSetRot;
		m_Model[i]->Scl = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Scl * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[NextKey]->Key[i]->Scl * Frame) +
			m_pMotionPartsX->Part[i]->OffSetScl;

		CEquation::SetMatrix(&m_Model[i]->Matrix, m_Model[i]->Pos, m_Model[i]->Rot, m_Model[i]->Scl);

		if (m_pMotionPartsX->Part[i]->Parent == -1)
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Matrix);   // ���[���h���W�̑��
		}
		else
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Model[i]->pParent->Matrix);   // ���[���h���W�̑��
		}
	}

	// �t���[�����`�F�b�N
	if (m_Frame > m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame)
	{
		// �t���[�����N���A
		m_Frame = 0;

		// ���̃L�[�t���[����
		m_Key++;

		// ���[�v���[�V����
		if (m_Key >= (signed)m_pMotionPartsX->Motion[m_MotionID]->KeyFrame.size())
		{
			m_Key = 0;
		}
	}

	// ���[�V�����t���[���v�Z
	m_MotionFrame = 0;
	for (int i = 0; i < m_Key; i++)
	{
		m_MotionFrame += m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[i]->Frame;
	}
	m_MotionFrame += m_Frame;

	// �����蔻��ۊǗp�̏�����
	if (!m_CollisionSphere.empty()) { m_CollisionSphere.clear(); }

	// ������͈̓Z�b�g
	for (int i = 0; i < (signed)m_pMotionPartsX->Motion[m_MotionID]->Collision.size(); i++)
	{
		if (m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->StartFrame > m_MotionFrame) { continue; }
		if (m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->EndFrame < m_MotionFrame) { continue; }
		D3DXVec3TransformCoord(&m_Model[m_MotionID]->Collision[i]->Pos,
			&m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->Pos,
			&m_Model[m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->PartID]->Matrix);
#ifdef _DEBUG
		m_Model[m_MotionID]->Collision[i]->Sphere->Update(m_Model[m_MotionID]->Collision[i]->Pos,
			m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->Scl);
#endif
		m_CollisionSphere.push_back(m_Model[m_MotionID]->Collision[i]);
	}

	// ���ʉ��v���C
	for (int i = 0; i < (signed)m_pMotionPartsX->Motion[m_MotionID]->Sound.size(); i++)
	{
		static int ji = 0;
		if (m_MotionFrame == m_pMotionPartsX->Motion[m_MotionID]->Sound[i]->Frame)
		{
			CManager::GetSound()->Play((CSound::SOUND_LABEL)m_pMotionPartsX->Motion[m_MotionID]->Sound[i]->ID);
		}
	}
}
// �u�����h���[�V�����̃}�g���N�X�Z�b�g����
void CSceneMotionPartsX::UpdateBlendMotion()
{
	// �p�[�c�������[�v���ĕ�ԏ���
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++)
	{
		float Frame = (float)m_Frame / (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame*0.5f);

		// ��ԗʂōX�V
		m_Model[i]->Pos = (m_BlendData[i]->Pos * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Pos * Frame) +
			m_pMotionPartsX->Part[i]->OffSetPos;
		m_Model[i]->Rot = (m_BlendData[i]->Rot * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Rot * Frame) +
			m_pMotionPartsX->Part[i]->OffSetRot;
		m_Model[i]->Scl = (m_BlendData[i]->Scl * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Scl * Frame) +
			m_pMotionPartsX->Part[i]->OffSetScl;

		CEquation::SetMatrix(&m_Model[i]->Matrix, m_Model[i]->Pos, m_Model[i]->Rot, m_Model[i]->Scl);

		if (m_pMotionPartsX->Part[i]->Parent == -1)
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Matrix);   // ���[���h���W�̑��
		}
		else
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Model[i]->pParent->Matrix);   // ���[���h���W�̑��
		}
	}

	// �t���[�����`�F�b�N
	if (m_Frame > m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame*0.5f)
	{
		// �t���[�����N���A
		m_Frame = 0;

		// ���̃L�[�t���[����
		m_Key = 0;

		m_Blend = false;
	}
}
// �Ō�̃L�[�t���[���̍X�V����
void CSceneMotionPartsX::UpdateLastKeyFrame()
{
	m_LastKye = true;

	// �p�[�c�������[�v���ĕ�ԏ���
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++)
	{
		// ��ԗʂōX�V
		m_Model[i]->Pos = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Pos) +
			m_pMotionPartsX->Part[i]->OffSetPos;
		m_Model[i]->Rot = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Rot) +
			m_pMotionPartsX->Part[i]->OffSetRot;
		m_Model[i]->Scl = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Scl) +
			m_pMotionPartsX->Part[i]->OffSetScl;

		CEquation::SetMatrix(&m_Model[i]->Matrix, m_Model[i]->Pos, m_Model[i]->Rot, m_Model[i]->Scl);

		if (m_pMotionPartsX->Part[i]->Parent == -1)
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Matrix);   // ���[���h���W�̑��
		}
		else
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Model[i]->pParent->Matrix);   // ���[���h���W�̑��
		}
	}

	// �t���[�����`�F�b�N
	if (m_Frame > m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame)
	{
		// �t���[�����N���A
		m_Frame = 0;

		// ���̃L�[�t���[����
		m_Key++;

		// ���[�v���[�V����
		if (m_Key >= (signed)m_pMotionPartsX->Motion[m_MotionID]->KeyFrame.size())
		{
			m_Key = 0;
		}
	}

	// ���[�V�����t���[���v�Z
	m_MotionFrame = 0;
	for (int i = 0; i < m_Key; i++)
	{
		m_MotionFrame += m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[i]->Frame;
	}
	m_MotionFrame += m_Frame;

	// �����蔻��ۊǗp�̏�����
	if (!m_CollisionSphere.empty()) { m_CollisionSphere.clear(); }

	// ������͈̓Z�b�g
	for (int i = 0; i < (signed)m_pMotionPartsX->Motion[m_MotionID]->Collision.size(); i++)
	{
		if (m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->StartFrame > m_MotionFrame) { continue; }
		if (m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->EndFrame < m_MotionFrame) { continue; }
		D3DXVec3TransformCoord(&m_Model[m_MotionID]->Collision[i]->Pos,
			&m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->Pos,
			&m_Model[m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->PartID]->Matrix);
#ifdef _DEBUG
		m_Model[m_MotionID]->Collision[i]->Sphere->Update(m_Model[m_MotionID]->Collision[i]->Pos,
			m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->Scl);
#endif
		m_CollisionSphere.push_back(m_Model[m_MotionID]->Collision[i]);
	}
}

//=======================================================================================
//   �`�揈��
//=======================================================================================
void CSceneMotionPartsX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = NULL;                // �G���[�`�F�b�N�̂���NULL������
	pDevice = CManager::GetRenderer()->GetDevice();                           // �f�o�C�X�̃|�C���^���擾

	if (pDevice == NULL)                            // �G���[�`�F�b�N
	{
		MessageBox(NULL, "Init��pDevece��NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}
	// �e�`��
	m_pShadow->Draw();

	// �֊s
	// �V�F�[�_�̎擾
	CShaderManga *pShaderManga = (CShaderManga*)CShaderManager::GetShader(CShaderManager::TYPE_ANIME);
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++) {

		// NULL�`�F�b�N
		if (m_pMotionPartsX->Part[i]->pBuffMat == NULL) { return; }
		D3DXMATERIAL*	pMat = NULL;					//  �}�e���A��

														// ���[���h���Z�b�g
		pDevice->SetTransform(D3DTS_WORLD, &m_Model[i]->Matrix);

		D3DMATERIAL9 matDef;
		pDevice->GetMaterial(&matDef);                 // ���݃f�o�C�X�ɐݒ肳��Ă�A�e���A�������擾

		pMat = (D3DXMATERIAL*)m_pMotionPartsX->Part[i]->pBuffMat->GetBufferPointer();

		// ���_�V�F�[�_�̑��
		pShaderManga->SetVertexInfo(m_Model[i]->Matrix);

		for (int j = 0; j < (int)m_pMotionPartsX->Part[i]->NumMat; j++)
		{
			pShaderManga->Begin(2);
			// ���b�V���̕`��
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
			m_pMotionPartsX->Part[i]->pMesh->DrawSubset(j);
			pShaderManga->End();
		}
	}


	// �S�p�[�c�����[�v
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++) {

	// NULL�`�F�b�N
	if (m_pMotionPartsX->Part[i]->pBuffMat == NULL) { return; }
		D3DXMATERIAL*	pMat = NULL;					//  �}�e���A��

		// ���[���h���Z�b�g
		pDevice->SetTransform(D3DTS_WORLD, &m_Model[i]->Matrix);

		D3DMATERIAL9 matDef;
		pDevice->GetMaterial(&matDef);                 // ���݃f�o�C�X�ɐݒ肳��Ă�A�e���A�������擾

		pMat = (D3DXMATERIAL*)m_pMotionPartsX->Part[i]->pBuffMat->GetBufferPointer();

		// �V�F�[�_�̎擾
		pShaderManga->SetVertexInfo(m_Model[i]->Matrix);

		for (int j = 0; j < (int)m_pMotionPartsX->Part[i]->NumMat; j++)
		{
			if (m_pMotionPartsX->Part[i]->pTexture[j] != NULL)
			{
				// �s�N�Z���V�F�[�_�̐ݒ�
				pShaderManga->SetPixelInfo(pMat[j].MatD3D.Diffuse, m_pMotionPartsX->Part[i]->pTexture[j]);
				pShaderManga->Begin();
			}
			else
			{
				// �s�N�Z���V�F�[�_�̐ݒ�
				pShaderManga->SetPixelInfo(pMat[j].MatD3D.Diffuse, NULL);
				pShaderManga->Begin(1);
			}
			// ���b�V���̕`��
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			m_pMotionPartsX->Part[i]->pMesh->DrawSubset(j);
			pShaderManga->End();
		}
	}
}

void CSceneMotionPartsX::SetMotion(int MotionID)
{
	if (m_MotionID == MotionID)
		return;

	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++) {
		m_BlendData[i]->Pos = m_Model[i]->Pos - m_pMotionPartsX->Part[i]->OffSetPos;
		m_BlendData[i]->Rot = m_Model[i]->Rot - m_pMotionPartsX->Part[i]->OffSetRot;
		m_BlendData[i]->Scl = m_Model[i]->Scl - m_pMotionPartsX->Part[i]->OffSetScl;
	}
	m_Blend = true;
	m_MotionID = MotionID;
	m_Key = 0;
	m_Frame = 0;
	m_LastKye = false;
}