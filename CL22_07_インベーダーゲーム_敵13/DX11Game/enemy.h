//=============================================================================
//
// �G���� [enemy.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"
#include "bullet.h"



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_TEXTURENAME			L"data/texture/enemy1.png"		// �e�N�X�`���t�@�C����
#define ENEMY_TEXTURENAME1			L"data/texture/enemy2.png"		// �e�N�X�`���t�@�C����
#define ENEMY_TEXTURENAME2			L"data/texture/enemy3.png"		// �e�N�X�`���t�@�C����
#define ENEMY_TEXTURENAME_1			L"data/texture/enemy1_2.png"	// �e�N�X�`���t�@�C����
#define ENEMY_TEXTURENAME1_1		L"data/texture/enemy2._2png"	// �e�N�X�`���t�@�C����
#define ENEMY_TEXTURENAME2_1		L"data/texture/enemy3_2.png"	// �e�N�X�`���t�@�C����


#define	ENEMY_POS_X			0								// �|���S���̕\���ʒu
#define	ENEMY_POS_Y			0								// �|���S���̕\���ʒu
#define	ENEMY_SIZE_X		50								// �|���S���̃T�C�Y
#define	ENEMY_SIZE_Y		50								// �|���S���̃T�C�Y
#define ENEMY_FRAME_X		1								// ���t���[����
#define ENEMY_FRAME_Y		1								// �c�t���[����
#define ENEMY_SPEED_X		0.5f							// ���ړ�����
#define ENEMY_SPEED_Y		0.5f							// �c�ړ�����

#define ENEMY_RADIUS		28

#define MAX_ENEMY_X			55
#define MAX_ENEMY_Y			5

//#define MAX_ENEMY_UFO		5



//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct {
	int			nType;		// ���(0:�X���C��)
	int			nStat;		// ���(0:����,1:�L��)
	int			nDir;		// ����(0:��,1:��,2:�E,3:��)
	int			nTimer;		// �����ύX�p
	int			nAnim;		// �Đ��ʒu
	int			nCount;		// �Đ��t���[����
	int			nDirStat;
	XMFLOAT2	vPos;		// ���W
	XMFLOAT2	vVel;		// ���x
} ENEMY;


class CEnemy
{
private:
	
protected:

public:
	// �R���X�g���N�^/�f�X�g���N�^
	CEnemy(void);
	~CEnemy(void);

	//	�l�又��
	HRESULT Init();
	void	Uninit();
	void	Update();
	void	Draw();

	int CollisionEnemy(XMFLOAT2 fB, float fBr);
	int GetMoveCnt();			// Y���̈ړ���

	// �ϐ�
	ID3D11ShaderResourceView*	m_pTexture[MAX_ENEMY_X];				// �e�N�X�`��
	//ID3D11ShaderResourceView*	m_pTextureUFO[MAX_ENEMY_UFO];				// �e�N�X�`��UFO
	static ENEMY m_enemy[MAX_ENEMY_X];	// �G���
	//static ENEMY m_enemyUFO[MAX_ENEMY_UFO];	// �G���(UFO)
	int m_nTimer;				// �G�����^�C�}�[
	int m_nDirection;			// �G�̌������ړ���
	int m_nCnt;					// �G�̓����̃J�E���g
	int m_nEnemyCnt;			// �G�̃J�E���g��
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************



