uniform sampler2D texture;
uniform float time;
uniform vec2 resolution;
out vec4 fragColor;

void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    float wave = sin(uv.y * 10.0 + time * 5.0) * 0.02;
    uv.x += wave;
    gl_FragColor = texture2D(texture, uv);
}
