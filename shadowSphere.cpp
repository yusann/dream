//=============================================================================
// �e
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "shadowSphere.h"

//*************
// ���C������
//*************
CShadowSphere::CShadowSphere() :
m_pVB_POS(NULL),
m_pVB_NORMAL(NULL),
m_pVB_COLOR(NULL),
m_pVB_TEX(NULL) {}
CShadowSphere::~CShadowSphere() {}

// �ϐ�������
CShadowSphere::CShadowSphere(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXCOLOR color, D3DXVECTOR3 pos)
	: m_SpherePos(pos),
	m_SphereScl(scl),
	m_SphereRadius(radius),
	m_Color(color),
	m_SphereNumX(numBlockX),
	m_SphereNumY(numBlockY),
	m_pVB_POS(NULL),
	m_pVB_NORMAL(NULL),
	m_pVB_COLOR(NULL),
	m_pVB_TEX(NULL)
{
	m_VtxBuff = NULL;
	m_SphereIdxBuff = NULL;
	m_SphereVtxBuff = NULL;
	m_IndexNum = numBlockY * numBlockX * 2 + ((numBlockY - 1) * 4) + 2;
	m_PolygonNum = m_IndexNum - 2;
	m_VexNum = m_SphereNumX * (m_SphereNumY - 1) + 2;
}

//==============================================================================
//  ��������
//==============================================================================
CShadowSphere *CShadowSphere::Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl)
{	// �f�t�H���g
	CShadowSphere *pSceneMD;
	pSceneMD = new CShadowSphere(numBlockX, numBlockY, radius, scl, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pSceneMD->Init();
	return pSceneMD;
}
CShadowSphere *CShadowSphere::Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXVECTOR3 pos)
{	// ���W�w��
	CShadowSphere *pSceneMD;
	pSceneMD = new CShadowSphere(numBlockX, numBlockY, radius, scl, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f),pos);
	pSceneMD->Init();
	return pSceneMD;
}
CShadowSphere *CShadowSphere::Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXCOLOR color)
{	// �F�w��
	CShadowSphere *pSceneMD;
	pSceneMD = new CShadowSphere(numBlockX, numBlockY, radius, scl, color, D3DXVECTOR3(0.0f,0.0f,0.0f));
	pSceneMD->Init();
	return pSceneMD;
}

//==============================================================================
//  ����������
//==============================================================================
void CShadowSphere::Init( void )
{
	MakeVex();				// �e���_
	MakeSphereVex();		// �X�t�B�A���_
	MakeSphereBuff();		// �X�t�B�A�C���f�N�X
}

//==============================================================================
//  �I������
//==============================================================================
void CShadowSphere::Uninit( void )
{
	SAFE_RELEASE(m_pVB_POS);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVB_NORMAL);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVB_COLOR);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVB_TEX);      // ���_�o�b�t�@�̔j��
	SAFE_RELEASE( m_VtxBuff);
	SAFE_RELEASE( m_SphereIdxBuff);
	SAFE_RELEASE( m_SphereVtxBuff);
}

//==============================================================================
//  �X�V����
//==============================================================================
void CShadowSphere::Update(const D3DXVECTOR3 pos, const D3DXVECTOR3 scl)
{	// �X�P�[���X�V
	m_SpherePos = pos;
	m_SphereScl = scl;
}
void CShadowSphere::Update(const D3DXVECTOR3 pos)
{	// ���W�X�V
	m_SpherePos = pos;
}

