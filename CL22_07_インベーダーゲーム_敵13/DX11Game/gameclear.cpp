//=============================================================================
//
// �^�C�g����ʏ��� [gameclear.cpp]
// Author : �O�n�q�M
//
//=============================================================================

// ===== �x���h�~ =====
#define _CRT_SECURE_NO_WARNINGS

//#include "title.h"
#include<stdio.h>
#include<stdlib.h>
#include "gameclear.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"
#include "fade.h"
#include "number.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAMECLEAR_TEXTURENAME	L"data/texture/GameClear.png"	// �e�N�X�`���t�@�C����

#define GAMECLEAR_POS_X		0								// �|���S���̕\���ʒu
#define GAMECLEAR_POS_Y		0								// �|���S���̕\���ʒu
#define GAMECLEAR_SIZE_X		SCREEN_WIDTH					// �|���S���̃T�C�Y
#define GAMECLEAR_SIZE_Y		SCREEN_HEIGHT					// �|���S���̃T�C�Y
#define GAMECLEAR_TIMER		(60+20)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// �e�N�X�`��
static int							g_nTimer;
static int							g_nScoreGameClear;		// �X�R�A�̒l
XMFLOAT2							g_vPosGameClear;		// �����̈ʒu
XMFLOAT2							g_vPosGameClearlastTime;// �O��X�R�A�̐����̈ʒu
CScore								g_ScoreGameClear;		// �X�R�A
int									g_nScoreArra[5];		// �X�R�A�ۑ��p
int									i;

//*****************************************************************************
// �\���̐錾��
//*****************************************************************************
typedef struct TScore
{
	//char szName[10 + 1];	//�L������
	int nScore;				//�̗�

	struct TScore *pNext;	//���̃L�����ւ̃|�C���^

}Score;

//*****************************************************************************
// �֐��v���g�^�C�v�錾
//*****************************************************************************
TScore *readFile(void);
void writeFile(TScore *pData);
void SetData(TScore * pSet);
void SetFillData();

//=============================================================================
// �w�i�\���̏���������
//=============================================================================
HRESULT InitgameClear()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMECLEAR_TEXTURENAME, &g_pTexture);

	g_nTimer = GAMECLEAR_TIMER;

	g_vPosGameClear = XMFLOAT2(-210.0f, 130.0f);
	g_vPosGameClearlastTime = XMFLOAT2(-210.0f, -150.0f);

	TScore *pScore;

	// �t�@�C���̃f�[�^���\���̔z��֓ǂݍ���
	pScore = readFile();

	// �t�@�C���փ��X�g�\���̓��e���o�͂���
	writeFile(pScore);

	// �t�@�C���̒��g��z��ɓ����
	SetData(pScore);

	return hr;
}

