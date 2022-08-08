#include "stdafx.h"
#include "system/system.h"

///////////////////////////////////////////////////////////////////
// 関数宣言
///////////////////////////////////////////////////////////////////
void InitLight(Light& light);
void InitModel(Model& model, Model& bgmodel, Light& light);
void RotateLight(Light& light);

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////

	//カメラの初期化。
	g_camera3D->SetPosition({ 0.0f, 70.0f, 150.0f });
	g_camera3D->SetTarget({ 0.0f, 70.0f, 0.0f });

	//ライトのデータを作成する。
	Light light;
	InitLight(light);

	//モデルを初期化する。
	Model model, bgmodel;
	InitModel(model, bgmodel, light);

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();		
		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////

		//step-1 キー入力で注視点を左右に動かす。
		Vector3 moveTarget;
		if (g_pad[0]->IsPress(enButtonLeft)) {
			//
			moveTarget.x = 1.0f;
		}
		if (g_pad[0]->IsPress(enButtonRight)) {
			moveTarget.x = -1.0f;
		}
		//注視点を動かす。
		g_camera3D->MoveTarget(moveTarget);

		//step-2 キー入力で視点を左右に動かす。
		Vector3 movePosition;
		if (g_pad[0]->IsPress(enButtonUp)) {
			movePosition.x = 1.0f;
		}
		if (g_pad[0]->IsPress(enButtonDown)) {
			movePosition.x = -1.0f;
		}
		//視点を動かす。
		g_camera3D->MovePosition(movePosition);

		//ライトを回す。
		RotateLight( light );
		
		//ティーポットをドロー。
		model.Draw(renderContext);
		//背景をドロー。

		bgmodel.Draw(renderContext);
		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		//レンダリング終了。
		g_engine->EndFrame();
	}
	return 0;
}