//==============================================================================
//  �`�揈��
//==============================================================================
void CShadowSphere::Draw( void )
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "shadow.cpp => Draw => pDevice��NULL�I�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}
	// �X�e���V���̐ݒ�

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);			// �X�e���V���L����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// Z�o�b�t�@�������܂Ȃ�
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);			// �J���[�������܂Ȃ�

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);		// ��r�֐��i�K�����i�j
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);					// �Q�ƒl

	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Z�o�b�t�@�ň��������������i�������Ȃ��j
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// �����_�����������i�������Ȃ��j
	// �\�`��
	//pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_DECR);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);		// �����ɒʂ������i+1�j
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	DrawSphere();
	// ���`��
	//pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);		// �����ɒʂ������i-1�j
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	DrawSphere();

	// �e�̐؂���ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);			// �J���[��������
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		// ��r�֐��i��������΁j

	// �e�̕`��
	// ���_�̃f�N�����[�V�����̐ݒ�
	CVertexDecl::SetTex2D(pDevice, m_VtxBuff);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// �X�e���V���ݒ�̃N���A
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// �X�e���V�����N���A
	pDevice->Clear(0, NULL,
		D3DCLEAR_STENCIL,								// �X�e���V��
		D3DCOLOR_RGBA(0, 0, 0, 0),				// �������F
		1.0f,											// 0~1�i0�͎�O�A1�͉����j
		0);

}

//=======================================================================================
// �e���_�ݒ�
//=======================================================================================
void CShadowSphere::MakeVex(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX2D) * NUM_VERTEX,           // �쐬���������_�o�b�t�@�̃T�C�Y�i��̒��_*���_���j
		D3DUSAGE_WRITEONLY,                         // �������ނ������Ȃ��i�`�F�b�N���Ȃ��j
		0,                              // �ǂ�Ȓ��_�ŏ����́i0�ɂ��Ă�OK�j
		D3DPOOL_MANAGED,                            // �������Ǘ������C���ɂ���
		&m_VtxBuff,
		NULL);

	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	CVertexDecl::VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�i 2D���W�E�E��� �j
	pVtx[0].pos = D3DXVECTOR4(        0.0f,          0.0f, 0.0f,1.0f);                 // ����̍��W
	pVtx[1].pos = D3DXVECTOR4(SCREEN_WIDTH,          0.0f, 0.0f,1.0f);                 // �E��̍��W
	pVtx[2].pos = D3DXVECTOR4(        0.0f, SCREEN_HEIGHT, 0.0f,1.0f);                 // �����̍��W
	pVtx[3].pos = D3DXVECTOR4(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f,1.0f);                 // �E���̍��W

	// ���_�J���[�̐ݒ�i0~255�̐����l�j
	pVtx[0].color = m_Color;  // ����̐F
	pVtx[1].color = m_Color;  // �E��̐F
	pVtx[2].color = m_Color;  // �����̐F
	pVtx[3].color = m_Color;  // �E���̐F

	// ���_�f�[�^��UV�f�[�^�̒ǉ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);                    // �����UV���W
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);                    // �E���UV���W
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);                    // ������UV���W
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);                    // �E����UV���W

 // �����J����
	m_VtxBuff->Unlock();
}

