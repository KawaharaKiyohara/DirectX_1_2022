//頂点シェーダーへの入力頂点構造体。
struct VSInput{
	float4 pos : POSITION;
	float3 color : COLOR;
	float2 uv : TEXCOORD; //頂点からUV座標をのデータを引っ張ってくる。
};
//頂点シェーダーの出力。
struct VSOutput{
	float4 pos : SV_POSITION;
	float3 color : COLOR;
	float2 uv : TEXCOORD;
};

cbuffer cb1: register( b0 ){
	float4x4 g_worldMatrix ;

};
cbuffer cb2 : register(b1) {
	float blendRate;
}
sampler g_sampler : register( s0 );

//t0レジスタに設定されているテクスチャにアクセスするための変数を追加する。
Texture2D g_texture0 : register( t0 );
Texture2D g_texture1 : register( t1 );

//頂点シェーダー。
//１．引数は変換前の頂点情報。
//２．戻り値は変換後の頂点情報。
VSOutput VSMain(VSInput In) 
{
	VSOutput vsOut = (VSOutput)0;
	vsOut.pos = mul( g_worldMatrix, In.pos );
	vsOut.uv = In.uv;
	vsOut.color = In.color; //
	return vsOut;
}
//ピクセルシェーダー。
float4 PSMain( VSOutput vsOut ) : SV_Target0
{
	//テクスチャカラーをサンプリングして返す。
	float4 texColor0 = g_texture0.Sample( 
		g_sampler, 	//第一引数はサンプラ。今は気にしなくてよい。
		vsOut.uv	//第二引数はUV座標。
	) ;
	float4 texColor1 = g_texture1.Sample(
		g_sampler, 	//第一引数はサンプラ。今は気にしなくてよい。
		vsOut.uv	//第二引数はUV座標。
	);
	//２枚のテクスチャをブレンディング率を使って線形補完。
	float4 finalColor;
	finalColor = texColor0 * blendRate + texColor1 * (1.0f - blendRate);
	
	return finalColor;
}