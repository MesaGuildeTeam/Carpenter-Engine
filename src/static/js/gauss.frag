precision mediump float;

varying vec2 v_UV;
varying vec3 v_Normal;
uniform mat4 u_Transform;

uniform sampler2D u_Color;

void main() {
    // Implementing Gauss Weight
    vec2 uv = gl_PointCoord * 2.0 - 1.0; // map to [-1,1] 
    float r2 = dot(uv, uv); // squared radius in normalized coords 
    float gaussian = exp(-r2 * 3.0); // adjust scale for softness

    vec3 LightPos = vec3(0.0, 0.0, 1.0);
    vec4 image = texture2D(u_Color, v_UV);
    if (image.a * gaussian < 0.05)
        discard;

    //float lighting = dot(v_Normal, LightPos / sqrt(2.26));
    float lighting = max(dot(v_Normal, LightPos / sqrt(2.26)), 0.0);
    if (v_Normal.z < 0.0) discard;

    gl_FragColor = image * vec4(vec3(lighting), gaussian * v_Normal.z);
}

