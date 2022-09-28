#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//待ち時間
	constexpr int kwaitFrameMin = 60;
	constexpr int kwaitFrameMax = 180;

	//車の速度
	constexpr float kSpeed = -24.0f;
}

Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	//m_moveType = kMoveTypeNormal;
	m_waitFrame = 0;
	m_stopFrame = 0;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

	//動きのバリエーションを選択
	int randNum = GetRand(99);
	if (randNum < 38)
	{
		m_moveType = kMoveTypeNormal;
	}
	if (randNum < 38 + 30)
	{
		m_moveType = kMoveTypeStop;
	}
	if (randNum < 38 + 30 + 30)
	{
		m_moveType = kMoveTypeJump;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}
	//強制的にジャンプ、デバック用
	m_moveType = kMoveTypeNormal;

	//動き始めるまでの時間を設定 1秒から3秒待つ  60フレームから180フレーム
	//m_waitFrame = GetRand(kwaitFrameMax - kwaitFrameMin) + kwaitFrameMin;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

	switch (m_moveType)
	{
	case kMoveTypeNormal:
			updateNormal();
			break;
	case kMoveTypeStop:
			updateStop();
			break;
	case kMoveTypeJump:
		updateJump();
		break;
	case kMoveTypeReturn:
		updateReturn();
		break;
	default:
		break;
	}
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	DrawFormatString(0, 0, GetColor(255, 255, 255),"wait%d", m_waitFrame);
}


//private

//まっすぐ進む
void Car::updateNormal()
{
	m_pos += m_vec;
	//車が0を下回るとプラスに戻す
	if (m_pos.x < -100)
	{
		m_pos.x = 3200; //5秒ループ
	}
}

//一時停止フェイント
void Car::updateStop()
{
	if (m_pos.x > 300)
	{
		m_pos += m_vec;
	}
	else
	{
		m_stopFrame++;
		if (m_stopFrame > 20)
		{
			m_pos += m_vec;
		}
		return;
	}
}

//ジャンプする
void Car::updateJump()
{
	bool isField = false;
	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}
	m_pos += m_vec;
	if (isField && m_pos.x < 450)
	{
		m_vec.y = -16.0;
	}
	m_vec.y += 0.8;
}

//途中で引き返す
void Car::updateReturn()
{
	
	if (m_stopFrame != 18)
	{
		m_pos += m_vec;
		m_stopFrame++;
	}
	else
	{
		m_pos -= m_vec;
	}
}