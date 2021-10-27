#pragma once


#include "main.h"
#include "renderer.h"

#define ballH 36
#define ballW 36




struct BALL
{
	bool					use;					// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;					// �{�[�����W
	D3DXVECTOR2				Speed;			// �{�[�������x



	int ballspeed;

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT  InitBall(void);
void UninitBall(void);
void UpdateBall(void);
void DrawBall(void);

void ResetSpeedBall();

BALL* GetBall(void);







