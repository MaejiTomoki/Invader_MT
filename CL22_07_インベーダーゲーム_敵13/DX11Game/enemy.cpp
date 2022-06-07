//=============================================================================
//
// �G���� [enemy.cpp]
// Author : �O�n�q�M
//
//=============================================================================
#include "enemy.h"
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "collision.h"
#include "effect.h"
#include "score.h"
#include "EnemyBuller.h"
#include "fade.h"
#include "scene.h"




//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CBullet				m_BulletEnemy;
XMFLOAT2			m_BulletEnemyPos;
ENEMY CEnemy::m_enemy[MAX_ENEMY_X];
//ENEMY CEnemy::m_enemyUFO[MAX_ENEMY_UFO];

int	g_nMoveCnt;				// Y(�c)�̈ړ���


// �R���X�g���N�^/�f�X�g���N�^
CEnemy::CEnemy(void)
{

}
CEnemy::~CEnemy(void)
{

}



//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemy::Init()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		ENEMY_TEXTURENAME, &m_pTexture[0]);
	if (FAILED(hr)) {
		return hr;
	}

	// �ϐ�������
	ENEMY* pEnemy = m_enemy;
	//ENEMY* pEnemyUFO = m_enemyUFO;
	for (int i = 0; i < MAX_ENEMY_X; ++i, ++pEnemy) 
	{
		pEnemy->nStat = 1;	// �L��
		pEnemy->nDir = 2;
		pEnemy->vVel = XMFLOAT2(0.5f, -20.0f);
		if (i < 11)
		{
			// 3�ԏ�̃^�C�v
			pEnemy->nType = 3;

			pEnemy->vPos = XMFLOAT2(-320.0f + i * 55, 250.0f);
			CreateTextureFromFile(GetDevice(),
				ENEMY_TEXTURENAME, &m_pTexture[i]);
		}
		else if (i>10 && i < 22)
		{
			// 2�ԏ�̃^�C�v
			pEnemy->nType = 2;

			pEnemy->vPos = XMFLOAT2(-925.0f + i * 55, 210.0f);
			CreateTextureFromFile(GetDevice(),
				ENEMY_TEXTURENAME, &m_pTexture[i]);
		}
		else if (i > 21 && i < 33)
		{
			// �Q�ԏ�̃^�C�v
			pEnemy->nType = 2;

			pEnemy->vPos = XMFLOAT2(-1530.0f + i * 55, 170.0f);
			CreateTextureFromFile(GetDevice(),
				ENEMY_TEXTURENAME1, &m_pTexture[i]);
		}
		else if (i > 32 && i < 44)
		{
			// ��ԏ�̃^�C�v
			pEnemy->nType = 1;

			pEnemy->vPos = XMFLOAT2(-2135.0f + i * 55, 130.0f);
			CreateTextureFromFile(GetDevice(),
				ENEMY_TEXTURENAME1, &m_pTexture[i]);
		}
		else if (i > 43 && i < 55)
		{
			// ��ԏ�̃^�C�v
			pEnemy->nType = 1;

			pEnemy->vPos = XMFLOAT2(-2740.0f + i * 55, 90.0f);
			CreateTextureFromFile(GetDevice(),
				ENEMY_TEXTURENAME2, &m_pTexture[i]);
		}
	}
	
	m_nTimer = rand() % FRAME_RATE + FRAME_RATE * 2;

	

	m_nDirection = 0;
	m_nCnt = 0;
	m_nEnemyCnt = 0;
	g_nMoveCnt = 0;

	return hr;
}



//=============================================================================
// �G�̏I������
//=============================================================================
void  CEnemy::Uninit()
{
	for (int i = 0; i < MAX_ENEMY_X; ++i)
	{
		// �e�N�X�`���J��
		SAFE_RELEASE(m_pTexture[i]);
	}
}



