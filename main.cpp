#include "DxLib.h"

#include "game.h"
#include "player.h"
#include "car.h"

namespace
{
	// �n�ʂ̍���
	constexpr int kFieldY = Game::kScreenHeight - 64;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	int hPlayer = LoadGraph("data/player.png");
	int hCar = LoadGraph("data/car.png");
	int frame = 0;		//�v���p�̕ϐ�
	int deadNum = 0;    //���S��
	int hitFrame = 0;   //���G�t���[��

	Player player;
	player.setGraphic(hPlayer);
	player.setup(kFieldY);

	Car car;
	car.setGraphic(hCar);
	car.setup(kFieldY);

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		player.update();
		car.update();


		//�Ԃɓ������
		if (player.isCol(car))
		//if(false)
		{
			player.setDead(true);	//�L���������S����
			if (hitFrame == 0)
			{
				deadNum++;			//���S�J�E���g��������
			}
			hitFrame = 10;			//�����������㖳�G���Ԕ���
		}
		if (hitFrame != 0)			//���G���Ԃ̊�
		{
			hitFrame--;				//���G�J�E���g�����炵�Ă���
		}
		if (true)
		{
			frame++;				//����ł���Ƃ�1���J�E���g
		}
		if (frame >= 60)			//�J�E���g�����܂�ƃL����������
		{
			player.setDead(false);
			frame = 0;
		}
		// �n�ʂ̕`��
		DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
		DrawFormatString(0, 17, GetColor(255, 255, 255), "���S��%d��", deadNum);
		player.draw();
		car.draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DeleteGraph(hPlayer);
	DeleteGraph(hCar);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}