#include "stdafx.h"
#include "system/system.h"
#include "TrianglePolygon.h"


//�֐��錾
void InitRootSignature(RootSignature& rs);

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

	//���[�g�V�O�l�`�����쐬�B
	RootSignature rootSignature;
	InitRootSignature(rootSignature);

	//�O�p�`�|���S�����`�B
	TrianglePolygon triangle;
	triangle.Init(rootSignature);

	//���s�ړ��s��𑗂邽�߂̒萔�o�b�t�@���쐬�B
	ConstantBuffer cb;
	cb.Init(sizeof(Matrix));


	//�f�B�X�N���v�^�q�[�v���쐬�B
	DescriptorHeap ds;	
	ds.RegistConstantBuffer(0, cb);		//�f�B�X�N���v�^�q�[�v�ɒ萔�o�b�t�@��o�^�B
	ds.Commit();						//�f�B�X�N���v�^�q�[�v�ւ̓o�^���m��B

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�t���[���J�n�B
		g_engine->BeginFrame();

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////

		//���[�g�V�O�l�`����ݒ�B
		renderContext.SetRootSignature(rootSignature);

		//���s�ړ��s����쐬�B
		Matrix mTrans;
		mTrans.MakeTranslation(0.5f, 0.4f, 0.0f);
		//���s�ړ��s���萔�o�b�t�@�ɃR�s�[�B
		cb.CopyToVRAM(mTrans);
				

		//�f�B�X�N���v�^�q�[�v��ݒ�B
		renderContext.SetDescriptorHeap(ds);

		//�O�p�`���h���[�B
		triangle.Draw(renderContext);

		/// //////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		//�t���[���I���B
		g_engine->EndFrame();
	}
	return 0;
}


//���[�g�V�O�l�`���̏������B
void InitRootSignature(RootSignature& rs)
{
	rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP);
}
