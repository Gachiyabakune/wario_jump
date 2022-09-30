#include "SceneTitle.h"
#include "DxLib.h"

SceneTitle::SceneTitle()
{
	m_fadeBright = 0;
	m_fadeSpeed = 0;
}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::init()
{
	m_fadeBright = 0;
	m_fadeSpeed = 8;
}

void SceneTitle::end()
{
	SetDrawBright(255,255,255);
}

bool SceneTitle::update()
{
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if ((m_fadeBright <= 0) && (m_fadeSpeed < 0))
	{
		//フェードアウトしきったら次のシーンへ
		m_fadeBright = 0;
		return true;
	}
	//キー入力
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (m_fadeSpeed == 0)
	{
		if (padState & PAD_INPUT_1)
		{
			//return true;
			m_fadeSpeed = -8;
		}
	}
	return false;
}

void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	DrawString(0, 0, "SceneMainの表示", GetColor(255, 255, 255));
}