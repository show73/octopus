
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "Ball.h"
#include "sound.h"


//-----------------------------
//�O���[�o���ϐ��錾
//-------------------------------


BALL g_Ball;

//�e�N�X�`��
int balltex;

//


//---------------------
//�ύX�\�萔
//----------------------


//x������~��
float ball_XMASATU = 0.15f;

//�d�͉����x
float BallGravity = 0.3f;

//�{�[���̏d�͉����J�n���x
float BallStartGrav = 15.0f;


//�{�[�����˓x
float Ball_bounce = 1.0f;


//�d�͉����x�ő�l
float B_AccYmax = 10.0f;

//�{�[������(1���Ɗ��S��~����Ǝv�� 0�Ŗ�����)
float Ball_speeddown_multiply = 0.05f;

//�Ǔ��Փˎ��̃{�[�������x

float Ball_speeddown_onHit = 0.7f;

//�{�[���̒��˂���E���x
//�Ȃ�Ƃ������A�{�[���̈ړ��ʂ��[���Ƃ݂Ȃ����̔�r�Ɏg���l
//����Ȃ��Ƃ�΂�
//X���W��0�ł���
//Y���W�Ƃ��ׂ����ݒ肵�Ȃ��Ƃ����ƍׂ����т��т�񒵂˂�
float Ball_minBounceSpeedX = 0.000f;
float Ball_minBounceSpeedY = 2.1f;



//-----------------------------------
//�Ȃ񂿂��錾
//---------------------------------

//�����x���Z�b�g
//Unity�łł�R�L�[�̃{�[���ʒu���Z�b�g�̎��Ɏg���Ă�����
//�{�[�����������Ƃ��Ƃ��Ɏg���邩��

void ResetSpeedBall();

//�ǂɓ��������Ƃ��̌����̊֐�
void SpeedDown_Ball();



HRESULT InitBall(void)
{
	balltex = LoadTexture("data/TEXTURE/ball.png");


	//������
	g_Ball.pos.x = SCREEN_WIDTH / 2;
	g_Ball.pos.y = SCREEN_HEIGHT / 4;
	g_Ball.Speed.x = 50;
	g_Ball.Speed.y = 0;
	g_Ball.use = true;

	return E_NOTIMPL;
}

void UninitBall(void)
{


}

void UpdateBall(void)
{

	//�����x�n�̏������e�����W�ɊҌ�
	g_Ball.pos.x += g_Ball.Speed.x;
	g_Ball.pos.y += g_Ball.Speed.y;

	//�{�[���̏d�͉�������

	if (g_Ball.ballspeed <= BallStartGrav) {

		if (g_Ball.Speed.y <= B_AccYmax)
		{
			g_Ball.Speed.y += BallGravity;
		}
	}

	g_Ball.ballspeed = (fabsf(g_Ball.Speed.x) + fabsf(g_Ball.Speed.y))/2 ;





	//��ʂ̉E���ɓ��������Ƃ�
	if (g_Ball.pos.x + (ballW / 2) >= SCREEN_WIDTH)
	{
		g_Ball.pos.x = SCREEN_WIDTH - (ballW / 2);
		g_Ball.Speed.x = -g_Ball.Speed.x;

		SpeedDown_Ball();
	}


	//��ʂ̍����ɓ��������Ƃ�
	if (g_Ball.pos.x - (ballW / 2) <= 0)
	{
		g_Ball.pos.x = +(ballW / 2);
		g_Ball.Speed.x = -g_Ball.Speed.x;

		SpeedDown_Ball();
	}

	//��ʂ̉����ɓ��������Ƃ�
	if (g_Ball.pos.y + (ballH / 2) >= SCREEN_HEIGHT)
	{
		g_Ball.pos.y = SCREEN_HEIGHT - (ballH / 2);
		g_Ball.Speed.y = -g_Ball.Speed.y;

		SpeedDown_Ball();
	}

	//��ʂ̏㑤�ɓ��������Ƃ�
	if (g_Ball.pos.y - (ballH / 2) <= 0)
	{
		g_Ball.pos.y = ballH / 2;
		g_Ball.Speed.y = -g_Ball.Speed.y;

		SpeedDown_Ball();
	}
}


void ResetSpeedBall() {
	g_Ball.Speed.x = 0;
	g_Ball.Speed.y = 0;
}




//�Č�����߂����ǕǍۂɃ{�[�����ᑬ�Ői�񂾍ۂ�
//�{�[������������ԂŒ�~�����̂ŉ��P�̗]�n����
//��
//�ꉞ���W�b�N�𕪂��čs���悤�ɕύX�����̂Ńo�O���Ȃ���΂��̂܂܂�
//�o�O�������̂Œ����܂���
//����Aelse���̏����͗͂���ɉ��������ɂ͕K�v�ȏ������������Ǖʂ�x�����ɂ͂���Ȃ�����
//���Ă��Ƃ�X����else�͏����܂���


void SpeedDown_Ball() 
{
	
	if (fabsf(g_Ball.Speed.x) >= Ball_minBounceSpeedX) {
		g_Ball.Speed.x =
			g_Ball.Speed.x * Ball_speeddown_onHit;
	}

	if (fabsf(g_Ball.Speed.y) >= Ball_minBounceSpeedY) {
		g_Ball.Speed.y =
			g_Ball.Speed.y * Ball_speeddown_onHit;
	}
	else
	{
		g_Ball.Speed.y = 0;
	}


}


void DrawBall(void)
{
	DrawSprite(balltex, g_Ball.pos.x, g_Ball.pos.y, ballW, ballH, 0, 0, 1, 1);
}

BALL* GetBall(void)
{
	return &g_Ball;
}
