precision mediump float;

varying vec2 v_UV;
varying vec3 v_Normal;
varying vec2 v_Density;
varying mat3 v_TBN;

uniform mat4 u_Transform;

uniform sampler2D u_Color;
uniform sampler2D u_AO;
uniform sampler2D u_Normal;

void main() {
    // Implementing Gauss Weight
    vec2 uv = (gl_PointCoord * 2.0 - 1.0) * v_Density; // map to [-1,1] 
    float r2 = dot(uv, uv); // squared radius in normalized coords 
    float gaussian = exp(-r2 * 3.0); // adjust scale for softness
    
    vec4 image = texture2D(u_Color, v_UV);
    if (image.a * gaussian < 0.05)
        discard;

    vec4 ao = texture2D(u_AO, v_UV);

    //float lighting = dot(v_Normal, LightPos / sqrt(2.26));

    vec3 normalMap = texture2D(u_Normal, v_UV).rgb * 2.0 - 1.0;
    vec3 worldNormal = v_TBN * normalMap;
    worldNormal /= length(worldNormal);
    vec3 LightPos = vec3(0.0, -0.5, 1.0);
    LightPos /= length(LightPos);
    float lighting = max(dot(worldNormal, LightPos), 0.0);

    gl_FragColor = image * vec4(vec3(lighting), 1.0);
    gl_FragColor = image * ao * vec4(vec3(lighting), gaussian * v_Normal.z);
}

