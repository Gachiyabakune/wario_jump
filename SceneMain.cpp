#include "SceneMain.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	// �n�ʂ̍���
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

//�Q�[������
bool SceneMain::update()
{
	m_player.update();
	m_car.update();

	//�Ԃɓ������
	if (m_player.isCol(m_car))
	{
		m_player.setDead(true);	//�L���������S����
		if (m_hitFrame == 0)
		{
			m_deadNum++;			//���S�J�E���g��������
		}
		m_hitFrame = 10;			//�����������㖳�G���Ԕ���
	}
	if (m_hitFrame != 0)			//���G���Ԃ̊�
	{
		m_hitFrame--;				//���G�J�E���g�����炵�Ă���
	}
	if (true)
	{
		m_frame++;				//����ł���Ƃ�1���J�E���g
	}
	if (m_frame >= 60)			//�J�E���g�����܂�ƃL����������
	{
		m_player.setDead(false);
		m_frame = 0;
	}
	return false;
}

//�`��
void SceneMain::draw()
{
	// �n�ʂ̕`��
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	//DrawFormatString(0, 17, GetColor(255, 255, 255), "���S��%d��", deadNum);
	m_player.draw();
	m_car.draw();
}