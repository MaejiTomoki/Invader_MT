//=============================================================================
//
// �G���� [enemyUFO.h]
// Author : �O�n�q�M
//
//=============================================================================
#pragma once

#include "main.h"
#include "bullet.h"



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_TEXTURENAME_UFO		L"data/texture/UFO.png"			// �e�N�X�`���t�@�C����


#define	ENEMY_UFO_POS_X			0								// �|���S���̕\���ʒu
#define	ENEMY_UFO_POS_Y			0								// �|���S���̕\���ʒu
#define	ENEMY_UFO_SIZE_X		50								// �|���S���̃T�C�Y
#define	ENEMY_UFO_SIZE_Y		50								// �|���S���̃T�C�Y
#define ENEMY_UFO_FRAME_X		1								// ���t���[����
#define ENEMY_UFO_FRAME_Y		1								// �c�t���[����
#define ENEMY_UFO_SPEED_X		0.5f							// ���ړ�����
#define ENEMY_UFO_SPEED_Y		0.5f							// �c�ړ�����

#define ENEMY_UFO_RADIUS		28

#define MAX_ENEMY_UFO_X			55
#define MAX_ENEMY_UFO_Y			5
				 
#define MAX_ENEMY_UFO_UFO		5



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
	int			nMoveCnt;	// Y(�c)�̈ړ���
	XMFLOAT2	vPos;		// ���W
	XMFLOAT2	vVel;		// ���x
} ENEMYUFO;


class CEnemyUFO
{
private:

protected:

public:
	// �R���X�g���N�^/�f�X�g���N�^
	CEnemyUFO(void);
	~CEnemyUFO(void);

	//	�l�又��
	HRESULT Init();
	void	Uninit();
	void	Update();
	void	Draw();

	int CollisionEnemyUFO(XMFLOAT2 fB, float fBr);

	// �ϐ�
	ID3D11ShaderResourceView*	m_pTextureUFO[MAX_ENEMY_UFO_UFO];				// �e�N�X�`��UFO
	static ENEMYUFO m_enemyUFO[MAX_ENEMY_UFO_UFO];	// �G���(UFO)
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************



