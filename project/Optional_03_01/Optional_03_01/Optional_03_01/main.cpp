#include "stdafx.h"
#include "system/system.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////
	
	//step-1 ���f�����A�j���[�V���������邽�߂ɕK�v�ȃI�u�W�F�N�g�����ׂĒ�`����B



	//step-2 �X�P���g��������������B



	//step-3 ���f��������������B



	//step-4 �A�j���[�V�����N���b�v�����[�h����B



	//step-10 �A�j���[�V�����N���b�v�Ƀ��[�v�ݒ������B



	//step-5 �A�j���[�V�����̍Đ�����������������B



	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		
		//step-9 �A�j���[�V������؂�ւ���B



		//step-6 �A�j���[�V������i�߂�v���O������ǉ��B



		//step-7 �A�j���[�V�������ʂ����ɃX�P���g�����X�V�B



		//step-8 ���f����`��B


		
		g_engine->EndFrame();
	}

	return 0;
}

