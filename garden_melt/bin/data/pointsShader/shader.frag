#version 150


uniform vec4 globalColor;

in vec2 texCoordVarying;
in vec4 colorVarying;

out vec4 outputColor;


// Author @patriciogv - 2015
// http://patriciogonzalezvivo.com
float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
    return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}
 
void main(){
    
    vec2 uv = gl_PointCoord;
    float pct = circle(uv,.9);
    vec4 color;
    color.rgb = colorVarying.rgb * pct;
    color.a = pct * 0.05;
    
    outputColor = color;
    
    
}
