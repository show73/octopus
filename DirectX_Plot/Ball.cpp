
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "Ball.h"
#include "sound.h"


//-----------------------------
//グローバル変数宣言
//-------------------------------


BALL g_Ball;

//テクスチャ
int balltex;

//


//---------------------
//変更可能定数
//----------------------


//x方向停止力
float ball_XMASATU = 0.15f;

//重力加速度
float BallGravity = 0.3f;

//ボールの重力加速開始速度
float BallStartGrav = 15.0f;


//ボール反射度
float Ball_bounce = 1.0f;


//重力加速度最大値
float B_AccYmax = 10.0f;

//ボール減速(1だと完全停止すると思う 0で無減速)
float Ball_speeddown_multiply = 0.05f;

//壁等衝突時のボール減速度

float Ball_speeddown_onHit = 0.7f;

//ボールの跳ねる限界速度
//なんというか、ボールの移動量をゼロとみなす時の比較に使う値
//これないとやばい
//X座標は0でいい
//Y座標とか細かく設定しないとずっと細かくびょんびょん跳ねる
float Ball_minBounceSpeedX = 0.000f;
float Ball_minBounceSpeedY = 2.1f;



//-----------------------------------
//なんちゃら宣言
//---------------------------------

//加速度リセット
//Unity版ではRキーのボール位置リセットの時に使ってたけど
//ボール持ちたいときとかに使えるかも

void ResetSpeedBall();

//壁に当たったときの原則の関数
void SpeedDown_Ball();



HRESULT InitBall(void)
{
	balltex = LoadTexture("data/TEXTURE/ball.png");


	//初期化
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

	//加速度系の処理内容を座標に還元
	g_Ball.pos.x += g_Ball.Speed.x;
	g_Ball.pos.y += g_Ball.Speed.y;

	//ボールの重力加速処理

	if (g_Ball.ballspeed <= BallStartGrav) {

		if (g_Ball.Speed.y <= B_AccYmax)
		{
			g_Ball.Speed.y += BallGravity;
		}
	}

	g_Ball.ballspeed = (fabsf(g_Ball.Speed.x) + fabsf(g_Ball.Speed.y))/2 ;





	//画面の右側に当たったとき
	if (g_Ball.pos.x + (ballW / 2) >= SCREEN_WIDTH)
	{
		g_Ball.pos.x = SCREEN_WIDTH - (ballW / 2);
		g_Ball.Speed.x = -g_Ball.Speed.x;

		SpeedDown_Ball();
	}


	//画面の左側に当たったとき
	if (g_Ball.pos.x - (ballW / 2) <= 0)
	{
		g_Ball.pos.x = +(ballW / 2);
		g_Ball.Speed.x = -g_Ball.Speed.x;

		SpeedDown_Ball();
	}

	//画面の下側に当たったとき
	if (g_Ball.pos.y + (ballH / 2) >= SCREEN_HEIGHT)
	{
		g_Ball.pos.y = SCREEN_HEIGHT - (ballH / 2);
		g_Ball.Speed.y = -g_Ball.Speed.y;

		SpeedDown_Ball();
	}

	//画面の上側に当たったとき
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




//再現性低めだけど壁際にボールが低速で進んだ際に
//ボールが浮いた状態で停止したので改善の余地あり
//↑
//一応ロジックを分けて行うように変更したのでバグがなければこのままで
//バグあったので直しました
//これ、else内の処理は力が常に加わる方向には必要な処理かもだけど別にx方向にはいらないかも
//ってことでX側のelseは消しました


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
