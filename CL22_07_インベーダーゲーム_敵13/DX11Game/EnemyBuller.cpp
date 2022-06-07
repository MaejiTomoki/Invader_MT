//=============================================================================
//
// �e���� [bullet.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "EnemyBuller.h"
#include "polygon.h"
#include "Texture.h"
#include "player.h"
//#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMYBULLET_TEXTURENAME	L"data/texture/player000.png"	// �e�N�X�`���t�@�C����

#define ENEMYBULLET_POS_X		0								// �|���S���̕\���ʒu
#define ENEMYBULLET_POS_Y		0								// �|���S���̕\���ʒu
#define ENEMYBULLET_SIZE_X		16								// �|���S���̃T�C�Y
#define ENEMYBULLET_SIZE_Y		16								// �|���S���̃T�C�Y
#define ENEMYBULLET_FRAME_X		4								// ���t���[����
#define ENEMYBULLET_FRAME_Y		4								// �c�t���[����
#define ENEMYBULLET_FRAME_NO		3								// �t���[��No.
#define ENEMYBULLET_SPEED_X		7								// ���ړ�����
#define ENEMYBULLET_SPEED_Y		7								// �c�ړ�����

#define ENEMYBULLET_RADIUS		30.0f
#define ENEMYBULLET_STRENGTH		1.0f





//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ENEMYBULLET CEnemyBullet::m_EnemyBullet[MAX_ENEMYBULLET];
CPlayer m_PlayerColl;


// �R���X�g���N�^/�f�X�g���N�^
CEnemyBullet::CEnemyBullet(void)
{

}

CEnemyBullet::~CEnemyBullet(void)
{

}


//=============================================================================
// �e�̏���������
//=============================================================================
HRESULT CEnemyBullet::Init()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		ENEMYBULLET_TEXTURENAME, &m_pTexture);

	// �e��񏉊���
	for (int i = 0; i < MAX_ENEMYBULLET; ++i)
	{
		m_EnemyBullet[i].nStat = 0;
		m_EnemyBullet[i].vPos = XMFLOAT2(10000.0f, 10000.0f);
	}

	return hr;
}

//=============================================================================
// �e�̏I������
//=============================================================================
void CEnemyBullet::Uninit()
{
	// �e�N�X�`���J��
	SAFE_RELEASE(m_pTexture);
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void CEnemyBullet::Update()
{
	// �e�̍X�V
	ENEMYBULLET* pEnemyBullet = m_EnemyBullet;
	
	for (int i = 0; i < MAX_ENEMYBULLET; ++i, ++pEnemyBullet) {
		if (pEnemyBullet->nStat == 0) {
			continue;	// �����Ȃ�X�L�b�v
		}
		// �ړ�
		pEnemyBullet->vPos.x += pEnemyBullet->vVel.x;
		pEnemyBullet->vPos.y += pEnemyBullet->vVel.y;
		// ��ʂ̊O�ɏ�������?
		if (pEnemyBullet->vPos.x <
			-(SCREEN_WIDTH + ENEMYBULLET_SIZE_X) / 2.0f ||
			pEnemyBullet->vPos.x >=
			(SCREEN_WIDTH + ENEMYBULLET_SIZE_X) / 2.0f ||
			pEnemyBullet->vPos.y <
			-(SCREEN_HEIGHT + ENEMYBULLET_SIZE_Y) / 2.0f ||
			pEnemyBullet->vPos.y >=
			(SCREEN_HEIGHT + ENEMYBULLET_SIZE_Y) / 2.0f) 
		{
			pEnemyBullet->nStat = 0;
			continue;
		}

		//if (m_PlayerColl.CollisionPlayer(pEnemyBullet->vPos, 10) >= 0)
		//{
		//	// �\�����Ȃ��悤�ɂ���
		//	pEnemyBullet->nStat = 0;
		//	// �e�����̏�Ɏc���Ă��܂��̂ŏ�����
		//	pEnemyBullet->vPos = XMFLOAT2(10000.0f, 10000.0f);

		//	continue;
		//}
		// �G�Ƃ̓����蔻��
		//if (CollisionEnemy(pBullet->vPos.x,pBullet->vPos.y, 
		//	BULLET_RADIUS,BULLET_STRENGTH, nullptr, nullptr) >= 0) 
		//{
		//	pBullet->nStat = 0;
		//	continue;
		//}
	}
}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void CEnemyBullet::Draw()
{
	// �e�`��
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	SetPolygonSize(ENEMYBULLET_SIZE_X, ENEMYBULLET_SIZE_Y);
	SetPolygonTexture(m_pTexture);
	SetPolygonFrameSize(1.0f / ENEMYBULLET_FRAME_X, 1.0f / ENEMYBULLET_FRAME_Y);
	int u = ENEMYBULLET_FRAME_NO % ENEMYBULLET_FRAME_X;
	int v = ENEMYBULLET_FRAME_NO / ENEMYBULLET_FRAME_X;
	SetPolygonUV(u / (float)ENEMYBULLET_FRAME_X, v / (float)ENEMYBULLET_FRAME_Y);

	ENEMYBULLET* pEnemyBullet = m_EnemyBullet;
	for (int i = 0; i < MAX_ENEMYBULLET; ++i, ++pEnemyBullet) {
		if (!pEnemyBullet->nStat) {
			// �����Ȃ玟��
			continue;
		}
		SetPolygonPos(pEnemyBullet->vPos.x, pEnemyBullet->vPos.y);
		DrawPolygon(pDeviceContext);
	}
	// �t���[����߂��Ă���
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}



//=============================================================================
// �e�̔��ˏ���
//=============================================================================
int CEnemyBullet::Fire(XMFLOAT2* pPos)
{
	ENEMYBULLET* pEnemyBullet = m_EnemyBullet;
	for (int i = 0; i < MAX_ENEMYBULLET; ++i, ++pEnemyBullet)
	{
		if (pEnemyBullet->nStat) {
			// �L���Ȃ�X�L�b�v
			continue;
		}
		// ���ˏ���
		pEnemyBullet->vPos = *pPos;

		pEnemyBullet->vVel.x = 0.0f;
		pEnemyBullet->vVel.y = -ENEMYBULLET_SPEED_Y;

		pEnemyBullet->nStat = 1;
		return i;	// ���ː���
	}
	return -1;		// ���˕s��
}



//=============================================================================
// �e�̈ʒu�擾
//=============================================================================
XMFLOAT2 CEnemyBullet::GetEnemyBulletPos()
{
	ENEMYBULLET* pEnemyBullet = m_EnemyBullet;
	return pEnemyBullet->vPos;
}


