//=============================================================================
// �e
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "shadowModel.h"
#include "light.h"

int CShadowModel::m_MaxID = 0;

CShadowModel::CShadowModel() : CScene2D(CScene::OBJTYPE_SHADOW)
{
}

CShadowModel::CShadowModel(const LPD3DXMESH pMesh) :
	CScene2D(CScene::OBJTYPE_SHADOW),
	m_pMesh(pMesh)
{
	m_Shadow.iNumVertex = 0;
	m_Shadow.pVertex = NULL;
	D3DXMatrixIdentity(&m_Matrix);                       // ���[���h�̒��g��������
}

CShadowModel::~CShadowModel()
{
	if (m_Shadow.pVertex != NULL)
	{
		delete[] m_Shadow.pVertex;
		m_Shadow.pVertex = NULL;
	}
}

//==============================================================================
//  ��������
//==============================================================================
CShadowModel *CShadowModel::Create(const LPD3DXMESH pMesh)
{
	CShadowModel *pSceneMD;                            // �ϐ��錾
	pSceneMD = new CShadowModel(pMesh);
	pSceneMD->Init();                            // ������
	return pSceneMD;                             // �l��Ԃ�
}

//==============================================================================
//  ����������
//==============================================================================
void CShadowModel::Init( void )
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_Color = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	m_pTexture = NULL;
	m_MaxID++;

	CScene2D::Init();

	// �^�C�v�̑��
	CScene::SetObjType(CScene::OBJTYPE_SHADOW);
}

//==============================================================================
//  �I������
//==============================================================================
void CShadowModel::Uninit( void )
{
	if (m_Shadow.pVertex != NULL)
	{
		delete[] m_Shadow.pVertex;
		m_Shadow.pVertex = NULL;
	}
	m_MaxID--;
	CScene2D::Uninit();
}

//==============================================================================
//  �X�V����
//==============================================================================
void CShadowModel::Update( void )
{
	D3DXVECTOR3	light;
	D3DXMATRIX	shadow;
	D3DXVECTOR3 lightPos = CManager::GetLight()->GetPos();
	D3DXMatrixInverse(&shadow, NULL, &m_Matrix);
	D3DXVec3TransformCoord(&light, &lightPos, &shadow);
	BuildShadowVolume(m_pMesh, light);
}

//==============================================================================
//  �`�揈��
//==============================================================================
void CShadowModel::Draw( void )
{
	/*
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �X�e���V���̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);			// �X�e���V���L����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// Z�o�b�t�@�������܂Ȃ�
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);			// �J���[�������܂Ȃ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0x000000ff);		// �X�e���V���}�X�N

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);	// ��r�֐��i�K�����i�j
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);				// �Q�ƒl
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Z�o�b�t�@�ň��������������i�������Ȃ��j
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// �����_�����������i�������Ȃ��j

	// �V���h�E�{�����[���̕\���X�e���V���ɕ`��
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);		// �����ɒʂ������i+1�j
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	pDevice->SetFVF(D3DFVF_XYZ);
	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_Shadow.iNumVertex / 3,
		*m_Shadow.pVertex, sizeof(D3DXVECTOR3));

	// �V���h�E�{�����[���̗����X�e���V���ɕ`��
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);		// �����ɒʂ������i-1�j
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	pDevice->SetFVF(D3DFVF_XYZ);
	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_Shadow.iNumVertex / 3,
		*m_Shadow.pVertex, sizeof(D3DXVECTOR3));

	// �Ō�`�悷��I�u�W�F�̃`�F�b�N
	static int ID = 0;
	ID++;
	if (ID == m_MaxID)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);			// �J���[�������މ\
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);				// �Q�ƒl
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);	// ��r�֐��i�ȉ��Ȃ�j

		CScene2D::Draw();

		ID = 0;

		// �X�e���V�����N���A
		pDevice->Clear(0, NULL,
			D3DCLEAR_STENCIL,								// �X�e���V��
			D3DCOLOR_RGBA(0, 0, 0, 0),				// �������F
			1.0f,											// 0~1�i0�͎�O�A1�͉����j
			0);

	}
	// �`��X�e�[�^�X�̕��A
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	*/
}