//=============================================================================
// �G�̍X�V����
//=============================================================================
void  CEnemy::Update()
{
	ENEMY* pEnemy = m_enemy;
	//ENEMY* pEnemyUFO = m_enemyUFO;
	for (int i = 0; i < MAX_ENEMY_X; ++i, ++pEnemy)
	{
		if (pEnemy->nStat == 0) {
 			m_nEnemyCnt++;
			continue;	// �����Ȃ�X�L�b�v
		}

		// 4��ړ����邽�тɑ�������
		if (g_nMoveCnt <= 4)	// 4�ȉ��̎�
		{
			// �E�����̈ړ�
			if (pEnemy->nDir == 2)
			{
				pEnemy->vPos.x += ENEMY_SPEED_X;
			}
			// �������̈ړ�
			else if (pEnemy->nDir == 1)
			{
				pEnemy->vPos.x -= ENEMY_SPEED_X;
			}
		}
		else if (g_nMoveCnt <= 8)		// 8�ȉ��̎�
		{
			// �E�����̈ړ�
			if (pEnemy->nDir == 2)
			{
				pEnemy->vPos.x += ENEMY_SPEED_X + 0.5f;
			}
			// �������̈ړ�
			else if (pEnemy->nDir == 1)
			{
				pEnemy->vPos.x -= ENEMY_SPEED_X + 0.5f;
			}
		}
		else	// 8�ȏ�̎�
		{
			// �E�����̈ړ�
			if (pEnemy->nDir == 2)
			{
				pEnemy->vPos.x += ENEMY_SPEED_X + 1;
			}
			// �������̈ړ�
			else if (pEnemy->nDir == 1)
			{
				pEnemy->vPos.x -= ENEMY_SPEED_X + 1;
			}
		}

		//������
		if ((pEnemy->vPos.x < -SCREEN_WIDTH / 2 + ENEMY_SIZE_X / 2))
		{
			// �S�Ă����������邽�߂ɏ����ɖ߂�
			pEnemy = m_enemy;
			// ��i�����đS�ĕ�����ς���
			for (int j = 0; j < MAX_ENEMY_X; ++j, ++pEnemy)
			{
				pEnemy->vPos.y -= 20;
				pEnemy->nDir = 2;
			}
			g_nMoveCnt++;
		}

		//�E����
		if ((pEnemy->vPos.x > SCREEN_WIDTH / 2 - ENEMY_SIZE_X / 2))
		{
			// �S�Ă����������邽�߂ɏ����ɖ߂�
			pEnemy = m_enemy;
			for (int j = 0; j < MAX_ENEMY_X; ++j, ++pEnemy)
			{
				// ��i�����đS�ĕ�����ς���
				pEnemy->vPos.y -= 20;
				pEnemy->nDir = 1;
			}
			g_nMoveCnt++;
		}

		
		// ===== �e�ƓG�̓����蔻�� =====
		// �e�̈ʒu�������Ă���
		m_BulletEnemyPos = m_BulletEnemy.GetBulletPos();
		// �����蔻��֐����g��
		CEnemy::CollisionEnemy(m_BulletEnemyPos, 20);
		// ===== �����܂� =====

		// -200�ȉ��ɂȂ�΃Q�[���I�[�o�[
		if (pEnemy->vPos.y < -200)
		{
			// �Q�[���I�[�o�[�V�[���֔��
			SetFadeOut(SCENE_GAMEOVER);
		}
	}

	// �G��55�̓|��������N���A
	if (m_nEnemyCnt == MAX_ENEMY_X)
	{
		SetFadeOut(SCENE_GAMECLEAR);
	}
	else
	{
		m_nEnemyCnt = 0;
	}

	// ============ �G�̒e�̏��� ============
	// �����_���֐����g���ĕ����̓G(3)��I��
	// --------------------------------------
	pEnemy = m_enemy;
	CEnemyBullet EnemyBullet;
	int nCnt;

	for (int i = 0; i < MAX_ENEMYBULLET; i++)
	{
		
		while (1)
		{
			nCnt = rand() % MAX_ENEMY_X;
			if (pEnemy[nCnt].nStat == 1)
			{
				break;
			}
		}
		
		for (int j = 0; j < nCnt; ++j, ++pEnemy)
		{
			if (nCnt - 1 == j)
			{
				EnemyBullet.Fire(&pEnemy->vPos);
			}
		}
	}


	m_nDirection++;
}



//=============================================================================
// �G�̕`�揈��
//=============================================================================
void  CEnemy::Draw()
{
	// �G�`��
	SetPolygonSize(ENEMY_SIZE_X, ENEMY_SIZE_Y);
	SetPolygonFrameSize(1.0f / ENEMY_FRAME_X, 1.0f / ENEMY_FRAME_Y);
	ENEMY* pEnemy = m_enemy;
	//ENEMY* pEnemyUFO = m_enemyUFO;
	for (int i = 0; i < MAX_ENEMY_X; ++i, ++pEnemy) {
		if (pEnemy->nStat == 0) {
			continue;	// �����Ȃ�X�L�b�v
		}
		SetPolygonTexture(m_pTexture[i]);
		SetPolygonPos(pEnemy->vPos.x, pEnemy->vPos.y);
		DrawPolygon(GetDeviceContext());
	}
	// �t���[����߂��Ă���
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}



//=============================================================================
// �G�Ƃ̏Փ˔���
//=============================================================================
int CEnemy::CollisionEnemy( XMFLOAT2 fB, float fBr)
{
	CScore Score;
	ENEMY* pEnemy = m_enemy;
	for (int i = 0; i < MAX_ENEMY_X; ++i, ++pEnemy) 
	{
		if (pEnemy->nStat == 0) {
			continue;	// �����Ȃ�X�L�b�v
		}
		//	�����蔻��
 		if (CollisionCircle(pEnemy->vPos, fB, ENEMY_SIZE_X / 2, fBr))
		{
			// �G������
 			pEnemy->nStat = 0;
			// �G�t�F�N�g
			StartEffect(&pEnemy->vPos, EEFECT_DEAD000);

			if (pEnemy->nType == 1)
			{
				// �X�R�A
				Score.AddScore(10);
			}
			if (pEnemy->nType == 2)
			{
				// �X�R�A
				Score.AddScore(20);
			}
			if (pEnemy->nType == 3)
			{
				// �X�R�A
				Score.AddScore(30);
			}
			

			return i;
		}
		
	}
	return -1;
}

//=============================================================================
// Y���̈ړ��񐔂��擾����
//=============================================================================
int CEnemy::GetMoveCnt()
{
	return g_nMoveCnt;
}


