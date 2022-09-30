#pragma once

#include "player.h"
#include "car.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	//�����������A�I������
	void init();
	void end();

	//�Q�[������
	bool update();
	//�`��
	void draw();

private:
	//�O���t�B�b�N�n���h��
	int m_hPlayer;
	int m_hCar;
	int m_frame = 0;		//�v���p�̕ϐ�
	int m_deadNum = 0;    //���S��
	int m_hitFrame = 0;   //���G�t���[��

	//�v���C���[
	Player m_player;
	//�G
	Car m_car;
};