#include "stdafx.h"
#include "system/system.h"

///////////////////////////////////////////////////////////////////
// 関数宣言
///////////////////////////////////////////////////////////////////
void InitLight(Light& light);
void InitModel(Model& model, Model& bgmodel, Light& light);
void RotateLight(Light& light);
void ExecuteTPSCamea(Vector3 teapotPos);

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

		

		//step-1 カメラの前ベクトルを求める。
		


		//step-2 カメラの前方向を使って、ティーポットの座標を動かす。
		



		//step-3 ティーポットのワールド行列を更新する。
		


		
		//TPSカメラの制御をする関数を呼び出す。
		ExecuteTPSCamea(teapotPos);

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
void ExecuteTPSCamea(Vector3 teapotPos)
{
	//ティーポットに追従させる処理を実行。
		//現在のカメラの視点を取得する。
	Vector3 cameraPos = g_camera3D->GetPosition();
	//現在のカメラのターゲットを取得する。
	Vector3 cameraTarget = g_camera3D->GetTarget();
	//視点から注視点に向かって伸びるベクトルを計算する。
	Vector3 toCameraPos = cameraPos - cameraTarget;

	//コントローラーの入力でY軸周りに回転するカメラを作成する。
	Quaternion qRotY;
	//g_pad[0]->GetRStickXF()はコントローラーの右スティックの入力量が取得できる関数。
	qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.005f);
	//回転クォータニオンでtoCameraPosを回す。
	qRotY.Apply(toCameraPos);

	Vector3 rotAxis;
	rotAxis.Cross(g_vec3AxisY, toCameraPos);
	rotAxis.Normalize();
	Quaternion qRotX;
	qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.005f);
	qRotX.Apply(toCameraPos);

	//新しい注視点をティーポットの少し上に設定する。
	cameraTarget = teapotPos;
	cameraTarget.y += 50.0f;
	//新しい視点を、「新しい注視点　＋　toCameraPos」で求める。
	cameraPos = cameraTarget + toCameraPos;

	//新しい視点と注視点をカメラに設定する。
	g_camera3D->SetPosition(cameraPos);
	g_camera3D->SetTarget(cameraTarget);
}
