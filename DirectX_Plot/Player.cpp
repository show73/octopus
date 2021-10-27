
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "Player.h"
#include "Ball.h"
#include "sound.h"



//�O���[�o���ϐ��錾
PLAYER g_Player;

int playertex;

//x������~��
float player_XMASATU = 0.15f;

//�d�͉����x
float PlayerGravity = 0.3f;


//�v���C���[�������ړ����x
float PlayerXspeed = 1.0f;

//�W�����v�͂��c�ł����˂��c
float PlayerJumpPower = 10.0f;

//�L�b�N��
float KickPower = 15.0f;



//���ɃV���b���ē�����̉����x(�����������̉����x�ő�l�ɐ��䂳��܂�)
float Player_sita_syun_naruyatu = 1.0f;

//�d�͉����x�ő�l
float P_AccYmax = 10.0f;



//��Ƃ��ďo����
//�L�b�N���̊p�x


float angle = 30.0f;//�x���ł̊p�x



void ResetAcceletarionPlayer();

HRESULT InitPlayer(void)
{
 	playertex =  LoadTexture("data/TEXTURE/player.png");

	//������
	g_Player.pos.x = SCREEN_WIDTH / 2;
	g_Player.pos.y = SCREEN_HEIGHT / 3;

	g_Player.Speed.x = 0;
	g_Player.Speed.y = 0;
	
	g_Player.use = true;
	g_Player.onGround = false;

	return E_NOTIMPL;
}

void UninitPlayer(void)
{


}

void UpdatePlayer(void) 
{



	//--------------------------
	//�������ړ�
	//--------------------------

	if (GetKeyboardPress(DIK_LEFT))
	{
		g_Player.Speed.x -= PlayerXspeed;

	}

	if (GetKeyboardPress(DIK_RIGHT))
	{
		g_Player.Speed.x += PlayerXspeed;

	}

	//--------------------------
	//�c�����ړ�
	//--------------------------

	//�W�����v
	if (g_Player.onGround) {
		if (GetKeyboardTrigger(DIK_UP))
		{
			g_Player.Speed.y = -PlayerJumpPower;
			g_Player.onGround = false;
		}
	}

	//���ɃV�������� �Ȃ���
	if (GetKeyboardPress(DIK_DOWN))
	{
		g_Player.Speed.y += Player_sita_syun_naruyatu;

	}

	
	//�������x�̐���(��C��R�I�ȓz)
	if (g_Player.Speed.y <= P_AccYmax) {

		g_Player.Speed.y += PlayerGravity;
	}
	

	//�����x�n�̏������e���v���C���[���W�ɊҌ�
	g_Player.pos.x += g_Player.Speed.x;
	g_Player.pos.y += g_Player.Speed.y;


	//---------------------------------
	//�{�[�����ƃ���������
	//---------------------------------


	BALL &ball = *GetBall();

	//�{�[���Ƃ̓����蔻��
	if (ball.pos.x + (ballW / 2) >= g_Player.pos.x - (playerW / 2) &&
		ball.pos.x - (ballW / 2) <= g_Player.pos.x + (playerW / 2) &&
		ball.pos.y + (ballH / 2) >= g_Player.pos.y - (playerH / 2) &&
		ball.pos.y - (ballH / 2) <= g_Player.pos.y + (playerH / 2)) 
	{
		if (GetKeyboardPress(DIK_SPACE)) {
			
			float radian = angle * (M_PI / 180);//�v�Z�p�Ƀ��W�A���ɕϊ�
												//�������R���g���[���[�������ɂ����������ς��܂�


			ball.Speed.x += sinf(radian) * KickPower;
			ball.Speed.y -= cosf(radian) * KickPower;
		}
	}



	//�v���C���[�̌�������(Y���W�͏d�͂��񂪎d�����Ă�̂�X���W�̂�)
	g_Player.Speed.x
		+= player_XMASATU *- g_Player.Speed.x;


	//�ړ������n(�Ǐo�����}�W�߂�ǂ�������)
	//���E�A���̕ǂ͎����ς�
	//������͍��̒i�K���Ƃǂ��撣���Ă������Ȃ��̂Ŏ������ĂȂ�


	if (g_Player.pos.x + (playerW / 2) >= SCREEN_WIDTH)
	{
		g_Player.pos.x = SCREEN_WIDTH - (playerW / 2);
		ResetAcceletarionPlayer();

	}
	if (g_Player.pos.x - (playerW / 2) <= 0)
	{
		g_Player.pos.x = + (playerW / 2);
		ResetAcceletarionPlayer();
	}

	if (g_Player.pos.y + (playerH / 2) >= SCREEN_HEIGHT)
	{
		g_Player.pos.y = SCREEN_HEIGHT - (playerH/2);
		g_Player.onGround = true;
	}
}


void ResetAcceletarionPlayer() {
	g_Player.Speed.x = 0;
	g_Player.Speed.y = 0;
}

void DrawPlayer(void) 
{
	DrawSprite(playertex, g_Player.pos.x, g_Player.pos.y, playerW, playerH, 0, 0, 1, 1);
}

PLAYER* GetPlayer(void) 
{
	return &g_Player;
}


