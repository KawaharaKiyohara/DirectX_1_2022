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

	Vector3 teapotPos;
	teapotPos.y = 20.0f;
	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();		
		
		//�e�B�[�|�b�g�𓮂����B
		teapotPos.x -= g_pad[0]->GetLStickXF();
		teapotPos.z -= g_pad[0]->GetLStickYF();

		//�y�n���Y�I���z�v���C���[��Ǐ]����J����
		




		//�e�B�[�|�b�g�̃��[���h�s����X�V����B
		model.UpdateWorldMatrix(teapotPos, g_quatIdentity, g_vec3One);
		//�e�B�[�|�b�g���h���[�B
		model.Draw(renderContext);
		//�w�i���h���[�B
		bgmodel.Draw(renderContext);
	

		//�����_�����O�I���B
		g_engine->EndFrame();
	}
	return 0;
}
