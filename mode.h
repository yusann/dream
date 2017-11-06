#ifndef _MODE_H_
#define _MODE_H_

//*****************************************************************************
//   モードクラス定義
//*****************************************************************************
class CMode
{
public:
	virtual void Init(void) = 0;      // 初期化処理
	virtual void Uninit(void) = 0;      // 終了処理
	virtual void Update(void) = 0;      // 更新処理
};

#endif