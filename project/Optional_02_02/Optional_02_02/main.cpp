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

	Vector3 teapotPos;
	teapotPos.y = 20.0f;
	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();		
		
		//ティーポットを動かす。
		teapotPos.x -= g_pad[0]->GetLStickXF();
		teapotPos.z -= g_pad[0]->GetLStickYF();

		//【ハンズオン】プレイヤーを追従するカメラ
		




		//ティーポットのワールド行列を更新する。
		model.UpdateWorldMatrix(teapotPos, g_quatIdentity, g_vec3One);
		//ティーポットをドロー。
		model.Draw(renderContext);
		//背景をドロー。
		bgmodel.Draw(renderContext);
	

		//レンダリング終了。
		g_engine->EndFrame();
	}
	return 0;
}
