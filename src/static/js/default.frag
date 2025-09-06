precision mediump float;

varying vec2 v_UV;
varying vec3 v_Normal;
uniform mat4 u_Transform;

uniform sampler2D u_Color;

void main() {

    vec3 LightPos = vec3(0.0, 0.0, 1.0);
    vec4 image = texture2D(u_Color, v_UV);
    if (image.a < 0.1)
        discard;

    //float lighting = dot(v_Normal, LightPos / sqrt(2.26));
    float lighting = max(dot(v_Normal, LightPos / sqrt(2.26)), 0.0);

    gl_FragColor = vec4(vec3(lighting), 1.0);
}
