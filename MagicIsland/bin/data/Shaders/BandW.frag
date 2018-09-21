#version 120

uniform sampler2DRect inputTexture;
uniform vec2 resolution;

void main() {
    
    vec2 uv = gl_FragCoord.xy / resolution;
    
    vec2 uvAbs = uv * resolution;
    
    vec3 tc = texture2DRect(inputTexture, uvAbs).rgb;
    
    float c = (tc.r + tc.g + tc.b) / 3.0;
    
    tc = vec3(c);
    
    gl_FragColor = vec4(tc, 1.0);
}
