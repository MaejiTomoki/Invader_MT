//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "player.h"
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "input.h"
#include "bullet.h"
#include "flare.h"
#include "enemy.h"
#include "flare.h"
#include "scene.h"
#include "fade.h"
#include "effect.h"
#include "collision.h"
#include "EnemyBuller.h"





//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CBullet				BulletPlayer;			// �N���X�o���b�g



// �R���X�g���N�^
CPlayer::CPlayer(void)
{

}


// �f�X�g���N�^
CPlayer::~CPlayer(void)
{
	 
}



//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CPlayer::Init()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		PLAYER_TEXTURENAME, &m_pTexture);
	if (FAILED(hr)) {
		return hr;
	}

	// �ϐ�������
	m_vPos.x = PLAYER_POS_X;
	m_vPos.y = PLAYER_POS_Y;
	m_nDir = 0;	// ��(�ҋ@)
	m_nStat = 1;
	m_nHP = 3;
	m_nCntHP = 0;

	return hr;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CPlayer::Uninit()
{
	// �e�N�X�`���J��
	SAFE_RELEASE(m_pTexture);
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CPlayer::Update()
{
	// �v���C���[�ړ�
	m_nDir &= 3;	// �ړ����N���A(�����͏����Ȃ�)
	if (GetKeyPress(VK_A) || GetKeyPress(VK_LEFT)) {
		// ���ړ�
		m_vPos.x -= PLAYER_SPEED_X;
		m_nDir = 5;	// ��(�ړ�)
	}
	if (GetKeyPress(VK_D) || GetKeyPress(VK_RIGHT)) {
		// �E�ړ�
		m_vPos.x += PLAYER_SPEED_X;
		m_nDir = 6;	// �E(�ړ�)
	}
	//if (GetKeyPress(VK_W) || GetKeyPress(VK_UP)) {
	//	// ��ړ�
	//	m_vPos.y += PLAYER_SPEED_Y;
	//	m_nDir = 7;	// ��(�ړ�)
	//}
	//if (GetKeyPress(VK_S) || GetKeyPress(VK_DOWN)) {
	//	// ���ړ�
	//	m_vPos.y -= PLAYER_SPEED_Y;
	//	m_nDir = 4;	// ��(�ړ�)
	//}

	//��ʒ[
	// ===== �ړ����� =====
	//������
	if (m_vPos.x < -SCREEN_WIDTH / 2 + PLAYER_SIZE_X / 2)
	{

		m_vPos.x = -SCREEN_WIDTH / 2 + PLAYER_SIZE_X / 2;
	}

	//�E����
	if (m_vPos.x > SCREEN_WIDTH / 2 - PLAYER_SIZE_X / 2)
	{
		m_vPos.x = SCREEN_WIDTH / 2 - PLAYER_SIZE_X / 2;
	}
	// ===== �����܂� =====

	// �e�̔���
	if (GetKeyTrigger(VK_SPACE)) {
		BulletPlayer.Fire(&m_vPos);
	}

	// �t���A �G�t�F�N�g�N�� (���Z�����e�X�g)
	if (GetKeyTrigger(VK_F)) {
		StartFlare(&m_vPos);
	}

	// �G�̒e�ƐڐG������
	CEnemyBullet EnemyBulletPlayer;
	XMFLOAT2 EnemyBulletPos = EnemyBulletPlayer.GetEnemyBulletPos();

	if (CPlayer::CollisionPlayer(EnemyBulletPos, 10) >= 0)
	{
		// ��񂵂�������Ȃ��悤�ɂ���
		if (m_nCntHP == 0)
		{
			// �v���C���[�̗̑͂����炷
			m_nHP--;
		}
		m_nCntHP++;
	}
	else
	{
		m_nCntHP = 0;
	}
	

	// HP��0�ɂȂ�����Q�[���I�[�o�[
	if (m_nHP == 0)
	{
		// �V�[���ړ�(�Q�[���I�[�o�[)
		SetFadeOut(SCENE_GAMEOVER);
	}
	//if (CollisionEnemy(m_vPos.x, m_vPos.y,
	//	PLAYER_RADIUS, 0.0f, &fX, &fY) >= 0) {
	//	// �����i�H�j
	//	m_nStat = 0;
	//	StartFlare(&m_vPos);
	//	m_nStat = 0;
	//	return;
	//}
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CPlayer::Draw()
{
	if (m_nStat == 0)return;

	// �v���C���[�`��
	SetPolygonPos(m_vPos.x, m_vPos.y);
	SetPolygonSize(PLAYER_SIZE_X, PLAYER_SIZE_Y);
	SetPolygonTexture(m_pTexture);
	// SetPolygonFrameSize(1.0f / PLAYER_FRAME_X, 1.0f / PLAYER_FRAME_Y);
	DrawPolygon(GetDeviceContext());
	// �t���[����߂��Ă���
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);

	// HP�p
	for (int i = 0; i < m_nHP; i++)
	{
		SetPolygonPos(PLAYER_HP_POS_X + i * 32, PLAYER_HP_POS_Y);
		SetPolygonSize(PLAYER_HP_SIZE_X, PLAYER_HP_SIZE_Y);
		SetPolygonTexture(m_pTexture);
		DrawPolygon(GetDeviceContext());
	}
}



//=============================================================================
// �v���C���[�Ƃ̏Փ˔���
//=============================================================================
int CPlayer::CollisionPlayer(XMFLOAT2 fB, float fBr)
{

	//	�����蔻��
	if (CollisionCircle(m_vPos, fB, ENEMY_SIZE_X / 2, fBr))
	{
		// �G�t�F�N�g
		StartEffect(&m_vPos, EEFECT_DEAD000);
		return 1;
	}


	return -1;
}