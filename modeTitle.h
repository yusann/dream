#ifndef _MODETITLE_H_
#define _MODETITLE_H_

//*****************************************************************************
//   タイトルモードクラス定義
//*****************************************************************************
class CModeTitle : public CMode
{
public:
	void Init(void);
	void Uninit(void);
	void Update(void);
};

#endif