//=============================================================================
// �w�i�\���̏I������
//=============================================================================
void UninitgameClear()
{
	//FILE *pFileOut;		// �t�@�C���|�C���^
	//
	//g_nScoreGameClear = g_ScoreGameClear.GetScore();
	//
	//Score ScoreList[1] =
	//{
	//	{ g_nScoreGameClear,NULL},
	//};
	//
	//// �t�@�C���I�[�v��
	//pFileOut = fopen("data/bin/Score.bin", "wb");
	//
	//// �t�@�C���֏����o��		
	//fwrite(ScoreList, sizeof(Score), 1, pFileOut);
	//
	//// �t�@�C���N���[�Y
	//fclose(pFileOut);
	//
	// �e�N�X�`���J��

	SetFillData();

	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// �w�i�\���̍X�V����
//=============================================================================
void UpdategameClear()
{
	// �X�R�A�̒l�������Ă���
	g_nScoreGameClear = g_ScoreGameClear.GetScore();

	// �f�o�b�O�p
	// g_nScoreGameClear = g_nScoreArra[0];

	// �X�y�[�X�L�[����������^�C�g��
	if (GetKeyRelease(VK_SPACE)) 
	{
		if (GetKeyRelease(VK_SPACE)) 
		{
			g_nScoreArra[0] = g_nScoreGameClear;
			SetFadeOut(SCENE_TITLE);
		}
	}
}

//=============================================================================
// �w�i�\������
//=============================================================================
void DrawgameClear()
{
	// �w�i�`��
	SetPolygonPos(GAMECLEAR_POS_X, GAMECLEAR_POS_Y);
	SetPolygonSize(GAMECLEAR_SIZE_X, GAMECLEAR_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());

	SetPolygonColor(0.0f, 1.0f, 0.0f);

	// �X�R�A�\��
	DrawNumber(&g_vPosGameClear,
		(unsigned)g_nScoreGameClear, SCORE_WIDTH,50,100);

	SetPolygonColor(1.0f, 0.0f, 0.0f);

	// �O��p
	DrawNumber(&g_vPosGameClearlastTime,
		(unsigned)g_nScoreArra[0], SCORE_WIDTH,50,100);
}

//=============================================================================
// �t�@�C���ǂݍ��݊֐�
//=============================================================================
TScore *readFile(void)
{
	FILE *pFileIn;		// �t�@�C������ǂݍ��ނ悤�|�C���^
	TScore *pData, *pRoot, *pBackUp;	//�擪�ƂЂƂO�̃|�C���^

	pRoot = NULL; //�擪�f�[�^��������
	pBackUp = NULL;

	// �t�@�C���I�[�v��(�ǂݍ��݃��[�h�A���s������I��)
	if ((pFileIn = fopen("data/bin/Score.bin", "rb")) == NULL)
		exit(EXIT_FAILURE);
	//�f�[�^����f�[�^�������A�J��Ԃ�
	while (1)
	{
		//���I�������m��(�\����party1�f�[�^��)
		pData = (TScore *)malloc(sizeof(TScore));

		// �t�@�C���̃f�[�^��ǂ݂���ō��m�ۂ����������ɂ̂Ɋi�[
		//�������f�[�^���ꌏ���Ȃ���΃������J��
		//0���̃t�@�C���̎��ƃt�@�C����S���ǂݍ��񂾌�
		//							�@ ���f�[�^�̌�
		if ((fread(pData, sizeof(TScore), 1, pFileIn)) < 1) {
			//		���ǂ��ց@��1�f�[�^�̃T�C�Y	�@���ǂ�����

			free(pData);
			pData = NULL;
			break;
		}
		else //�f�[�^��ǂݍ��߂��ꍇ
		{
			//�ꌏ�ڂȂ�A�擪�A�h���X��ۑ�
			if (pRoot == NULL)
			{
				pRoot = pData;
			}
			else//�񌏖ڈȍ~�Ȃ�A1�O�̃f�[�^�ƃ��X�g���Ȃ�
			{
				pBackUp->pNext = pData;
			}

			//�����ڂł����ʏ���
			//pNext��NULL�ɂ��čŏI�f�[�^�̖ڈ����ꂦ��
			//���݂̃f�[�^���o�b�N�A�b�v����(���ɂ̔�����)
			pData->pNext = NULL;
			pBackUp = pData;

		}

	}

	// �t�@�C���N���[�Y
	fclose(pFileIn);

	//�擪�A�h���X����߂�l�Ƃ��ĕԂ�
	return pRoot;
}

//=============================================================================
// �t�@�C���ǂݍ��݊֐�
//=============================================================================
void writeFile(TScore *pData)
{
	FILE *pFileOut;		// �t�@�C���ɏ����o���^�C�v�̃|�C���^
	// �t�@�C���I�[�v��(�����o�����[�h�A�t�@�C���������)
	pFileOut = fopen("party.bin", "wb");

	// ���X�g�\���̏��ԂɃt�@�C���֏o��
	//pData = pRoot;
	while (pData)
	{
		fwrite(pData, sizeof(TScore), 1, pFileOut);
		pData = pData->pNext;	// ���̃f�[�^��
	}

	// �t�@�C���N���[�Y
	fclose(pFileOut);
}

//=============================================================================
// ���X�g�\���\���֐�
//=============================================================================
void SetData(TScore * pSet)
{
	////������NULL�Ȃ�ċA���~�߂Ė߂�
	//if (pSet == NULL)// || g_nCntData == 5)
	//	return;
	//
	//// ���X�g�̏��ԂŔz��ɕۑ�
	//for (int i = 0; i < 5; i++)
	//{
	//	//������NULL�Ȃ�ċA���~�߂Ė߂�
	//	if (pSet == NULL)
	//	{
	//		return;
	//	}
	//	g_nScoreArra[i] = pSet->nScore;
	//	pSet = pSet->pNext;
	//}
	//return;

	//������NULL�Ȃ�ċA���~�߂Ė߂�
	if (pSet == NULL || i == 5)
		return;

	// ���X�g�̏��ԂŔz��ɕۑ�
	g_nScoreArra[i] = pSet->nScore;
	pSet = pSet->pNext;
	i++;

	//�ċA�Ăяo���Ŏ��̃f�[�^��\������
	SetData(pSet);
}

void SetFillData()
{
	FILE *pFileOut;		// �t�@�C���|�C���^

	g_nScoreGameClear = g_ScoreGameClear.GetScore();

	Score ScoreList[1] =
	{
		{ g_nScoreGameClear,NULL},
	};

	// �t�@�C���I�[�v��
	pFileOut = fopen("data/bin/Score.bin", "wb");

	// �t�@�C���֏����o��		
	fwrite(ScoreList, sizeof(Score), 1, pFileOut);

	// �t�@�C���N���[�Y
	fclose(pFileOut);
}