#include "stdafx.h"
#include "system/system.h"

///////////////////////////////////////////////////////////////////
// �֐��錾
///////////////////////////////////////////////////////////////////
void InitLight(Light& light);
void InitModel(Model& model, Model& bgmodel, Light& light);
void RotateLight(Light& light);

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

	//�J�����̏������B
	g_camera3D->SetPosition({ 0.0f, 70.0f, 150.0f });
	g_camera3D->SetTarget({ 0.0f, 70.0f, 0.0f });

	//���C�g�̃f�[�^���쐬����B
	Light light;
	InitLight(light);

	//���f��������������B
	Model model, bgmodel;
	InitModel(model, bgmodel, light);

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();		
		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////

		//step-1 �L�[���͂Œ����_�����E�ɓ������B
		Vector3 moveTarget;
		if (g_pad[0]->IsPress(enButtonLeft)) {
			//
			moveTarget.x = 1.0f;
		}
		if (g_pad[0]->IsPress(enButtonRight)) {
			moveTarget.x = -1.0f;
		}
		//�����_�𓮂����B
		g_camera3D->MoveTarget(moveTarget);

		//step-2 �L�[���͂Ŏ��_�����E�ɓ������B
		Vector3 movePosition;
		if (g_pad[0]->IsPress(enButtonUp)) {
			movePosition.x = 1.0f;
		}
		if (g_pad[0]->IsPress(enButtonDown)) {
			movePosition.x = -1.0f;
		}
		//���_�𓮂����B
		g_camera3D->MovePosition(movePosition);

		//���C�g���񂷁B
		RotateLight( light );
		
		//�e�B�[�|�b�g���h���[�B
		model.Draw(renderContext);
		//�w�i���h���[�B

		bgmodel.Draw(renderContext);
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		//�����_�����O�I���B
		g_engine->EndFrame();
	}
	return 0;
}
