#version 120

uniform sampler2DRect inputTexture;
uniform vec2 resolution;

void main() {
    
    // Find the Position of my pixel
    vec2 uv = gl_FragCoord.xy / resolution;

    // Flip the position upside-down (because computers suck and bring in texture flipped)
//    uv.y = 1.0 - uv.y;

    // given where my pixel is, find what color I shoul be from GWPE
    vec3 tc = texture2DRect(inputTexture, uv * resolution).rgb;

    tc = vec3(1.0, 1.0, 1.0) - tc;

    // Display that color on screen
    gl_FragColor = vec4(tc, 1.0);
}
