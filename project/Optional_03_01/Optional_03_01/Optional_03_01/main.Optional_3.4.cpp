#include "stdafx.h"
#include "system/system.h"

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
	
	//step-1 モデルをアニメーションさせるために必要なオブジェクトをすべて定義する。
	Skeleton skeleton;						//① スケルトン。
	Model model;								//② モデル表示処理。
	AnimationClip animationClips[2];		//③ アニメーションクリップ。
	Animation animation;					//④ アニメション再生処理。
	

	//step-2 スケルトンを初期化する。
	//SkeletonクラスのInit関数を呼び出している。
	//第一引数はスケルトンデータのファイルパス。
	skeleton.Init("Assets/modelData/unityChan.tks");

	//step-3 モデルを初期化する。
	ModelInitData initData;
	//tkmファイルのファイルパスを指定する。
	initData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	//シェーダーファイルのファイルパスを指定する。
	initData.m_fxFilePath = "Assets/shader/model.fx";
	//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
	initData.m_vsEntryPointFunc = "VSMain";
	//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
	initData.m_vsSkinEntryPointFunc = "VSSkinMain";
	//スケルトンを指定する。
	initData.m_skeleton = &skeleton;

	//モデルの上方向を指定する。
	//3dsMaxではデフォルトZアップになっているが、
	//ユニティちゃんはアニメーションでYアップに変更されている。
	initData.m_modelUpAxis = enModelUpAxisY;

	//ModelクラスのInit関数にinitDataを渡してモデルを初期化する、
	model.Init(initData);

	//step-4 アニメーションクリップをロードする。
	animationClips[0].Load("Assets/animData/idle.tka");
	animationClips[1].Load("Assets/animData/walk.tka");

	//step-10 アニメーションクリップにループ設定をする。
	//歩きクリップにループ設定をつける。	
	animationClips[1].SetLoopFlag(true);

	//step-5 アニメーションの再生処理を初期化する。
	//アニメーションを初期化。
	animation.Init(
		skeleton,				//アニメーションを流し込むスケルトン。
		animationClips,		//アニメーションクリップ。
		2							//アニメーションの数。
	);

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();
		
		//step-9 アニメーションを切り替える。
		if (g_pad[0]->IsPress(enButtonA) ){
			//Assets/animData/idle.tkaを流す。
			animation.Play(0);
		}
		if (g_pad[0]->IsPress(enButtonB)) {
			//Assets/animData/walk.tkaを流す。
			animation.Play(1);
		}
		//step-6 アニメーションを進めるプログラムを追加。
		//AnimationクラスのProgress()を呼び出すとアニメーションが進む。
		//第一引数は進める時間。単位は秒。
		//今回のプログラムでは、毎フレーム、1 ÷ 60 = 0.016秒アニメーションが進む。
		animation.Progress(1.0/60.0f);

		//step-7 アニメーション結果を元にスケルトンを更新。
		//SkeletonクラスのUpdate()を呼び出すと、
		//スケルトンの骨にアニメーションの再生結果が流し込まれます。
		//第一引数にはアニメーションを流すモデルのワールド行列を指定します。
		skeleton.Update(
			model.GetWorldMatrix()
		);
		
		//step-8 モデルを描画。
		model.Draw(renderContext);

		g_engine->EndFrame();
	}

	return 0;
}