//=======================================================================================
// �X�t�B�A���_�ݒ�
//=======================================================================================
void CShadowSphere::MakeSphereVex(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_POS) * m_VexNum,           // �쐬���������_�o�b�t�@�̃T�C�Y�i��̒��_*���_���j
		D3DUSAGE_WRITEONLY,                         // �������ނ������Ȃ��i�`�F�b�N���Ȃ��j
		0,                              // �ǂ�Ȓ��_�ŏ����́i0�ɂ��Ă�OK�j
		D3DPOOL_MANAGED,                            // �������Ǘ������C���ɂ���
		&m_pVB_POS,
		NULL);

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_POS* v0;
	m_pVB_POS->Lock(0, 0, (void**)&v0, 0);

	// ���a���L��
	float Radius = m_SphereRadius;

	for (int i = 0; i < m_SphereNumY + 1; i++)
	{
		m_SphereRadius = cos(D3DXToRadian((180 / (float)m_SphereNumY) * i - 90)) * Radius;
		if (i == 0 || i == m_SphereNumY)
		{
			// ���_���̐ݒ�
			v0[0].pos = D3DXVECTOR3(0.0f,
				sin(D3DXToRadian(((-180 / (float)m_SphereNumY) * i - 90))) * Radius,                                                                            // Y���W�̐ݒ�
				0.0f);
			v0++;
		}
		else
		{
			for (int nCntWidth = 0; nCntWidth < m_SphereNumX; nCntWidth++, v0++)
			{
				// ���_���̐ݒ�
				v0[0].pos = D3DXVECTOR3(cos(D3DXToRadian((360 / (float)m_SphereNumX) * nCntWidth)) * m_SphereRadius,      // X���W�̐ݒ�i 3D���W�E�E��� �j
					sin(D3DXToRadian(((-180 / (float)m_SphereNumY) * i - 90))) * Radius,                                                                            // Y���W�̐ݒ�
					sin(D3DXToRadian((360 / (float)m_SphereNumX) * nCntWidth)) * m_SphereRadius);    // Z���W�̐ݒ�
			}
		}
	}
	m_pVB_POS->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�m�[�}�����W)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_NORMAL) * m_VexNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_NORMAL, NULL))) {
		MessageBox(NULL, "�m�[�}�����W�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_NORMAL* v1;
	m_pVB_NORMAL->Lock(0, 0, (void**)&v1, 0);
	for (int i = 0; i < m_SphereNumY + 1; i++)
	{
		m_SphereRadius = cos(D3DXToRadian((180 / (float)m_SphereNumY) * i - 90)) * Radius;
		if (i == 0 || i == m_SphereNumY)
		{
			v1[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
			v1++;
		}
		else
		{
			for (int nCntWidth = 0; nCntWidth < m_SphereNumX; nCntWidth++, v1++)
			{
				v1[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
			}
		}
	}
	m_pVB_NORMAL->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�F)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_COLOR) * m_VexNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_COLOR, NULL))) {
		MessageBox(NULL, "���_�F�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_COLOR* v2;
	m_pVB_COLOR->Lock(0, 0, (void**)&v2, 0);

	for (int i = 0; i < m_SphereNumY + 1; i++)
	{
		m_SphereRadius = cos(D3DXToRadian((180 / (float)m_SphereNumY) * i - 90)) * Radius;
		if (i == 0 || i == m_SphereNumY)
		{
			v2[0].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			v2++;
		}
		else
		{
			for (int nCntWidth = 0; nCntWidth < m_SphereNumX; nCntWidth++, v2++)
			{
				v2[0].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			}
		}
	}
	m_pVB_COLOR->Unlock();

	// �I�u�W�F�N�g�̒��_�o�b�t�@(�e�N�X�`�����W)�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CVertexDecl::VERTEX3D_TEX) * m_VexNum,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED, &m_pVB_TEX, NULL))) {
		MessageBox(NULL, "�e�N�X�`�����W�����G���[�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	CVertexDecl::VERTEX3D_TEX* v3;
	m_pVB_TEX->Lock(0, 0, (void**)&v3, 0);

	for (int i = 0; i < m_SphereNumY + 1; i++)
	{
		m_SphereRadius = cos(D3DXToRadian((180 / (float)m_SphereNumY) * i - 90)) * Radius;
		if (i == 0 || i == m_SphereNumY)
		{
			v3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			v3++;
		}
		else
		{
			for (int nCntWidth = 0; nCntWidth < m_SphereNumX; nCntWidth++, v3++)
			{
				v3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			}
		}
	}
	m_pVB_TEX->Unlock();
}

//=======================================================================================
// �X�t�B�A�C���f�N�X�o�b�t�@�ݒ�
//=======================================================================================
void CShadowSphere::MakeSphereBuff(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "shadow.cpp => MakeSphereBuff => pDevice��NULL�I�I", "�G���[", MB_OK | MB_ICONASTERISK);
		return;
	}

	// �C���f�b�N�X�o�b�t�@�̍쐬
	HRESULT hr;
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * m_IndexNum,        // ���_���iWORD��16Bid�j
		D3DUSAGE_WRITEONLY,              // �g�p�p�r�t���O�i�������ނ̂݁j
		D3DFMT_INDEX16,                  // �f�[�^�̃t�H�[�}�b�g�i32Bid�ݒ肵����16��32�ɕύX�j
		D3DPOOL_MANAGED,                 // �������̊Ǘ����@�i���C���j
		&m_SphereIdxBuff,              // �o�b�t�@�\�C���^�[�t�F�C�X�|�C���^�̃A�h���X
		NULL);

	// �C���f�b�N�X���i�[�p�^���o�b�t�@�̐錾
	WORD* pIdx;

	// ���b�N
	m_SphereIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int i = 0; i < m_SphereNumY; i++)
	{
		// ���W
		if (i == 0)
		{
			for (int j = 0; j < m_SphereNumX; j++)
			{
				pIdx[0] = 0;
				pIdx++;
				pIdx[0] = (WORD)(j+1);
				pIdx++;
				if (j == m_SphereNumX - 1)
				{
					pIdx[0] = 0;
					pIdx++;
					pIdx[0] = 1;
					pIdx++;
					pIdx[0] = 1;
					pIdx++;
				}
			}
		}
		// ����
		else if (i < m_SphereNumY - 1)
		{
			pIdx[0] = (WORD)((i - 1) * m_SphereNumX + 1);
			pIdx++;
			for (int j = 0; j < m_SphereNumX; j++)
			{
				pIdx[0] = (WORD)((i - 1) * m_SphereNumX + 1 + j);
				pIdx++;
				pIdx[0] = (WORD)(i * m_SphereNumX + 1 + j);
				pIdx++;
				if (j == m_SphereNumX - 1)
				{
					pIdx[0] = (WORD)((i - 1) * m_SphereNumX + 1);
					pIdx++;
					pIdx[0] = (WORD)(i * m_SphereNumX + 1);
					pIdx++;
				}
			}
			pIdx[0] = (WORD)(i * m_SphereNumX + 1);
			pIdx++;
		}
		// ��W
		else
		{
			for (int j = 0; j < m_SphereNumX + 1; j++)
			{
				pIdx[0] = (WORD)(m_VexNum - 1 - j);
				pIdx++;
				pIdx[0] = (WORD)(m_VexNum - 1);
				pIdx++;
				if (j == m_SphereNumX)
				{
					pIdx[0] = (WORD)(m_VexNum - 2);
					pIdx++;
				}
			}
		}
	}
	// ���b�N���
	m_SphereIdxBuff->Unlock();
}

