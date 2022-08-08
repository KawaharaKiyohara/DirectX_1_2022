#include "stdafx.h"
#include "system/system.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//step-1 3D���f�������[�h����B
	//���[�h���邽�߂̏����������쐬�B
	ModelInitData initData;
	//tkm�t�@�C���̃t�@�C���p�X�B
	initData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	//�g�p����V�F�[�_�[�̃t�@�C���p�X�B
	initData.m_fxFilePath = "Assets/shader/Sample.fx";
	//�쐬���������������g���āA����������B
	Model charaModel;
	charaModel.Init(initData);

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//step-3 �L�����̈ʒu�A��]�A�g�嗦��\���ϐ����`����B
	Vector3 pos;
	Quaternion rot;
	Vector3 scale;
	//�g�嗦��x�Ay�Az��1�ŏ��������Ă����B
	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////

		//step-4 �R���g���[���[�̓��͂ŃL�����𓮂����B
		pos.x += g_pad[0]->GetLStickXF();

		//step-5 �R���g���[���[�̓��͂ŃL������Y������ɉ�]������B
		Quaternion addRot;
		addRot.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f );
		//�N�H�[�^�j�I���͊|���Z�ŉ�]�������ł���B
		rot *= addRot ;

		//step-6 �R���g���[���[�̓��͂ŃL������X�������Ɋg�傳����B
		if (g_pad[0]->IsPress(enButtonLeft)) {
			scale.x += 0.01f;
		}
		if (g_pad[0]->IsPress(enButtonRight)) {
			scale.x -= 0.01f;
		}

		//step-7 ���s�ړ��A��]�A�g�嗦�𗘗p���ă��[���h�s����v�Z����B
		charaModel.UpdateWorldMatrix(pos, rot, scale);

		//step-2 3D���f�����h���[����B
		charaModel.Draw(renderContext);


		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		//�����_�����O�I���B
		g_engine->EndFrame();
	}
	return 0;
}