
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "Player.h"
#include "Ball.h"
#include "sound.h"



//グローバル変数宣言
PLAYER g_Player;

int playertex;

//x方向停止力
float player_XMASATU = 0.15f;

//重力加速度
float PlayerGravity = 0.3f;


//プレイヤー横方向移動速度
float PlayerXspeed = 1.0f;

//ジャンプ力ぅ…ですかねぇ…
float PlayerJumpPower = 10.0f;

//キック力
float KickPower = 15.0f;



//下にシュッって動くやつの加速度(こっちも下の加速度最大値に制御されます)
float Player_sita_syun_naruyatu = 1.0f;

//重力加速度最大値
float P_AccYmax = 10.0f;



//例として出した
//キック時の角度


float angle = 30.0f;//度数での角度



void ResetAcceletarionPlayer();

HRESULT InitPlayer(void)
{
 	playertex =  LoadTexture("data/TEXTURE/player.png");

	//初期化
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
	//横方向移動
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
	//縦方向移動
	//--------------------------

	//ジャンプ
	if (g_Player.onGround) {
		if (GetKeyboardTrigger(DIK_UP))
		{
			g_Player.Speed.y = -PlayerJumpPower;
			g_Player.onGround = false;
		}
	}

	//下にシュンって なるやつ
	if (GetKeyboardPress(DIK_DOWN))
	{
		g_Player.Speed.y += Player_sita_syun_naruyatu;

	}

	
	//落下速度の制限(空気抵抗的な奴)
	if (g_Player.Speed.y <= P_AccYmax) {

		g_Player.Speed.y += PlayerGravity;
	}
	

	//加速度系の処理内容をプレイヤー座標に還元
	g_Player.pos.x += g_Player.Speed.x;
	g_Player.pos.y += g_Player.Speed.y;


	//---------------------------------
	//ボールけとヴぁす処理
	//---------------------------------


	BALL &ball = *GetBall();

	//ボールとの当たり判定
	if (ball.pos.x + (ballW / 2) >= g_Player.pos.x - (playerW / 2) &&
		ball.pos.x - (ballW / 2) <= g_Player.pos.x + (playerW / 2) &&
		ball.pos.y + (ballH / 2) >= g_Player.pos.y - (playerH / 2) &&
		ball.pos.y - (ballH / 2) <= g_Player.pos.y + (playerH / 2)) 
	{
		if (GetKeyboardPress(DIK_SPACE)) {
			
			float radian = angle * (M_PI / 180);//計算用にラジアンに変換
												//ここもコントローラー導入時におもっくそ変えます


			ball.Speed.x += sinf(radian) * KickPower;
			ball.Speed.y -= cosf(radian) * KickPower;
		}
	}



	//プレイヤーの減速処理(Y座標は重力くんが仕事してるのでX座標のみ)
	g_Player.Speed.x
		+= player_XMASATU *- g_Player.Speed.x;


	//移動制限系(壁出た時マジめんどくさそう)
	//左右、下の壁は実装済み
	//上方向は今の段階だとどう頑張ってもいけないので実装してない


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


