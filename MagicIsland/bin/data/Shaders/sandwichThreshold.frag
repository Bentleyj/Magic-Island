#version 120

uniform sampler2DRect inputTexture;
uniform vec2 resolution;
uniform float threshMin;
uniform float threshMax;

void main() {
    
    vec2 uv = gl_FragCoord.xy / resolution;
    
    vec2 uvAbs = uv * resolution;
    
    vec3 tc = texture2DRect(inputTexture, uvAbs).rgb;
    
    float c = (tc.r + tc.g + tc.b)/3.0;
    
    if(c < threshMin) {
        tc = vec3(0.0);
    } else if(c > threshMax) {
        tc = vec3(0.0);
    } else {
        tc = vec3(1.0);
    }
    
    gl_FragColor = vec4(tc, 1.0);
}
