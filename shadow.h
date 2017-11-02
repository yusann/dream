#ifndef _SHADOW_H_
#define _SHADOW_H_

//*****************************************************************************
//   �ۉe�N���X��`
//*****************************************************************************
class CShadow : public CScene
{
public:
	CShadow(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl);             // �f�t�H���g�R���X�g���N�^
	~CShadow();                             // �f�X�g���N�^

	static CShadow* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Scl);
	void Init(void);        // ����������
	void Uninit(void);      // �I������
	void Update(void);      // �X�V����
	void Draw(void);        // �`�揈��
	void SetPos(D3DXVECTOR3 Pos) { m_Pos = Pos; }
	void SetScl(float Scl) { m_Scl.z = Scl;}

private:
	void MakeVex(void);     // ���_�̐ݒ�
};

#endif