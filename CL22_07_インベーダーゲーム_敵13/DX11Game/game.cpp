//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "player.h"
#include "score.h"
#include "bullet.h"
#include "enemy.h"
#include "effect.h"
#include "flare.h"
#include "EnemyBuller.h"
#include "EnemyUFO.h"
/*#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"
*/

//============================================================================
// �O���[�o���ϐ�
//============================================================================
CPlayer			Player;
CBullet			Bullet;
CEnemy			Enemy;
CScore			ScoreEnemy;
CEnemyBullet	EnemyBullet;
CEnemyUFO		EnemyUFO;

//=============================================================================
// �Q�[����ʂ̏���������
//=============================================================================
HRESULT InitGame()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = S_OK;

	// �v���C���[������
	hr = Player.Init();
	if (FAILED(hr)) {
		MsgBox(_T("�v���C���[�������G���["),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �w�i�\��������
	hr = InitBG();
	if (FAILED(hr)) {
		MsgBox(_T("�w�i�������G���["),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �e����������
	hr = Bullet.Init();
	if (FAILED(hr)) {
		MsgBox( _T("�e�����������G���["),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �G����������
	hr = Enemy.Init();
	if (FAILED(hr)) {
		MsgBox(_T("�G�����������G���["),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �G(UFO)����������
	hr = EnemyUFO.Init();
	if (FAILED(hr)) {
		MsgBox(_T("�G(UFO)�����������G���["),
			MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �G�̒e����
	hr = EnemyBullet.Init();
	if (FAILED(hr)) {
		MsgBox(_T("�G�̒e�����������G���["),
			MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �G�t�F�N�g����������
	hr = InitEffect();
	if (FAILED(hr)) {
		MsgBox(_T("�G�t�F�N�g�����������G���["),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �t���A �G�t�F�N�g����������
	hr = InitFlare();
	if (FAILED(hr)) {
		MsgBox(_T("�t���A �G�t�F�N�g�����������G���["),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �X�R�A�\������������
	hr = ScoreEnemy.Init();
	if (FAILED(hr)) {
		MsgBox(_T("�X�R�A�\�������������G���["),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}


	return hr;
}

//=============================================================================
// �Q�[����ʂ̏I������
//=============================================================================
void UninitGame()
{
	// �X�R�A�\���I������
	ScoreEnemy.Uninit();

	// �t���A �G�t�F�N�g�I������
	UninitFlare();

	// �G�t�F�N�g�I������
	UninitEffect();

	// �G�̒e����
	EnemyBullet.Uninit();

	// �G(UFO)�̏���
	EnemyUFO.Uninit();

	// �G�I������
	Enemy.Uninit();

	// �e�I������
	Bullet.Uninit();

	// �w�i�\���I������
	UninitBG();

	// �v���C���[�I������
	Player.Uninit();

}

//=============================================================================
// �Q�[����ʂ̍X�V����
//=============================================================================
void UpdateGame()
{
	// �w�i�\���X�V
	UpdateBG();

	// �v���C���[�X�V
	Player.Update();

	// �e�X�V
	Bullet.Update();

	// �G�X�V
	Enemy.Update();

	// �G(UFO)�X�V
	EnemyUFO.Update();

	// �G�̒e����
	EnemyBullet.Update();

	// �G�t�F�N�g�X�V
	UpdateEffect();

	// �t���A �G�t�F�N�g�X�V
	UpdateFlare();

	// �X�R�A�X�V
	ScoreEnemy.Update();
}

//=============================================================================
// �Q�[����ʏ���
//=============================================================================
void DrawGame()
{
	// �w�i�`�揈�� (�K��ClearRenderTargetView�̒���)
	DrawBG();

	// �G�`�揈��
	Enemy.Draw();

	// �G(FUO)�`�揈��
	EnemyUFO.Draw();

	EnemyBullet.Draw();

	// �e�`�揈��
	Bullet.Draw();

	// �v���C���[�`�揈��
	Player.Draw();

	// �G�t�F�N�g�`�揈��
	DrawEffect();

	// �t���A �G�t�F�N�g�`�揈��
	DrawFlare();

	// �X�R�A�`�揈��
	ScoreEnemy.Draw();
}
