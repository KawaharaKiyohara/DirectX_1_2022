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
		//現在のカメラの視点を取得する。
		Vector3 cameraPos = g_camera3D->GetPosition();
		//現在のカメラのターゲットを取得する。
		Vector3 cameraTarget = g_camera3D->GetTarget();
		//視点から注視点に向かって伸びるベクトルを計算する。
		Vector3 toCameraPos = cameraPos - cameraTarget;
		//新しい注視点をティーポットの少し上に設定する。
		cameraTarget = teapotPos;
		cameraTarget.y = 50.0f;
		//新しい視点を、「新しい注視点　＋　toCameraPos」で求める。
		cameraPos = cameraTarget + toCameraPos;

		//新しい視点と注視点をカメラに設定する。
		g_camera3D->SetPosition(cameraPos);
		g_camera3D->SetTarget(cameraTarget);


		//ティーポットのワールド行列を更新する。
		model.UpdateWorldMatrix(teapotPos, g_quatIdentity, g_vec3One);
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
