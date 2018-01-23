//=============================================================================
// 2D�I�u�W�F�N�g
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "GBuffer.h"
#include "UIBase.h"
#include "UITitle.h"
#include "texture.h"
#include "equation.h"

//=======================================================================================
// �쐬����
//=======================================================================================
CUITitle *CUITitle::Create(){
	CUITitle *pScene2D;                            // �ϐ��錾
	pScene2D = new CUITitle;                       // ���I�m��
	pScene2D->Init();                            // ������
	return pScene2D;                             // �l��Ԃ�
}

//=======================================================================================
//   ����������
//=======================================================================================
void CUITitle::Init()
{
	m_TexID = 0;
	MakeVex();
}

//=======================================================================================
//   �I������
//=======================================================================================
void CUITitle::Uninit()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pTexture);
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CUITitle::Update()
{
	ImGui::DragFloat2("UI Pos", &m_Pos[0]);
	ImGui::DragFloat2("UI Scl", &m_Scl[0]);
	ImGui::DragFloat("UI Rot", &m_Rot, 0.01f);

	ImGui::DragFloat2("UI Pos Point RT", &m_PosPoint[0][0]);
	ImGui::DragFloat2("UI Pos Point RB", &m_PosPoint[1][0]);
	ImGui::DragFloat2("UI Pos Point LT", &m_PosPoint[2][0]);
	ImGui::DragFloat2("UI Pos Point LB", &m_PosPoint[3][0]);

	ImGui::InputInt("TexID", &m_TexID);
	CEquation::Min(0.0f, m_TexID, 0.0f);
	m_pTexture = CTexture::GetTexture(m_TexID);
	SetVex();
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CUITitle::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�̃f�N�����[�V�����̐ݒ�
	CVertexDecl::SetTex2D(pDevice, m_pVB);

	// �`�撼�O�Ƀe�N�X�`�����Z�b�g�i�e�N�X�`���̐ݒ�j
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,        // �v���~�e�B�u�̎��
		0,                          // �I�t�Z�b�g�i���_���j
		NUM_POLYGON);              // �v���~�e�B�u�̐��i�|���S���̐��j
}
