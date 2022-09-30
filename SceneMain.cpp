#include "SceneMain.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	// 地面の高さ
	constexpr int kFieldY = Game::kScreenHeight - 64;
}

SceneMain::SceneMain()
{
	m_hPlayer = -1;
	m_hCar = -1;
	m_frame = 0;		
	m_deadNum = 0;    
	m_hitFrame = 0;  
}

SceneMain::~SceneMain()
{

}

void SceneMain::init()
{
	m_hPlayer = LoadGraph("data/player.png");
	m_hCar = LoadGraph("data/car.png");

	m_player.setGraphic(m_hPlayer);
	m_player.setup(kFieldY);

	m_car.setGraphic(m_hCar);
	m_car.setup(kFieldY);
}

void SceneMain::end()
{
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hCar);
}

//ゲーム処理
bool SceneMain::update()
{
	m_player.update();
	m_car.update();

	//車に当たると
	if (m_player.isCol(m_car))
	{
		m_player.setDead(true);	//キャラが死亡する
		if (m_hitFrame == 0)
		{
			m_deadNum++;			//死亡カウントが増える
		}
		m_hitFrame = 10;			//当たった直後無敵時間発生
	}
	if (m_hitFrame != 0)			//無敵時間の間
	{
		m_hitFrame--;				//無敵カウントを減らしていく
	}
	if (true)
	{
		m_frame++;				//死んでいるとき1ずつカウント
	}
	if (m_frame >= 60)			//カウントがたまるとキャラが復活
	{
		m_player.setDead(false);
		m_frame = 0;
	}
	return false;
}

//描画
void SceneMain::draw()
{
	// 地面の描画
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	//DrawFormatString(0, 17, GetColor(255, 255, 255), "死亡回数%d回", deadNum);
	m_player.draw();
	m_car.draw();
}