#ifndef _MODERESULT_H_
#define _MODERESULT_H_

//*****************************************************************************
//   ���U���g���[�h�N���X��`
//*****************************************************************************
class CModeResult : public CMode
{
public:
	void Init(void);
	void Uninit(void);
	void Update(void);
	static void SetClear(bool Clear) { m_Clear = Clear; }

private:
	static bool m_Clear;
};

#endif