//=============================================================================
//
// �e���� [bullet.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "bullet.h"
#include "polygon.h"
#include "Texture.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_TEXTURENAME	L"data/texture/player000.png"	// �e�N�X�`���t�@�C����

#define BULLET_POS_X		0								// �|���S���̕\���ʒu
#define BULLET_POS_Y		0								// �|���S���̕\���ʒu
#define BULLET_SIZE_X		16								// �|���S���̃T�C�Y
#define BULLET_SIZE_Y		16								// �|���S���̃T�C�Y
#define BULLET_FRAME_X		4								// ���t���[����
#define BULLET_FRAME_Y		4								// �c�t���[����
#define BULLET_FRAME_NO		3								// �t���[��No.
#define BULLET_SPEED_X		10								// ���ړ�����
#define BULLET_SPEED_Y		10								// �c�ړ�����

#define BULLET_RADIUS		30.0f
#define BULLET_STRENGTH		1.0f





//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
BULLET CBullet::m_bullet[MAX_BULLET];
CEnemy m_EnemyBullet;


// �R���X�g���N�^/�f�X�g���N�^
CBullet::CBullet(void)
{

}

CBullet::~CBullet(void)
{

}


//=============================================================================
// �e�̏���������
//=============================================================================
HRESULT CBullet::Init()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		BULLET_TEXTURENAME, &m_pTexture);

	// �e��񏉊���
	for (int i = 0; i < MAX_BULLET; ++i) 
	{
		m_bullet[i].nStat = 0;
		m_bullet[i].vPos = XMFLOAT2(10000.0f, 1000.0f);
	}

	return hr;
}

//=============================================================================
// �e�̏I������
//=============================================================================
void CBullet::Uninit()
{
	// �e�N�X�`���J��
	SAFE_RELEASE(m_pTexture);
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void CBullet::Update()
{
	// �e�̍X�V
	BULLET* pBullet = m_bullet;
	for (int i = 0; i < MAX_BULLET; ++i, ++pBullet) {
		if (pBullet->nStat == 0) {
			continue;	// �����Ȃ�X�L�b�v
		}
		// �ړ�
		pBullet->vPos.x += pBullet->vVel.x;
		pBullet->vPos.y += pBullet->vVel.y;
		// ��ʂ̊O�ɏ�������?
		if (pBullet->vPos.x <
			-(SCREEN_WIDTH + BULLET_SIZE_X) / 2.0f ||
			pBullet->vPos.x >=
			(SCREEN_WIDTH + BULLET_SIZE_X) / 2.0f ||
			pBullet->vPos.y <
			-(SCREEN_HEIGHT + BULLET_SIZE_Y) / 2.0f ||
			pBullet->vPos.y >=
			(SCREEN_HEIGHT + BULLET_SIZE_Y) / 2.0f) 
		{
			pBullet->nStat = 0;
			continue;
		}
		if (m_EnemyBullet.CollisionEnemy(pBullet->vPos, 20) >= 0)
		{
			// �\�����Ȃ��悤�ɂ���
			pBullet->nStat = 0;
			// �e�����̏�Ɏc���Ă��܂��̂ŏ�����
			pBullet->vPos = XMFLOAT2(10000.0f, 10000.0f);

			continue;
		}
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
void CBullet::Draw()
{
	// �e�`��
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	SetPolygonSize(BULLET_SIZE_X, BULLET_SIZE_Y);
	SetPolygonTexture(m_pTexture);
	SetPolygonFrameSize(1.0f / BULLET_FRAME_X, 1.0f / BULLET_FRAME_Y);
	int u = BULLET_FRAME_NO % BULLET_FRAME_X;
	int v = BULLET_FRAME_NO / BULLET_FRAME_X;
	SetPolygonUV(u / (float)BULLET_FRAME_X, v / (float)BULLET_FRAME_Y);
	BULLET* pBullet = m_bullet;
	for (int i = 0; i < MAX_BULLET; ++i, ++pBullet) {
		if (!pBullet->nStat) {
			// �����Ȃ玟��
			continue;
		}
		SetPolygonPos(pBullet->vPos.x, pBullet->vPos.y);
		DrawPolygon(pDeviceContext);
	}
	// �t���[����߂��Ă���
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}



//=============================================================================
// �e�̔��ˏ���
//=============================================================================
int CBullet::Fire(XMFLOAT2* pPos)
{
	BULLET* pBullet = m_bullet;
	for (int i = 0; i < MAX_BULLET; ++i, ++pBullet)
	{
		if (pBullet->nStat) {
			// �L���Ȃ�X�L�b�v
			continue;
		}
		// ���ˏ���
		pBullet->vPos = *pPos;

		pBullet->vVel.x = 0.0f;
		pBullet->vVel.y = BULLET_SPEED_Y;

		pBullet->nStat = 1;
		return i;	// ���ː���
	}
	return -1;		// ���˕s��
}



//=============================================================================
// �e�̔��ˏ���
//=============================================================================
XMFLOAT2 CBullet::GetBulletPos()
{
	BULLET* pBullet = m_bullet;
	return pBullet->vPos;
}