//-----------------------------------------------------------------------------
// ���b�V���ƌ����ւ̃x�N�g�����V���h�E�{�����[���𐶐�
//-----------------------------------------------------------------------------
HRESULT CShadowModel::BuildShadowVolume( LPD3DXMESH pMesh, D3DXVECTOR3 vLight)
{
	BYTE*	pVertex;
	WORD*	pIndex;

	// ���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̎擾
	pMesh->LockVertexBuffer(0, (LPVOID*)&pVertex);
	pMesh->LockIndexBuffer(0, (LPVOID*)&pIndex);
	DWORD	dwNumFace = pMesh->GetNumFaces();
	DWORD	dwStride = pMesh->GetNumBytesPerVertex();

	// ���[�N�p�G�b�W���X�g�m��
	WORD*	pEdge = new WORD[dwNumFace * 6];
	if (pEdge == NULL) {
		pMesh->UnlockIndexBuffer();
		pMesh->UnlockVertexBuffer();
		return E_OUTOFMEMORY;
	}

	DWORD	dwNumEdge = 0;
	DWORD	i;

	// �����������Ă���ʂ�����
	for (i = 0; i < dwNumFace; i++) {
		WORD	wFace0 = pIndex[i * 3 + 0];
		WORD	wFace1 = pIndex[i * 3 + 1];
		WORD	wFace2 = pIndex[i * 3 + 2];
		D3DXVECTOR3&	v0 = *(D3DXVECTOR3*)&pVertex[wFace0 * dwStride];
		D3DXVECTOR3&	v1 = *(D3DXVECTOR3*)&pVertex[wFace1 * dwStride];
		D3DXVECTOR3&	v2 = *(D3DXVECTOR3*)&pVertex[wFace2 * dwStride];
		// �����������Ă���ʂ�?
		D3DXVECTOR3	vCross1(v1 - v0);
		D3DXVECTOR3	vCross2(v2 - v0);
		D3DXVECTOR3	vNormal;
		D3DXVec3Cross(&vNormal, &vCross1, &vCross2);
		if (D3DXVec3Dot(&vNormal, &vLight) <= 0.0f) {
			// �G�b�W���X�g��3�ӂ�ǉ�
			AddEdge(pEdge, &dwNumEdge, wFace0, wFace1);
			AddEdge(pEdge, &dwNumEdge, wFace1, wFace2);
			AddEdge(pEdge, &dwNumEdge, wFace2, wFace0);
		}
	}

	// �V���h�E�{�����[���̑��ʂ�ǉ�
	if (m_Shadow.pVertex != NULL)
	{
		delete[] m_Shadow.pVertex;
		m_Shadow.pVertex = NULL;
	}
	m_Shadow.pVertex = new D3DXVECTOR3[dwNumEdge * 6];
	m_Shadow.iNumVertex = 0;
	for (i = 0; i < dwNumEdge; i++) {
		D3DXVECTOR3&	v1 = *(D3DXVECTOR3*)&pVertex[pEdge[i * 2 + 0] * dwStride];
		D3DXVECTOR3&	v2 = *(D3DXVECTOR3*)&pVertex[pEdge[i * 2 + 1] * dwStride];
		D3DXVECTOR3		v3 = v1 - vLight;
		D3DXVECTOR3		v4 = v2 - vLight;

		// ��`�̒ǉ�
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v1;
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v2;
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v3;
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v2;
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v4;
		m_Shadow.pVertex[m_Shadow.iNumVertex++] = v3;
	}

	// ���[�N�p�G�b�W���X�g���
	delete[] pEdge;

	// ���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̉��
	pMesh->UnlockIndexBuffer();
	pMesh->UnlockVertexBuffer();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �G�b�W���X�g�ւ̒ǉ�
//-----------------------------------------------------------------------------
void CShadowModel::AddEdge(WORD* pEdge, DWORD* pdwNumEdge, WORD v0, WORD v1)
{
	// �O�p�`�Ԃ̋��L�G�b�W�̍폜�i2�x�ڂ̓o�^���j
	for (DWORD i = 0; i < *pdwNumEdge; ++i) {
		if ((pEdge[i * 2 + 0] == v0 && pEdge[i * 2 + 1] == v1) ||
			(pEdge[i * 2 + 0] == v1 && pEdge[i * 2 + 1] == v0)) {
			// �����̃G�b�W�ŏ㏑�����ď���
			if (*pdwNumEdge > 1) {
				pEdge[i * 2 + 0] = pEdge[(*pdwNumEdge - 1) * 2 + 0];
				pEdge[i * 2 + 1] = pEdge[(*pdwNumEdge - 1) * 2 + 1];
			}
			--*pdwNumEdge;
			return;
		}
	}
	// �G�b�W���X�g�֒ǉ�
	pEdge[*pdwNumEdge * 2 + 0] = v0;
	pEdge[*pdwNumEdge * 2 + 1] = v1;
	++*pdwNumEdge;
}