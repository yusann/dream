//=============================================================================
// �e
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "shadow.h"

//*************
// ���C������
//*************
CShadow::CShadow(){}
CShadow::~CShadow() {}

// �ϐ�������
CShadow::CShadow(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXCOLOR color, D3DXVECTOR3 pos)
	: m_SpherePos(pos),
	m_SphereScl(scl),
	m_SphereRadius(radius),
	m_Color(color),
	m_SphereNumX(numBlockX),
	m_SphereNumY(numBlockY)
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
CShadow *CShadow::Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl)
{	// �f�t�H���g
	CShadow *pSceneMD;
	pSceneMD = new CShadow(numBlockX, numBlockY, radius, scl, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pSceneMD->Init();
	return pSceneMD;
}
CShadow *CShadow::Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXVECTOR3 pos)
{	// ���W�w��
	CShadow *pSceneMD;
	pSceneMD = new CShadow(numBlockX, numBlockY, radius, scl, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.3f),pos);
	pSceneMD->Init();
	return pSceneMD;
}
CShadow *CShadow::Create(int numBlockX, int numBlockY, float radius, D3DXVECTOR3 scl, D3DXCOLOR color)
{	// �F�w��
	CShadow *pSceneMD;
	pSceneMD = new CShadow(numBlockX, numBlockY, radius, scl, color, D3DXVECTOR3(0.0f,0.0f,0.0f));
	pSceneMD->Init();
	return pSceneMD;
}

//==============================================================================
//  ����������
//==============================================================================
void CShadow::Init( void )
{
	MakeVex();				// �e���_
	MakeSphereVex();		// �X�t�B�A���_
	MakeSphereBuff();		// �X�t�B�A�C���f�N�X
}

//==============================================================================
//  �I������
//==============================================================================
void CShadow::Uninit( void )
{
	SAFE_RELEASE( m_VtxBuff);
	SAFE_RELEASE( m_SphereIdxBuff);
	SAFE_RELEASE( m_SphereVtxBuff);
}

//==============================================================================
//  �X�V����
//==============================================================================
void CShadow::Update(const D3DXVECTOR3 pos, const D3DXVECTOR3 scl)
{	// �X�P�[���X�V
	m_SpherePos = pos;
	m_SphereScl = scl;
}
void CShadow::Update(const D3DXVECTOR3 pos)
{	// ���W�X�V
	m_SpherePos = pos;
}

//==============================================================================
//  �`�揈��
//==============================================================================
void CShadow::Draw( void )
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "shadow.cpp => Draw => pDevice��NULL�I�I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// �X�e���V���̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	// �\�`��
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	DrawSphere();
	// ���`��
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	DrawSphere();

	// �e�̐؂���ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	// �e�̕`��
	pDevice->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// �X�e���V���ݒ�̃N���A
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=======================================================================================
// �e���_�ݒ�
//=======================================================================================
void CShadow::MakeVex(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULL�`�F�b�N���Ă��������I", "�G���[", MB_OK | MB_ICONASTERISK);         // �G���[���b�Z�[�W
		return;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,           // �쐬���������_�o�b�t�@�̃T�C�Y�i��̒��_*���_���j
		D3DUSAGE_WRITEONLY,                         // �������ނ������Ȃ��i�`�F�b�N���Ȃ��j
		FVF_VERTEX_2D,                              // �ǂ�Ȓ��_�ŏ����́i0�ɂ��Ă�OK�j
		D3DPOOL_MANAGED,                            // �������Ǘ������C���ɂ���
		&m_VtxBuff,
		NULL);

	// ���_����ݒ�
	// ���_���i�[�p�^���o�b�t�@�̐錾
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�i 2D���W�E�E��� �j
	pVtx[0].pos = D3DXVECTOR3(        0.0f,          0.0f, 0.0f);                 // ����̍��W
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH,          0.0f, 0.0f);                 // �E��̍��W
	pVtx[2].pos = D3DXVECTOR3(        0.0f, SCREEN_HEIGHT, 0.0f);                 // �����̍��W
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);                 // �E���̍��W

	// rhw�̐ݒ�i�K��1.0f�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CShadow::MakeSphereVex(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "shadow.cpp => MakeSphereVex => pDevice��NULL�I�I", "�G���[", MB_OK | MB_ICONASTERISK);
		return;
	}

	// ���_�o�b�t�@�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_VexNum,           // �쐬���������_�o�b�t�@�̃T�C�Y�i��̒��_*���_���j
		D3DUSAGE_WRITEONLY,                                      // �������ނ������Ȃ��i�`�F�b�N���Ȃ��j
		FVF_VERTEX_3D,                                           // �ǂ�Ȓ��_�ŏ����́i0�ɂ��Ă�OK�j
		D3DPOOL_MANAGED,                                         // �������Ǘ������C���ɂ���
		&m_SphereVtxBuff,
		NULL);

	// ���_���i�[�p�^���o�b�t�@�̐錾
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����i0,0���L������ƑS�������b�N�j
	m_SphereVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// ���a���L��
	float Radius = m_SphereRadius;

	for (int i = 0; i < m_SphereNumY + 1; i++)
	{
		m_SphereRadius = cos(D3DXToRadian((180 / (float)m_SphereNumY) * i - 90)) * Radius;
		if (i == 0 || i == m_SphereNumY)
		{
			// ���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f,
				sin(D3DXToRadian(((-180 / (float)m_SphereNumY) * i - 90))) * Radius,                                                                            // Y���W�̐ݒ�
				0.0f);
			pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
			pVtx[0].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx++;
		}
		else
		{
			for (int nCntWidth = 0; nCntWidth < m_SphereNumX; nCntWidth++, pVtx++)
			{
				// ���_���̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(cos(D3DXToRadian((360 / (float)m_SphereNumX) * nCntWidth)) * m_SphereRadius,      // X���W�̐ݒ�i 3D���W�E�E��� �j
					sin(D3DXToRadian(((-180 / (float)m_SphereNumY) * i - 90))) * Radius,                                                                            // Y���W�̐ݒ�
					sin(D3DXToRadian((360 / (float)m_SphereNumX) * nCntWidth)) * m_SphereRadius);    // Z���W�̐ݒ�
				pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);                          // �@���̐ݒ�
				pVtx[0].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			}
		}
	}
	// �����J����
	m_SphereVtxBuff->Unlock();
}

//=======================================================================================
// �X�t�B�A�C���f�N�X�o�b�t�@�ݒ�
//=======================================================================================
void CShadow::MakeSphereBuff(void)
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
void CShadow::DrawSphere()
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

	// �p�C�v���C��
	pDevice->SetStreamSource(0,
		m_SphereVtxBuff,     // �X�g���[���̂��ƂɂȂ钸�_�̃o�b�t�@�̎n�_
		0,                       // �I�t�Z�b�g�i�o�C�g�j
		sizeof(VERTEX_3D));      // ��̒��_�f�[�^�̃T�C�Y�i�X�g���C�h�ʁj

	// �f�o�C�X�ɃC���f�b�N�X�o�b�t�@�̐ݒ�
	pDevice->SetIndices(m_SphereIdxBuff); 

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

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