//=======================================================================================
// �X�t�B�A�̕`��
//=======================================================================================
void CShadowSphere::DrawSphere()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "shadow.cpp => DrawSphere => pDevice��NULL�I�I", "�G���[", MB_OK | MB_ICONASTERISK);
		return;
	}

	// �ϊ��s��̐錾
	D3DXMATRIX mtxScl;             // ���[�J���X�P�[��
	D3DXMATRIX mtxPos;             // ���[�J�����W
	D3DXMATRIX mtxWorld;           // ���[���h���

	// ���[�J���X�P�[���̑��
	D3DXMatrixScaling(&mtxScl,
		m_SphereScl.x,
		m_SphereScl.y,
		m_SphereScl.z);

	// ���[�J�����W�̑��
	D3DXMatrixTranslation(&mtxPos,
		m_SpherePos.x,
		m_SpherePos.y,
		m_SpherePos.z);

	// ���[���h��񏈗�
	D3DXMatrixIdentity(&mtxWorld);                       // ���[���h�̒��g��������
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);   // ���[���h�X�P�[���̑��
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);   // ���[���h���W�̑��
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);       // ���[���h���Z�b�g
	
	// ���_�̃f�N�����[�V�����̐ݒ�
	CVertexDecl::SetTex3D(pDevice, m_pVB_POS, m_pVB_NORMAL, m_pVB_COLOR, m_pVB_TEX);

	// �f�o�C�X�ɃC���f�b�N�X�o�b�t�@�̐ݒ�
	pDevice->SetIndices(m_SphereIdxBuff); 

	// �`�撼�O�Ƀe�N�X�`�����Z�b�g�i�e�N�X�`���̐ݒ�j
	pDevice->SetTexture(0, NULL);

	// �C���f�b�N�X�v���~�e�B�u�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,                 // �v���~�e�B�u�̎��
		0,
		0,
		m_VexNum,   // ���_��
		0,
		m_PolygonNum);                       // �v���~�e�B�u�̐��i�|���S���̐��j
}