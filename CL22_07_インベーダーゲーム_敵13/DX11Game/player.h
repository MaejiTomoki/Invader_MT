//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �O�n�q�M
//
//=============================================================================
#pragma once

#include "main.h"



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_TEXTURENAME	L"data/texture/Player.png"	// �e�N�X�`���t�@�C����

#define	PLAYER_POS_X		0								// �|���S���̕\���ʒu
#define	PLAYER_POS_Y		-SCREEN_CENTER_Y + 100			// �|���S���̕\���ʒu
#define	PLAYER_SIZE_X		64								// �|���S���̃T�C�Y
#define	PLAYER_SIZE_Y		64								// �|���S���̃T�C�Y
#define PLAYER_FRAME_X		4								// ���t���[����
#define PLAYER_FRAME_Y		4								// �c�t���[����
#define PLAYER_SPEED_X		3			// ���ړ�����
#define PLAYER_SPEED_Y		2			// �c�ړ�����

#define PLAYER_RADIUS		28			// �����蔻��H

#define PLAYER_HP_SIZE_X	32								// HP�̉摜�p
#define PLAYER_HP_SIZE_Y	32								// 
#define PLAYER_HP_POS_X		\
(-SCREEN_WIDTH/2+PLAYER_HP_SIZE_X)
#define PLAYER_HP_POS_Y		\
(SCREEN_HEIGHT/2-PLAYER_HP_SIZE_Y)




//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct {
	int nPatNo;		// �\���p�^�[���ԍ�
	int nCount;		// �\���t���[����
} ANIM_PAT;



class CPlayer
{
private:

protected:

public:
	// �R���X�g���N�^/�f�X�g���N�^
	CPlayer(void);
	~CPlayer(void);

	// �l�又��
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// �v���C���[�̈ʒu�擾
	XMFLOAT2 GetPlayerPos(void);

	// �v���C���[�̃T�C�Y�擾
	XMFLOAT2 GetPlayerSixe(void);

	// �v���C���[�̓����蔻��
	int CollisionPlayer(XMFLOAT2 fB, float fBr);


	// �����o�ϐ�
	ID3D11ShaderResourceView*	m_pTexture;			// �e�N�X�`��

	int				m_nDir;							// ����(0:��,1:��,2:�E,3:��)
	XMFLOAT2		m_vPos;							// ���W
	int				m_nStat;						// ��ԁi0:����1:�L���j
	int				m_nHP;							// �v���C���[�̗̑�
	int				m_nCntHP;						// �����Ԗ��G
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

