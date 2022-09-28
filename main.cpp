#include "DxLib.h"

#include "game.h"
#include "player.h"
#include "car.h"

namespace
{
	// 地面の高さ
	constexpr int kFieldY = Game::kScreenHeight - 64;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	int hPlayer = LoadGraph("data/player.png");
	int hCar = LoadGraph("data/car.png");
	int frame = 0;		//計測用の変数
	int deadNum = 0;    //死亡回数
	int hitFrame = 0;   //無敵フレーム

	Player player;
	player.setGraphic(hPlayer);
	player.setup(kFieldY);

	Car car;
	car.setGraphic(hCar);
	car.setup(kFieldY);

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		player.update();
		car.update();


		//車に当たると
		if (player.isCol(car))
		//if(false)
		{
			player.setDead(true);	//キャラが死亡する
			if (hitFrame == 0)
			{
				deadNum++;			//死亡カウントが増える
			}
			hitFrame = 10;			//当たった直後無敵時間発生
		}
		if (hitFrame != 0)			//無敵時間の間
		{
			hitFrame--;				//無敵カウントを減らしていく
		}
		if (true)
		{
			frame++;				//死んでいるとき1ずつカウント
		}
		if (frame >= 60)			//カウントがたまるとキャラが復活
		{
			player.setDead(false);
			frame = 0;
		}
		// 地面の描画
		DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
		DrawFormatString(0, 17, GetColor(255, 255, 255), "死亡回数%d回", deadNum);
		player.draw();
		car.draw();

		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DeleteGraph(hPlayer);
	DeleteGraph(hCar);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}