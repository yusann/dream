#ifndef _MODE_H_
#define _MODE_H_

//*****************************************************************************
//   ���[�h�N���X��`
//*****************************************************************************
class CMode
{
public:
	virtual void Init(void) = 0;      // ����������
	virtual void Uninit(void) = 0;      // �I������
	virtual void Update(void) = 0;      // �X�V����
};

#endif