#pragma once

#include "player.h"
#include "car.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	//初期化処理、終了処理
	void init();
	void end();

	//ゲーム処理
	bool update();
	//描画
	void draw();

private:
	//グラフィックハンドル
	int m_hPlayer;
	int m_hCar;
	int m_frame = 0;		//計測用の変数
	int m_deadNum = 0;    //死亡回数
	int m_hitFrame = 0;   //無敵フレーム

	//プレイヤー
	Player m_player;
	//敵
	Car m_car;
};