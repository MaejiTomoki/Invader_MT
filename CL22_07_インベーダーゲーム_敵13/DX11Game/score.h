//=============================================================================
//
// �X�R�A�\������ [score.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FRAME_TEXTURENAME	L"data/texture/frame_score.png"	// �e�N�X�`���t�@�C����

#define FRAME_SIZE_X		340								// �|���S���̃T�C�Y
#define FRAME_SIZE_Y		80								// �|���S���̃T�C�Y
#define FRAME_POS_X			\
(SCREEN_WIDTH/2-FRAME_SIZE_X/2)	// �|���S���̕\���ʒu
#define FRAME_POS_Y			\
(SCREEN_HEIGHT/2-FRAME_SIZE_Y/2)// �|���S���̕\���ʒu

#define SCORE_SIZE_X		35								// �����̃T�C�Y
#define SCORE_SIZE_Y		50								// �����̃T�C�Y
#define SCORE_WIDTH			8								// �\������
#define SCORE_POS_X			\
(FRAME_POS_X-SCORE_SIZE_X*(SCORE_WIDTH/2))// �����̕\���ʒu
#define SCORE_POS_Y			\
(FRAME_POS_Y+SCORE_SIZE_Y/2-8)	// �����̕\���ʒu



//=============================================================================
// �N���X
//=============================================================================
class CScore
{
private:
	// �����o�ϐ�
	ID3D11ShaderResourceView*	m_pTexture;				// �e�N�X�`��
	static int							m_nScore;
	XMFLOAT2						m_vPos;				// �����̈ʒu
protected:

public:
	// �R���X�g���N�^/�f�X�g���N�^
	CScore(void);
	~CScore(void);

	// �l�又��
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// �X�R�A�擾
	int GetScore();

	// �X�R�A���Z
	void AddScore(int nValue);	
};




