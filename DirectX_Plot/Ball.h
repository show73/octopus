#pragma once


#include "main.h"
#include "renderer.h"

#define ballH 36
#define ballW 36




struct BALL
{
	bool					use;					// true:使っている  false:未使用
	D3DXVECTOR2				pos;					// ボール座標
	D3DXVECTOR2				Speed;			// ボール加速度



	int ballspeed;

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT  InitBall(void);
void UninitBall(void);
void UpdateBall(void);
void DrawBall(void);

void ResetSpeedBall();

BALL* GetBall(void);







