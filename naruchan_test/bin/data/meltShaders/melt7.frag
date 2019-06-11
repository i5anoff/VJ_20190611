#version 150
#pragma include "noise.glsl"

#define PI 3.14159265358979


uniform sampler2D tex0; ////this is "draw in the shader"
uniform sampler2D tex1;

in vec2 varyingtexcoord;
out vec4 outputColor;
uniform vec2 u_resolution;
uniform float u_time;
uniform vec3 u_bColor;
uniform float u_val;
uniform float u_framerate;

//https://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB:Vector_field_and_trajectories_of_a_simple_limit_cycle.svg
vec2 vectorFeild(vec2 _uv){
    //_uv = _uv * 2. - 1; //0to1を-1to1に正規化
    float deltaX = _uv.x/pow((_uv.x*_uv.x + _uv.y*_uv.y), .75);
    float deltaY = _uv.y/pow((_uv.x*_uv.x + _uv.y*_uv.y), .75);
    
    return vec2(deltaX, deltaY);
}

float circle(vec2 _uv){
    vec2 dist = _uv-vec2(0.5);
    return dot(dist, dist);
}

void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    float fRateRate = 60./u_framerate;
    
    //外側に向けてのベクターフィールド
    vec2 signedUv = uv;
    signedUv = (signedUv * 2.0 - 1.)/2.;
    signedUv.x *= u_resolution.x/u_resolution.y * 2.;
    signedUv *= .5;
    
    vec2 delta = vectorFeild(signedUv)*0.001;
    uv -= delta * fRateRate; //ずらす
    
    //ノイズのグネグネ乗せる
    vec2 uv2 =  varyingtexcoord.xy;
    float circlePct = circle(uv2) * .5;
    float noiseTime = u_time * 0.2;
    delta.x = snoise(vec3(uv2*4.5, 10. + noiseTime));
    delta.y = snoise(vec3(uv2*4.5, 90. + noiseTime));
    uv += delta * circlePct * u_val * fRateRate; //ずらす
    
    vec4 t0 = texture(tex0,uv);
    vec4 col;
    col = mix(t0,vec4(u_bColor,1.0), 0.007);
    
    outputColor = col.rgba;

}
