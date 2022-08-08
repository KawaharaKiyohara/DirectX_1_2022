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
	Skeleton skeleton;						//�@ �X�P���g���B
	Model model;								//�A ���f���\�������B
	AnimationClip animationClips[2];		//�B �A�j���[�V�����N���b�v�B
	Animation animation;					//�C �A�j���V�����Đ������B
	

	//step-2 �X�P���g��������������B
	//Skeleton�N���X��Init�֐����Ăяo���Ă���B
	//�������̓X�P���g���f�[�^�̃t�@�C���p�X�B
	skeleton.Init("Assets/modelData/unityChan.tks");

	//step-3 ���f��������������B
	ModelInitData initData;
	//tkm�t�@�C���̃t�@�C���p�X���w�肷��B
	initData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	//�V�F�[�_�[�t�@�C���̃t�@�C���p�X���w�肷��B
	initData.m_fxFilePath = "Assets/shader/model.fx";
	//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
	initData.m_vsEntryPointFunc = "VSMain";
	//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
	initData.m_vsSkinEntryPointFunc = "VSSkinMain";
	//�X�P���g�����w�肷��B
	initData.m_skeleton = &skeleton;

	//���f���̏�������w�肷��B
	//3dsMax�ł̓f�t�H���gZ�A�b�v�ɂȂ��Ă��邪�A
	//���j�e�B�����̓A�j���[�V������Y�A�b�v�ɕύX����Ă���B
	initData.m_modelUpAxis = enModelUpAxisY;

	//Model�N���X��Init�֐���initData��n���ă��f��������������A
	model.Init(initData);

	//step-4 �A�j���[�V�����N���b�v�����[�h����B
	animationClips[0].Load("Assets/animData/idle.tka");
	animationClips[1].Load("Assets/animData/walk.tka");

	//step-10 �A�j���[�V�����N���b�v�Ƀ��[�v�ݒ������B
	//�����N���b�v�Ƀ��[�v�ݒ������B	
	animationClips[1].SetLoopFlag(true);

	//step-5 �A�j���[�V�����̍Đ�����������������B
	//�A�j���[�V�������������B
	animation.Init(
		skeleton,				//�A�j���[�V�����𗬂����ރX�P���g���B
		animationClips,		//�A�j���[�V�����N���b�v�B
		2							//�A�j���[�V�����̐��B
	);

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
		if (g_pad[0]->IsPress(enButtonA) ){
			//Assets/animData/idle.tka�𗬂��B
			animation.Play(0);
		}
		if (g_pad[0]->IsPress(enButtonB)) {
			//Assets/animData/walk.tka�𗬂��B
			animation.Play(1);
		}
		//step-6 �A�j���[�V������i�߂�v���O������ǉ��B
		//Animation�N���X��Progress()���Ăяo���ƃA�j���[�V�������i�ށB
		//�������͐i�߂鎞�ԁB�P�ʂ͕b�B
		//����̃v���O�����ł́A���t���[���A1 �� 60 = 0.016�b�A�j���[�V�������i�ށB
		animation.Progress(1.0/60.0f);

		//step-7 �A�j���[�V�������ʂ����ɃX�P���g�����X�V�B
		//Skeleton�N���X��Update()���Ăяo���ƁA
		//�X�P���g���̍��ɃA�j���[�V�����̍Đ����ʂ��������܂�܂��B
		//�������ɂ̓A�j���[�V�����𗬂����f���̃��[���h�s����w�肵�܂��B
		skeleton.Update(
			model.GetWorldMatrix()
		);
		
		//step-8 ���f����`��B
		model.Draw(renderContext);

		g_engine->EndFrame();
	}

	return 0;
}

