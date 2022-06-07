//=============================================================================
//
// �V�[���J�ڏ��� [scene.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "gameover.h"
#include "gameclear.h"
#include "gameclear02.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int 	g_nScene = SCENE_NOTE;				// ���݂̃V�[��

//=============================================================================
// �V�[���̏���������
//=============================================================================
HRESULT InitScene()
{
	SetScene(SCENE_GAMECLEAR);// SCENE_TITLE);			// �ŏ��̓^�C�g�����
	return S_OK;
}

//=============================================================================
// �V�[���̏I������
//=============================================================================
void UninitScene()
{
	UninitgameClear();

	SetScene(SCENE_NOTE);			// ���݂̃V�[�����I��
}

//=============================================================================
// �V�[���̍X�V����
//=============================================================================
void UpdateScene()
{
	switch (g_nScene) 
	{
	case SCENE_TITLE:		// �^�C�g�����
		UpdateTitle();
		break;

	case SCENE_GAME:		// �Q�[�����
		UpdateGame();
		break;

	case SCENE_GAMEOVER:		// �Q�[�����
		Updategameover();
		break;

	case SCENE_GAMECLEAR:		// �Q�[���N���A���
		UpdateGameClear02();
		break;

	case SCENR_RANKING:			// �����L���O
		UpdategameClear();
		break;
	}
}

//=============================================================================
// �V�[���`�揈��
//=============================================================================
void DrawScene()
{
	switch (g_nScene)
	{
	case SCENE_TITLE:		// �^�C�g�����
		DrawTitle();
		break;

	case SCENE_GAME:		// �Q�[�����
		DrawGame();
		break;

	case SCENE_GAMEOVER:		// �Q�[�����
		Drawgameover();
		break;

	case SCENE_GAMECLEAR:		// �Q�[���N���A���
		DrawGameClear02();
		break;

	case SCENR_RANKING:
		DrawgameClear();
		break;
	}
}

//=============================================================================
// �V�[���؂�ւ�����
//=============================================================================
void SetScene(int nScene)
{
	// ���݂̃V�[�����I��
	switch (nScene)
	{
	case SCENE_TITLE:	// �^�C�g�����
		UninitTitle();
		break;

	case SCENE_GAME:	// �Q�[�����
		UninitGame();
		break;

	case SCENE_GAMEOVER:	// �Q�[�����
		Uninitgameover();
		break;

	case SCENE_GAMECLEAR:		// �Q�[���N���A���
		UninitGameClear02();
		break;

	case SCENR_RANKING:
		UninitgameClear();
		break;
	}
	g_nScene = nScene;
	// ���̃V�[����������
	switch (nScene)
	{
	case SCENE_TITLE:	// �^�C�g�����
		InitTitle();
			break;

	case SCENE_GAME:	// �Q�[�����
		InitGame();
			break;

	case SCENE_GAMEOVER:	// �Q�[�����
		Initgameover();
		break;

	case SCENE_GAMECLEAR:		// �Q�[���N���A���
		InitGameClear02();
		break;

	case SCENR_RANKING:
		InitgameClear();
		break;
	}
}
