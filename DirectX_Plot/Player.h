#pragma once


#include "main.h"
#include "renderer.h"

#define playerH 72
#define playerW 36




struct PLAYER
{
	bool					use;					// true:使っている  false:未使用
	D3DXVECTOR2				pos;					// プレイヤー座標
	D3DXVECTOR2				Speed;			// プレイヤー加速度

	bool					onGround;				//地面と接触しているか



};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void ResetAcceletarionPlayer();

PLAYER* GetPlayer(void);







