//頂点シェーダーへの入力頂点構造体。
struct VSInput{
	float4 pos : POSITION;
	float3 color : COLOR; //頂点からカラーのデータを引っ張ってくる。
};
//頂点シェーダーの出力。
struct VSOutput{
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};




//頂点シェーダー。
//１．引数は変換前の頂点情報。
//２．戻り値は変換後の頂点情報。
VSOutput VSMain(VSInput In) 
{
	VSOutput vsOut = (VSOutput)0;
	
	vsOut.color = In.color; //
	return vsOut;
}
//ピクセルシェーダー。
float4 PSMain( VSOutput vsOut ) : SV_Target0
{
	return float4( 1.0f, 0.0f , 0.0f, 1.0f);
}