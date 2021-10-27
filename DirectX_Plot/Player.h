#pragma once


#include "main.h"
#include "renderer.h"

#define playerH 72
#define playerW 36




struct PLAYER
{
	bool					use;					// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;					// �v���C���[���W
	D3DXVECTOR2				Speed;			// �v���C���[�����x

	bool					onGround;				//�n�ʂƐڐG���Ă��邩



};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void ResetAcceletarionPlayer();

PLAYER* GetPlayer(void);







