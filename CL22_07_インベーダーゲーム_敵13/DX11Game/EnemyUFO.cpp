//=============================================================================
//
// �G���� [enemy.cpp]
// Author : �O�n�q�M
//
//=============================================================================
#include "enemyUFO.h"
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "collision.h"
#include "effect.h"
#include "score.h"
#include "EnemyBuller.h"
#include "fade.h"
#include "scene.h"
#include "enemy.h"




//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CBullet				g_BulletEnemyUFO;
XMFLOAT2			g_BulletEnemyUFOPos;
CEnemy				g_CEnemyUFO;
int					g_CEnemyUFOMoveCnt;
ENEMYUFO CEnemyUFO::m_enemyUFO[MAX_ENEMY_UFO_UFO];


// �R���X�g���N�^/�f�X�g���N�^
CEnemyUFO::CEnemyUFO(void)
{

}
CEnemyUFO::~CEnemyUFO(void)
{

}



//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemyUFO::Init()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		ENEMY_TEXTURENAME, &m_pTextureUFO[0]);
	if (FAILED(hr)) {
		return hr;
	}

	// �ϐ�������
	ENEMYUFO* pEnemyUFO = m_enemyUFO;
	
	for (int i = 0; i < MAX_ENEMY_UFO_UFO; ++i, ++pEnemyUFO)
	{
		pEnemyUFO->nStat = 1;	// �L��
		pEnemyUFO->nDir = 2;
		pEnemyUFO->vVel = XMFLOAT2(0.5f, -20.0f);
		pEnemyUFO->vPos = XMFLOAT2(-1320.0f + i * 55, 1250.0f);
		CreateTextureFromFile(GetDevice(), ENEMY_TEXTURENAME_UFO, &m_pTextureUFO[i]);
	}

	return hr;
}



//=============================================================================
// �G�̏I������
//=============================================================================
void  CEnemyUFO::Uninit()
{
	for (int i = 0; i < MAX_ENEMY_UFO_UFO; ++i)
	{
		// �e�N�X�`���J��
		SAFE_RELEASE(m_pTextureUFO[i]);
	}
}



//=============================================================================
// �G�̍X�V����
//=============================================================================
void  CEnemyUFO::Update()
{
	ENEMYUFO* pEnemyUFO = m_enemyUFO;
	
	// �x���̈ړ��񐔂������Ă���
	g_CEnemyUFOMoveCnt = g_CEnemyUFO.GetMoveCnt();

	// UFO�̏���
	for (int i = 0; i < MAX_ENEMY_UFO_UFO; ++i, ++pEnemyUFO)
	{
		if (pEnemyUFO->nStat == 0) {
			continue;	// �����Ȃ�X�L�b�v
		}

		// 2��ړ����邽�т�UFO�o��
		if ( g_CEnemyUFOMoveCnt == 1)		// 2��ړ������̎�
		{
			if (i == 0)
			{
				pEnemyUFO->vPos = XMFLOAT2(-420.0f, 250.0f);
			}
		}
		else if (g_CEnemyUFOMoveCnt == 3)		// 2��ړ������̎�
		{
			if (i == 1)
			{
				pEnemyUFO->vPos = XMFLOAT2(-520.0f, 250.0f);
			}
		}
		else if (g_CEnemyUFOMoveCnt == 4)		// 2��ړ������̎�
		{
			if (i == 2)
			{
				pEnemyUFO->vPos = XMFLOAT2(-920.0f, 250.0f);
			}
		}
		else if (g_CEnemyUFOMoveCnt == 7)		// 2��ړ������̎�
		{
			if (i == 3)
			{
				pEnemyUFO->vPos = XMFLOAT2(-420.0f, 250.0f);
			}
		}
		else if (g_CEnemyUFOMoveCnt == 9)		// 2��ړ������̎�
		{
			if (i == 4)
			{
				pEnemyUFO->vPos = XMFLOAT2(-820.0f, 250.0f);
			}
		}
		// �E�����̈ړ�
		if (pEnemyUFO->nDir == 2)
		{
			pEnemyUFO->vPos.x += ENEMY_SPEED_X * 8;
		}
		// �������̈ړ�
		else if (pEnemyUFO->nDir == 1)
		{
			pEnemyUFO->vPos.x -= ENEMY_SPEED_X + 1;
		}
	}
	// ===== �e�ƓG�̓����蔻�� =====
		// �e�̈ʒu�������Ă���
	g_BulletEnemyUFOPos = g_BulletEnemyUFO.GetBulletPos();
	// �����蔻��֐����g��
	CEnemyUFO::CollisionEnemyUFO(g_BulletEnemyUFOPos, 20);
	// ===== �����܂� =====
}



//=============================================================================
// �G�̕`�揈��
//=============================================================================
void  CEnemyUFO::Draw()
{
	// �G�`��
	SetPolygonSize(ENEMY_UFO_SIZE_X, ENEMY_UFO_SIZE_Y);
	SetPolygonFrameSize(1.0f / ENEMY_UFO_FRAME_X, 1.0f / ENEMY_UFO_FRAME_Y);
	ENEMYUFO* pEnemyUFO = m_enemyUFO;
	for (int i = 0; i < MAX_ENEMY_UFO_UFO; ++i, ++pEnemyUFO) {
		if (pEnemyUFO->nStat == 0) {
			continue;	// �����Ȃ�X�L�b�v
		}
		SetPolygonTexture(m_pTextureUFO[i]);
		SetPolygonPos(pEnemyUFO->vPos.x, pEnemyUFO->vPos.y);
		DrawPolygon(GetDeviceContext());
	}
	// �t���[����߂��Ă���
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}




//=============================================================================
// �G�Ƃ̏Փ˔���
//=============================================================================
int CEnemyUFO::CollisionEnemyUFO(XMFLOAT2 fB, float fBr)
{
	CScore Score;
	ENEMYUFO* pEnemyUFO = m_enemyUFO;
	for (int i = 0; i < MAX_ENEMY_UFO_UFO; ++i, ++pEnemyUFO)
	{
		if (pEnemyUFO->nStat == 0) {
			continue;	// �����Ȃ�X�L�b�v
		}
		//	�����蔻��
		if (CollisionCircle(pEnemyUFO->vPos, fB, ENEMY_SIZE_X / 2, fBr))
		{
			// �G������
			pEnemyUFO->nStat = 0;
			// �G�t�F�N�g
			StartEffect(&pEnemyUFO->vPos, EEFECT_DEAD000);
			// �X�R�A
			Score.AddScore(100);

			return i;
		}

	}
	return -1;
}
